#include "NesoraManager.h"

void NesoraFrame::SetNesoraMenuBar() {
    menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "nesora.manager.menubar.file.hello"_ns_locale, "Help string shown in status bar for this menu item");
    menuFile->Append(ID_Hello_Nesora, "nesora.manager.menubar.file.nesora"_ns_locale, "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
 
    menuHelp = new wxMenu;
    menuHelp->Append(ID_Help_Nesora, "nesora.manager.menubar.help.aboutNesora"_ns_locale, "About Nesora");
    menuHelp->Append(wxID_ABOUT);

    menuPlugin = new wxMenu;
    menuPlugin->Append(ID_Open_Plugi_Dir_Nesora, "nesora.manager.menubar.plugin.openfile"_ns_locale, "Open plugin directory");

    menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "nesora.manager.menubar.file"_ns_locale);
    menuBar->Append(menuPlugin, "nesora.manager.menubar.plugin"_ns_locale);
    menuBar->Append(menuHelp, "nesora.manager.menubar.help"_ns_locale);
 
    SetMenuBar(menuBar);

    Bind(wxEVT_MENU, &NesoraFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &NesoraFrame::OnOpenPluginDirectory, this, ID_Open_Plugi_Dir_Nesora);
    Bind(wxEVT_MENU, &NesoraFrame::OnNesora, this, ID_Hello_Nesora);
    Bind(wxEVT_MENU, &NesoraFrame::OnNesora, this, ID_Help_Nesora);
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

void NesoraFrame::OnOpenPluginDirectory(wxCommandEvent& event) {
    std::error_code ec;
    if (!std::filesystem::exists(nesoraPlaginDirectory, ec)) {
        if(wxMessageDialog(panel, "nesora.manager.plugin.notfounddirectory"_ns_locale, "Nesora", wxCANCEL | wxYES_NO).ShowModal() == wxID_YES)
            std::filesystem::create_directory(nesoraPlaginDirectory);
        else
            return;
    }
    wxExecute("open -R " + nesoraPlaginDirectory);
}