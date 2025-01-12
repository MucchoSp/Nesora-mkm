
#ifndef NESORA_MANAGER_H
#define NESORA_MANAGER_H

#include <iostream>
#include <filesystem>

#include <wx/wx.h>
#include <wx/aui/aui.h>
#include <wx/treectrl.h>
#include <wx/artprov.h>

#include "../Common/NesoraWindowIDs.h"
#include "../Common/NesoraLocale.h"
#include "../Common/Nesora_wx/NesoraTabart.h"

class NesoraApp : public wxApp {
public:
    virtual bool OnInit();

    void SetShowImages(bool show) { m_showImages = show; }
    bool ShowImages() const { return m_showImages; }

    void SetShowStates(bool show) { m_showStates = show; }
    bool ShowStates() const { return m_showStates; }

private:
    bool m_showImages, m_showStates, m_showButtons;
};//class NesoraApp

class NesoraFrame : public wxFrame {
public:
    NesoraFrame(
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
    wxTreeCtrl* treectrl;
    wxBitmapButton* button1;
    wxAuiNotebook *notebook;
    std::vector<wxPanel*> tabs;

    wxBitmap bitmap;

    void OnHello(wxCommandEvent& event);
    void OnNesora(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent& event);

    void SetFileTree(std::string path, wxTreeItemId id);
    void SetLayout();

    void SetNesoraMenuBar();
}; // class NesoraFrame

enum {
    ID_Hello = nesoraEditorID::NS_ID_MANAGER_START,
    ID_Hello_Nesora,
    ID_Help_Nesora,
    ID_MANAGER_TREE
};

wxDECLARE_APP(NesoraApp);

#endif //NESORA_MANAGER_H