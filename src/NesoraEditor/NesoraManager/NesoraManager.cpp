#include "NesoraManager.h"


bool NesoraApp::OnInit() {
    wxInitAllImageHandlers();
    NesoraFrame *frame = new NesoraFrame(nullptr, wxID_ANY, "nesora.app.name"_ns_locale, wxDefaultPosition, wxSize(1280, 720));
    frame->Show(true);
    return true;
}

NesoraFrame::NesoraFrame(
    wxWindow* parent,
    wxWindowID id,
    const wxString& title,
    const wxPoint& pos,
    const wxSize& size,
    long style,
    const wxString& name
) : wxFrame(parent, id, title, pos, size, style, name) {
    SetNesoraMenuBar();

    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");

    //パネル（親widgetはこのthisつまりNesoraFrame）
    panel = new wxPanel(this, wxID_ANY);

    if(wxPlatformId::MatchesCurrent("msw"))
        nesoraPlaginDirectory = wxFileName::GetHomeDir().ToStdString() + "/AppData/Local/Nesora/NesoraMikomi/Plugin";
    else
        nesoraPlaginDirectory = wxFileName::GetHomeDir().ToStdString() + "/Library/Nesora/NesoraMikomi/Plugin";
    nesoraProjectDirectory = wxFileName::GetHomeDir().ToStdString() + "/Documents/Nesora/NesoraMikomi/Plugin";

    // ツリーコントロールとノートブックウィジェットを分割するやつ
    splitter = new wxSplitterWindow(panel, wxID_ANY);
    splitter->SetMinimumPaneSize(20);

    // ツリーコントロール（親widgetはsplitter）
    treectrl = new wxTreeCtrl(splitter, ID_MANAGER_TREE, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE);
    wxTreeItemId root = treectrl->AddRoot("Nesora Mikomi/str");
    SetFileTree("./src", root);
    treectrl->Bind(wxEVT_LEFT_DCLICK, [=](wxMouseEvent &event)
                   {
            wxPanel* editor_panel;

            auto text = treectrl->GetItemText(treectrl->GetSelection());
            std::string textstr = text.ToStdString();

            //MACなので、.dylibにしています。Linuxならば、.soにしてください。
            if(textstr.rfind('.') != std::string::npos){
                if(nesora::plugin::pluginlist_editor.find(textstr.substr(textstr.find_last_of('.')))){
                    std::string pluginfile = nesoraPlaginDirectory + std::string("/editor/") + nesora::plugin::pluginlist_editor[textstr.substr(textstr.find_last_of('.'))] + NESORA_PLUGIN_FILE_NAME;
                    const auto addlib = dlopen(pluginfile.c_str(), RTLD_LAZY);
                    if (addlib == NULL) {
                        const char *const error_message = dlerror();
                        //std::cerr << error_message << std::endl;
                        auto dialog = wxMessageDialog(panel, error_message, "error.plugin.notfoundfile"_ns_locale);
                        dialog.ShowModal();
                        return 1;
                    }

                    void* const addfunc = dlsym(addlib, "makeObject");
                    {
                        const char* const error_message = dlerror();
                        if (error_message != NULL) {
                            //std::cerr << error_message << std::endl;
                            auto dialog = wxMessageDialog(panel, error_message, "error.plugin.notfoundfunction"_ns_locale);
                            dialog.ShowModal();
                            dlclose(addfunc);
                            return 1;
                        }
                    }
                    editor_panel = reinterpret_cast<wxPanel*(*)(wxWindow*, wxWindowID, const wxString&)>(addfunc)(notebook, wxID_ANY, ((NesoraTreeItemData*)treectrl->GetItemData(treectrl->GetSelection()))->GetPath());

                    dlclose(addfunc);
                } else {
                    editor_panel = new wxPanel(notebook, wxID_ANY);
                    wxStaticText *error_text = new wxStaticText(editor_panel, wxID_ANY, "error.plugin.notsetup"_ns_locale);
                }
            } else {
                std::error_code ec;
                std::string path = ((NesoraTreeItemData *)treectrl->GetItemData(treectrl->GetSelection()))->GetPath();
                if (std::filesystem::is_directory(path, ec)) {
                    editor_panel = new wxPanel(notebook, wxID_ANY);
                    wxStaticText *error_text = new wxStaticText(editor_panel, wxID_ANY, "directory desu\n" + path);
                } else {
                    editor_panel = new wxPanel(notebook, wxID_ANY);
                    wxStaticText *error_text = new wxStaticText(editor_panel, wxID_ANY, "error.plugin.notextension"_ns_locale);
                }
            }

            if (tabs.size())
            {
                int nowSelection = notebook->GetSelection();
                auto newTab = tabs.insert(tabs.begin() + nowSelection, editor_panel);
                notebook->InsertPage(nowSelection + 1, *newTab, text, true);
            }
            else
            {
                tabs.push_back(editor_panel);
                notebook->AddPage(tabs[0], text);
                notebook->SetSelection(0);
            }
            return 0; });
    treectrl->Expand(root);

    // Create the wxNotebook widget
    notebook = new wxAuiNotebook(splitter, wxID_ANY, wxDefaultPosition, FromDIP(wxSize(200, -1)), wxAUI_NB_DEFAULT_STYLE | wxAUI_NB_TAB_EXTERNAL_MOVE);
    notebook->SetArtProvider(new NesoraTabArt);
    notebook->Bind(wxEVT_AUINOTEBOOK_PAGE_CLOSE, [=](wxAuiNotebookEvent &event)
                   {
                int nowSelection = notebook->GetSelection();
                tabs.erase(tabs.begin() + nowSelection); });

    splitter->SplitVertically(treectrl, notebook, 256);

    // 絵ボタン (親widgetはplanel)
    bitmap.LoadFile("assets/64x64.png", wxBITMAP_TYPE_PNG);
    button1 = new wxBitmapButton(panel, wxID_ANY, bitmap, wxDefaultPosition, wxSize(64, 64));

    SetLayout();

}

void NesoraFrame::SetFileTree(std::string path, wxTreeItemId id) {
    for(const std::filesystem::directory_entry &i:std::filesystem::directory_iterator(path)) {
        if(i.is_directory()) {
            wxTreeItemId directry = treectrl->AppendItem(id, i.path().filename().string(), -1, -1, new NesoraTreeItemData(i.path().string()));
            SetFileTree(i.path().string(), directry);
        } else {
            treectrl->AppendItem(id, i.path().filename().string(), -1, -1, new NesoraTreeItemData(i.path().string()));
        }
    }
}

void NesoraFrame::SetLayout() {
    // サイザー (一番大きいやつ)
    auto mainSizer = new wxBoxSizer(wxHORIZONTAL);

    //レイアウトを整える
    panel->SetSizer(mainSizer);

    mainSizer->Add(button1, 0, wxALIGN_LEFT);
    mainSizer->Add(splitter, 1, wxEXPAND);
}

