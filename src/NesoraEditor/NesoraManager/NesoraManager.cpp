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

    //ツリーコントロール（親widgetはpanel）
    treectrl = new wxTreeCtrl(panel, ID_MANAGER_TREE, wxDefaultPosition, wxSize(256, 64), wxTR_DEFAULT_STYLE);
    wxTreeItemId root    = treectrl->AddRoot("Nesora Mikomi/str");
    SetFileTree("./src", root);
    treectrl->Bind(wxEVT_LEFT_DCLICK, [=](wxMouseEvent &event) {
            auto text = treectrl->GetItemText(treectrl->GetSelection());
            if(tabs.size()) {
                int nowSelection = notebook->GetSelection();
                auto newTab = tabs.insert(tabs.begin() + nowSelection, new wxPanel(notebook, wxID_ANY));
                notebook->InsertPage(nowSelection + 1, *newTab, text, true);
            } else {
                tabs.push_back(new wxPanel(notebook, wxID_ANY));
                notebook->AddPage(new wxPanel(notebook, wxID_ANY), text);
                notebook->SetSelection(0);
            }});
        

    //絵ボタン (親widgetはplanel)
    bitmap.LoadFile("assets/64x64.png", wxBITMAP_TYPE_PNG);
    button1 = new wxBitmapButton(panel, wxID_ANY, bitmap, wxDefaultPosition, wxSize(64, 64));

    // Create the wxNotebook widget
    notebook = new wxAuiNotebook(panel, wxID_ANY, wxDefaultPosition, FromDIP(wxSize(200,-1)), wxAUI_NB_DEFAULT_STYLE);
    notebook->SetArtProvider(new NesoraTabArt);
    notebook->Bind(wxEVT_AUINOTEBOOK_PAGE_CLOSE, [=](wxAuiNotebookEvent & event){
                int nowSelection = notebook->GetSelection();
                tabs.erase(tabs.begin() + nowSelection);
            });

    // Add 2 pages to the wxNotebook widget
    // tabs.push_back(new wxPanel(notebook, wxID_ANY));
    // notebook->AddPage(tabs[0], "Tab 1");
    // tabs.push_back(new wxPanel(notebook, wxID_ANY));
    // notebook->AddPage(tabs[1], "Tab 2");

    SetLayout();

}

void NesoraFrame::SetFileTree(std::string path, wxTreeItemId id) {
    for(const std::filesystem::directory_entry &i:std::filesystem::directory_iterator(path)) {
        if(i.is_directory()) {
            wxTreeItemId directry = treectrl->AppendItem(id, i.path().filename().string());
            SetFileTree(i.path().string(), directry);
        } else {
            treectrl->AppendItem(id, i.path().filename().string());
        }
    }
}

void NesoraFrame::SetLayout() {
    // サイザー (一番大きいやつ)
    auto mainSizer = new wxBoxSizer(wxHORIZONTAL);

    //レイアウトを整える
    panel->SetSizer(mainSizer);

    mainSizer->Add(button1, 0, wxALIGN_LEFT);
    mainSizer->Add(treectrl, 0, wxALL | wxEXPAND);
    mainSizer->Add(notebook, 1, wxEXPAND);
}

