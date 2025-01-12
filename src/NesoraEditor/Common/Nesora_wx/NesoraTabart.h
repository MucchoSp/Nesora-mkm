#ifndef NESORA_TABART_H
#define NESORA_TABART_H

#include <wx/wx.h>
#include <wx/aui/aui.h>

class WXDLLIMPEXP_AUI NesoraTabArt : public wxAuiTabArt
{

public:

    NesoraTabArt();
    virtual ~NesoraTabArt();

    wxAuiTabArt* Clone() override;
    void SetFlags(unsigned int flags) override;
    void SetSizingInfo(const wxSize& tabCtrlSize,
                       size_t tabCount,
                       wxWindow* wnd = nullptr) override;

    void SetNormalFont(const wxFont& font) override;
    void SetSelectedFont(const wxFont& font) override;
    void SetMeasuringFont(const wxFont& font) override;
    void SetColour(const wxColour& colour) override;
    void SetActiveColour(const wxColour& colour) override;

    wxFont GetNormalFont() const override;
    wxFont GetSelectedFont() const override;

    void DrawBorder(
                 wxDC& dc,
                 wxWindow* wnd,
                 const wxRect& rect) override;

    void DrawBackground(
                 wxDC& dc,
                 wxWindow* wnd,
                 const wxRect& rect) override;

    void DrawTab(wxDC& dc,
                 wxWindow* wnd,
                 const wxAuiNotebookPage& pane,
                 const wxRect& inRect,
                 int closeButtonState,
                 wxRect* outTabRect,
                 wxRect* outButtonRect,
                 int* xExtent) override;

    void DrawButton(
                 wxDC& dc,
                 wxWindow* wnd,
                 const wxRect& inRect,
                 int bitmapId,
                 int buttonState,
                 int orientation,
                 wxRect* outRect) override;

    int GetIndentSize() override;

    int GetBorderWidth(
                 wxWindow* wnd) override;

    int GetAdditionalBorderSpace(
                 wxWindow* wnd) override;

    wxSize GetTabSize(
                 wxReadOnlyDC& dc,
                 wxWindow* wnd,
                 const wxString& caption,
                 const wxBitmapBundle& bitmap,
                 bool active,
                 int closeButtonState,
                 int* xExtent) override;

    int ShowDropDown(
                 wxWindow* wnd,
                 const wxAuiNotebookPageArray& items,
                 int activeIdx) override;

    int GetBestTabCtrlSize(wxWindow* wnd,
                 const wxAuiNotebookPageArray& pages,
                 const wxSize& requiredBmpSize) override;

    // Provide opportunity for subclasses to recalculate colours
    virtual void UpdateColoursFromSystem() override;

protected:

    wxFont m_normalFont;
    wxFont m_selectedFont;
    wxFont m_measuringFont;
    wxColour m_baseColour;
    wxPen m_baseColourPen;
    wxPen m_borderPen;
    wxBrush m_baseColourBrush;
    wxColour m_activeColour;
    wxBitmapBundle m_activeCloseBmp;
    wxBitmapBundle m_disabledCloseBmp;
    wxBitmapBundle m_activeLeftBmp;
    wxBitmapBundle m_disabledLeftBmp;
    wxBitmapBundle m_activeRightBmp;
    wxBitmapBundle m_disabledRightBmp;
    wxBitmapBundle m_activeWindowListBmp;
    wxBitmapBundle m_disabledWindowListBmp;

    int m_fixedTabWidth;
    int m_tabCtrlHeight;
    unsigned int m_flags;
};

#endif //NESORA_TABART_H