
#ifndef NESORA_MANAGER_H
#define NESORA_MANAGER_H

#include <iostream>
#include <wx/wx.h>
#include "../Common/NesoraWindowIDs.h"

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame {
public:
    MyFrame(
        wxWindow* parent,
        wxWindowID id,
        const wxString& title,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_FRAME_STYLE,
        const wxString& name = wxFrameNameStr
        );
 
private:
    wxMenu *menuFile;
    wxMenu *menuHelp;
    wxMenuBar *menuBar;

    wxPanel* panel;
    wxTextCtrl* textCtrl;
    wxButton* button_uc;
    wxButton* button_lc;

    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};

enum {
    ID_Hello = 1
};


#endif