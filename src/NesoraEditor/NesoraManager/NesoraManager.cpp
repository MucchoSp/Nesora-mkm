#include "NesoraManager.h"



bool NesoraApp::OnInit() {
    wxInitAllImageHandlers();
    NesoraFrame *frame = new NesoraFrame(nullptr, wxID_ANY, "My test app", wxDefaultPosition, wxSize(768, 576));
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
    menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
 
    menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
 
    menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
 
    SetMenuBar(menuBar);

    Bind(wxEVT_MENU, &NesoraFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &NesoraFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &NesoraFrame::OnExit, this, wxID_EXIT);
 
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");

    //パネル（親widgetはこのthisつまりNesoraFrame）
    panel = new wxPanel(this, wxID_ANY);

    //テキストコントロール（親widgetはpanel）
    textCtrl = new wxTextCtrl(panel, wxID_ANY);

    //ボタン（親widgetはpanel）
    button_uc = new wxButton(panel, wxID_ANY, "UpperCase");
    button_lc = new wxButton(panel, wxID_ANY, "LowerCase");

    //ツリーコントロール（親widgetはpanel）
    treectrl = new wxTreeCtrl(panel, ID_MANAGER_TREE, wxDefaultPosition, wxSize(256, 64), wxTR_DEFAULT_STYLE);
    wxTreeItemId root    = treectrl->AddRoot("Nesora Mikomi/str");
    SetFileTree("./src", root);
    treectrl->Bind(wxEVT_LEFT_DCLICK, [=](wxMouseEvent &event) {
            auto text = treectrl->GetItemText(treectrl->GetSelection());
            textCtrl->SetValue(text); });

    bitmap.LoadFile("assets/64x64.png", wxBITMAP_TYPE_PNG);
    button1 = new wxBitmapButton(panel, wxID_ANY, bitmap, wxDefaultPosition, wxSize(64, 64));

    SetLayout();

    //UpperCaseボタンを押したら、TextCtrlの文字列をUpperCaseする
    button_uc->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event) {
        //ダイアログ（親widgetはこのthisつまりmyFrame）
        auto dialog = wxMessageDialog(this, "テキストをUpperCaseしますか？", "タイトル", wxCANCEL);

        //ダイアログを表示して、OKボタンを押したらテキストの変換を実施する
        if(dialog.ShowModal() == wxID_OK) {
            auto text = textCtrl->GetValue();
            text.UpperCase();
            textCtrl->SetValue(text);
        }
    });

    //LowerCaseボタンを押したら、TextCtrlの文字列をLowerCaseする
    button_lc->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event) {
        //ダイアログ（親widgetはこのthisつまりmyFrame）
        auto dialog = wxMessageDialog(this, "テキストをlowerCaseしますか？", "タイトル", wxCANCEL);

        //ダイアログを表示して、OKボタンを押したらテキストの変換を実施する    
        if(dialog.ShowModal() == wxID_OK) {
            auto text = textCtrl->GetValue();
            text.LowerCase();
            textCtrl->SetValue(text);
        }
    });

}

void NesoraFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}

void NesoraFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("This is a wxWidgets Hello World example", "About Hello World", wxOK | wxICON_INFORMATION);
}

void NesoraFrame::OnHello(wxCommandEvent& event) {
    wxLogMessage("Hello world from wxWidgets!");
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
    // サイザー（垂直方向に詰める）
    auto vsizer = new wxBoxSizer(wxVERTICAL);
    //サイザー（水平方向に詰める）
    auto hsizer = new wxBoxSizer(wxHORIZONTAL);

    //レイアウトを整える
    panel->SetSizer(mainSizer);

    mainSizer->Add(button1, 0, wxALIGN_LEFT);
    mainSizer->Add(treectrl, 0, wxALL | wxEXPAND);
    mainSizer->Add(vsizer, 0, wxALIGN_LEFT);
    vsizer->Add(textCtrl, 0, wxALIGN_CENTER);
    vsizer->Add(hsizer, 0, wxALIGN_CENTER);
    hsizer->Add(button_uc, 0, wxALIGN_CENTER);
    hsizer->Add(button_lc, 0, wxALIGN_CENTER);
}
