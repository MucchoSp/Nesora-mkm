#include "NesoraManager.h"



bool MyApp::OnInit() {
    MyFrame *frame = new MyFrame(nullptr, wxID_ANY, "My test app");
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(
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

    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
 
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");

    //パネル（親widgetはこのthisつまりmyFrame）
    panel = new wxPanel(this, wxID_ANY);

    //テキストコントロール（親widgetはpanel）
    textCtrl = new wxTextCtrl(panel, wxID_ANY);

    //ボタン（親widgetはpanel）
    button_uc = new wxButton(panel, wxID_ANY, "UpperCase");
    button_lc = new wxButton(panel, wxID_ANY, "LowerCase");

    //サイザー（垂直方向に詰める）
    auto vsizer = new wxBoxSizer(wxVERTICAL);

    //サイザー（水平方向に詰める）
    auto hsizer = new wxBoxSizer(wxHORIZONTAL);

    //レイアウトを整える
    panel->SetSizer(vsizer);

    vsizer->Add(textCtrl, 0, wxALIGN_CENTER);
    vsizer->Add(hsizer, 0, wxALIGN_CENTER);
    hsizer->Add(button_uc, 0, wxALIGN_CENTER);
    hsizer->Add(button_lc, 0, wxALIGN_CENTER);

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

void MyFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("This is a wxWidgets Hello World example", "About Hello World", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent& event) {
    wxLogMessage("Hello world from wxWidgets!");
}

