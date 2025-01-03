#include "NesoraManager.h"

void NesoraFrame::SetNesoraMenuBar() {
    menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...", "Help string shown in status bar for this menu item");
    menuFile->Append(ID_Hello_Nesora, "&Nesora...\tCtrl-N", "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
 
    menuHelp = new wxMenu;
    menuHelp->Append(ID_Help_Nesora, "&About Nesora...\tCtrl-H", "About Nesora");
    menuHelp->Append(wxID_ABOUT);

    menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
 
    SetMenuBar(menuBar);

    Bind(wxEVT_MENU, &NesoraFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &NesoraFrame::OnNesora, this, ID_Hello_Nesora);
    Bind(wxEVT_MENU, &NesoraFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &NesoraFrame::OnExit, this, wxID_EXIT);
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

void NesoraFrame::OnNesora(wxCommandEvent &event) {
    wxLogMessage("Hello Nesora from wxWidgets!");
}
