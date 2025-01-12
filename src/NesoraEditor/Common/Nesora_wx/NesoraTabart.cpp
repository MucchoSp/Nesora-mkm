#include "NesoraTabart.h"

// -- GUI helper classes and functions --

class wxAuiCommandCapture : public wxEvtHandler
{
public:

    wxAuiCommandCapture() { m_lastId = 0; }
    int GetCommandId() const { return m_lastId; }

    bool ProcessEvent(wxEvent& evt) override
    {
        if (evt.GetEventType() == wxEVT_MENU)
        {
            m_lastId = evt.GetId();
            return true;
        }

        if (GetNextHandler())
            return GetNextHandler()->ProcessEvent(evt);

        return false;
    }

private:
    int m_lastId;
};


// these functions live in dockart.cpp -- they'll eventually
// be moved to a new utility cpp file
// lib/wxWidgets/src/aui/dockart.cppから移植してきたやつら

wxBitmap wxAuiBitmapFromBits(const unsigned char bits[], int w, int h,
                             const wxColour& color)
{
    wxImage img = wxBitmap((const char*)bits, w, h).ConvertToImage();
    img.InitAlpha();
    const int newr = color.Red();
    const int newg = color.Green();
    const int newb = color.Blue();
    const int newa = color.Alpha();
    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            int r = img.GetRed(x, y);
            int g = img.GetGreen(x, y);
            int b = img.GetBlue(x, y);
            if (r == 0 && g == 0 && b == 0)
            {
                img.SetAlpha(x, y, wxALPHA_TRANSPARENT);
            }
            else
            {
                img.SetRGB(x, y, newr, newg, newb);
                img.SetAlpha(x, y, newa);
            }
        }
    }
    return wxBitmap(img);
}

inline float wxAuiGetSRGB(float r) {
    return r <= 0.03928f ? r / 12.92f : std::pow((r + 0.055f) / 1.055f, 2.4f);
}

float wxAuiGetRelativeLuminance(const wxColour& c)
{
    // based on https://www.w3.org/TR/2008/REC-WCAG20-20081211/#relativeluminancedef
    return
        0.2126f * wxAuiGetSRGB(c.Red()   / 255.0f) +
        0.7152f * wxAuiGetSRGB(c.Green() / 255.0f) +
        0.0722f * wxAuiGetSRGB(c.Blue()  / 255.0f);
}

// This function is defined in dockart.cpp.
float wxAuiGetColourContrast(const wxColour& c1, const wxColour& c2)
{
    // based on https://www.w3.org/TR/UNDERSTANDING-WCAG20/visual-audio-contrast7.html
    float L1 = wxAuiGetRelativeLuminance(c1);
    float L2 = wxAuiGetRelativeLuminance(c2);
    return L1 > L2 ? (L1 + 0.05f) / (L2 + 0.05f) : (L2 + 0.05f) / (L1 + 0.05f);
}

wxString wxAuiChopText(wxDC& dc, const wxString& text, int max_size)
{
    wxCoord x,y;

    // first check if the text fits with no problems
    dc.GetTextExtent(text, &x, &y);
    if (x <= max_size)
        return text;

    size_t i, len = text.length();
    size_t last_good_length = 0;
    for (i = 0; i < len; ++i)
    {
        wxString s = text.Left(i);
        s += wxT("...");

        dc.GetTextExtent(s, &x, &y);
        if (x > max_size)
            break;

        last_good_length = i;
    }

    wxString ret = text.Left(last_good_length);
    ret += wxT("...");
    return ret;
}

// Check if the color has sufficient contrast ratio (4.5 recommended)
// (based on https://www.w3.org/TR/UNDERSTANDING-WCAG20/visual-audio-contrast7.html)
static bool wxAuiHasSufficientContrast(const wxColour& c1, const wxColour& c2)
{
    return wxAuiGetColourContrast(c1, c2) >= 4.5f;
}

// Pick a color that provides better contrast against the background
static wxColour wxAuiGetBetterContrastColour(const wxColour& back_color,
    const wxColour& c1, const wxColour& c2)
{
    return wxAuiGetColourContrast(back_color, c1)
          > wxAuiGetColourContrast(back_color, c2) ? c1 : c2;
}

static void DrawButtons(wxDC& dc,
                        const wxSize& offset,
                        const wxRect& _rect,
                        const wxBitmap& bmp,
                        const wxColour& bkcolour,
                        int button_state)
{
    wxRect rect = _rect;

    if (button_state == wxAUI_BUTTON_STATE_PRESSED)
    {
        rect.x += offset.x;
        rect.y += offset.y;
    }

    if (button_state == wxAUI_BUTTON_STATE_HOVER ||
        button_state == wxAUI_BUTTON_STATE_PRESSED)
    {
        dc.SetBrush(wxBrush(bkcolour.ChangeLightness(120)));
        dc.SetPen(wxPen(bkcolour.ChangeLightness(75)));

        // draw the background behind the button
        dc.DrawRectangle(rect.x, rect.y, bmp.GetLogicalWidth()-offset.x, bmp.GetLogicalHeight()-offset.y);
    }

    // draw the button itself
    dc.DrawBitmap(bmp, rect.x, rect.y, true);
}

static void IndentPressedBitmap(const wxSize& offset, wxRect* rect, int button_state)
{
    if (button_state == wxAUI_BUTTON_STATE_PRESSED)
    {
        rect->x += offset.x;
        rect->y += offset.y;
    }
}

// -- bitmaps --
// TODO: Provide x1.5 and x2.0 versions or migrate to SVG.

 static const unsigned char ns_close_bits[]={
     0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xf3, 0xcf, 0xf9,
     0x9f, 0xfc, 0x3f, 0xfe, 0x3f, 0xfe, 0x9f, 0xfc, 0xcf, 0xf9, 0xe7, 0xf3,
     0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

static const unsigned char ns_left_bits[] = {
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x7f, 0xfe, 0x3f, 0xfe,
   0x1f, 0xfe, 0x0f, 0xfe, 0x1f, 0xfe, 0x3f, 0xfe, 0x7f, 0xfe, 0xff, 0xfe,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

static const unsigned char ns_right_bits[] = {
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0x9f, 0xff, 0x1f, 0xff,
   0x1f, 0xfe, 0x1f, 0xfc, 0x1f, 0xfe, 0x1f, 0xff, 0x9f, 0xff, 0xdf, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

static const unsigned char ns_list_bits[] = {
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0x0f, 0xf8, 0xff, 0xff, 0x0f, 0xf8, 0x1f, 0xfc, 0x3f, 0xfe, 0x7f, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};


// -- NesoraTabArt class implementation --
// wxAuiGenericTabArtをちょっといじっただけのやつ

NesoraTabArt::NesoraTabArt()
    : m_normalFont(*wxNORMAL_FONT)
    , m_selectedFont(m_normalFont)
{
    m_selectedFont.SetWeight(wxFONTWEIGHT_BOLD);
    m_measuringFont = m_selectedFont;

    m_fixedTabWidth = wxWindow::FromDIP(100, nullptr);
    m_tabCtrlHeight = 0;
    m_flags = 0;

    UpdateColoursFromSystem();
}

NesoraTabArt::~NesoraTabArt()
{
}

void NesoraTabArt::UpdateColoursFromSystem()
{
    wxColor baseColour = wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE);

    // the baseColour is too pale to use as our base colour,
    // so darken it a bit --
    if ((255-baseColour.Red()) +
        (255-baseColour.Green()) +
        (255-baseColour.Blue()) < 60)
    {
        baseColour = baseColour.ChangeLightness(92);
    }

    m_activeColour = baseColour;
    m_baseColour = baseColour;
    wxColor borderColour = baseColour.ChangeLightness(75);

    m_borderPen = wxPen(borderColour);
    m_baseColourPen = wxPen(m_baseColour);
    m_baseColourBrush = wxBrush(m_baseColour);

    const int disabledLightness = wxSystemSettings::GetAppearance().IsUsingDarkBackground() ? 130 : 70;

    m_activeCloseBmp = wxAuiBitmapFromBits(ns_close_bits, 16, 16, wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
    m_disabledCloseBmp = wxAuiBitmapFromBits(ns_close_bits, 16, 16, wxSystemSettings::GetColour(wxSYS_COLOUR_INACTIVECAPTIONTEXT).ChangeLightness(disabledLightness));
    m_activeLeftBmp = wxAuiBitmapFromBits(ns_left_bits, 16, 16, wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
    m_disabledLeftBmp = wxAuiBitmapFromBits(ns_left_bits, 16, 16, wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT));
    m_activeRightBmp = wxAuiBitmapFromBits(ns_right_bits, 16, 16, wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
    m_disabledRightBmp = wxAuiBitmapFromBits(ns_right_bits, 16, 16, wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT));
    m_activeWindowListBmp = wxAuiBitmapFromBits(ns_list_bits, 16, 16, wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
    m_disabledWindowListBmp = wxAuiBitmapFromBits(ns_list_bits, 16, 16, wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT));
}

wxAuiTabArt* NesoraTabArt::Clone()
{
    return new NesoraTabArt(*this);
}

void NesoraTabArt::SetFlags(unsigned int flags)
{
    m_flags = flags;
}

void NesoraTabArt::SetSizingInfo(const wxSize& tab_ctrl_size,
                                       size_t tab_count,
                                       wxWindow* wnd)
{
    if ( !wnd )
    {
        // This is only allowed for backwards compatibility, we should be
        // really passed a valid window.
        wnd = wxTheApp->GetTopWindow();
        wxCHECK_RET( wnd, "must have some window" );
    }

    m_fixedTabWidth = wnd->FromDIP(100);

    int tot_width = (int)tab_ctrl_size.x - GetIndentSize() - wnd->FromDIP(4);

    if (m_flags & wxAUI_NB_CLOSE_BUTTON)
        tot_width -= m_activeCloseBmp.GetPreferredLogicalSizeFor(wnd).x;
    if (m_flags & wxAUI_NB_WINDOWLIST_BUTTON)
        tot_width -= m_activeWindowListBmp.GetPreferredLogicalSizeFor(wnd).x;

    if (tab_count > 0)
    {
        m_fixedTabWidth = tot_width/(int)tab_count;
    }


    m_fixedTabWidth = wxMax(m_fixedTabWidth, wnd->FromDIP(100));

    if (m_fixedTabWidth > tot_width/2)
        m_fixedTabWidth = tot_width/2;

    m_fixedTabWidth = wxMin(m_fixedTabWidth, wnd->FromDIP(220));

    m_tabCtrlHeight = tab_ctrl_size.y;
}


void NesoraTabArt::DrawBorder(wxDC& dc, wxWindow* wnd, const wxRect& rect)
{
    int i, border_width = GetBorderWidth(wnd);

    wxRect theRect(rect);
    for (i = 0; i < border_width; ++i)
    {
        dc.DrawRectangle(theRect.x, theRect.y, theRect.width, theRect.height);
        theRect.Deflate(1);
    }
}

void NesoraTabArt::DrawBackground(wxDC& dc,
                                        wxWindow* WXUNUSED(wnd),
                                        const wxRect& rect)
{
    // draw background
    dc.SetBrush(m_baseColourBrush);
    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.DrawRectangle(-1, -1, rect.GetWidth()+2, rect.GetHeight()+2);

    // draw base line
    dc.SetPen(*wxGREY_PEN);
    dc.DrawLine(0, rect.GetHeight()-1, rect.GetWidth(), rect.GetHeight()-1);
}


// DrawTab() draws an individual tab.
//
// dc       - output dc
// in_rect  - rectangle the tab should be confined to
// caption  - tab's caption
// active   - whether or not the tab is active
// out_rect - actual output rectangle
// x_extent - the advance x; where the next tab should start

void NesoraTabArt::DrawTab(wxDC& dc,
                                 wxWindow* wnd,
                                 const wxAuiNotebookPage& page,
                                 const wxRect& in_rect,
                                 int close_button_state,
                                 wxRect* out_tab_rect,
                                 wxRect* out_button_rect,
                                 int* x_extent)
{
    wxCoord normal_textx, normal_texty;
    wxCoord selected_textx, selected_texty;
    wxCoord texty;

    // if the caption is empty, measure some temporary text
    wxString caption = page.caption;
    if (caption.empty())
        caption = wxT("Xj");

    dc.SetFont(m_selectedFont);
    dc.GetTextExtent(caption, &selected_textx, &selected_texty);

    dc.SetFont(m_normalFont);
    dc.GetTextExtent(caption, &normal_textx, &normal_texty);

    // figure out the size of the tab
    wxSize tab_size = GetTabSize(dc,
                                 wnd,
                                 page.caption,
                                 page.bitmap,
                                 page.active,
                                 close_button_state,
                                 x_extent);

    wxCoord tab_height = m_tabCtrlHeight - 3;
    wxCoord tab_width = tab_size.x;
    wxCoord tab_x = in_rect.x;
    wxCoord tab_y = in_rect.y + in_rect.height - tab_height;


    caption = page.caption;


    // select pen, brush and font for the tab to be drawn

    if (page.active)
    {
        dc.SetFont(m_selectedFont);
        texty = selected_texty;
    }
    else
    {
        dc.SetFont(m_normalFont);
        texty = normal_texty;
    }


    // create points that will make the tab outline

    int clip_width = tab_width;
    if (tab_x + clip_width > in_rect.x + in_rect.width)
        clip_width = (in_rect.x + in_rect.width) - tab_x;

    dc.SetClippingRegion(tab_x, tab_y, clip_width+1, tab_height-3);


    wxPoint border_points[6];
    if (m_flags &wxAUI_NB_BOTTOM)
    {
        border_points[0] = wxPoint(tab_x,             tab_y);
        border_points[1] = wxPoint(tab_x,             tab_y+tab_height-6);
        border_points[2] = wxPoint(tab_x+2,           tab_y+tab_height-4);
        border_points[3] = wxPoint(tab_x+tab_width-2, tab_y+tab_height-4);
        border_points[4] = wxPoint(tab_x+tab_width,   tab_y+tab_height-6);
        border_points[5] = wxPoint(tab_x+tab_width,   tab_y);
    }
    else //if (m_flags & wxAUI_NB_TOP) {}
    {
        border_points[0] = wxPoint(tab_x,             tab_y+tab_height-4);
        border_points[1] = wxPoint(tab_x,             tab_y+2);
        border_points[2] = wxPoint(tab_x+2,           tab_y);
        border_points[3] = wxPoint(tab_x+tab_width-2, tab_y);
        border_points[4] = wxPoint(tab_x+tab_width,   tab_y+2);
        border_points[5] = wxPoint(tab_x+tab_width,   tab_y+tab_height-4);
    }
    // TODO: else if (m_flags &wxAUI_NB_LEFT) {}
    // TODO: else if (m_flags &wxAUI_NB_RIGHT) {}

    int drawn_tab_yoff = border_points[1].y;
    int drawn_tab_height = border_points[0].y - border_points[1].y;

    bool isdark = wxSystemSettings::GetAppearance().IsUsingDarkBackground();

    wxColor back_color = m_baseColour;
    if (page.active)
    {
        // draw active tab

        // draw base background color
        wxRect r(tab_x, tab_y, tab_width, tab_height);
        dc.SetPen(wxPen(m_activeColour));
        dc.SetBrush(wxBrush(m_activeColour));
        dc.DrawRectangle(r.x+1, r.y+1, r.width-1, r.height-4);

        // this white helps fill out the gradient at the top of the tab
        wxColor gradient = *wxWHITE;
        if (isdark)
        {
            //dark mode, we go darker
            gradient = m_activeColour.ChangeLightness(70);
        }
        back_color = gradient;

        dc.SetPen(wxPen(gradient));
        dc.SetBrush(wxBrush(gradient));
        dc.DrawRectangle(r.x+2, r.y+1, r.width-3, r.height-4);

        // these two points help the rounded corners appear more antialiased
        dc.SetPen(wxPen(m_activeColour));
        dc.DrawPoint(r.x+2, r.y+1);
        dc.DrawPoint(r.x+r.width-2, r.y+1);

        // set rectangle down a bit for gradient drawing
        r.SetHeight(r.GetHeight()/2);
        r.x += 2;
        r.width -= 3;
        r.y += r.height;
        r.y -= 2;

        // draw gradient background
        wxColor top_color = gradient;
        wxColor bottom_color = m_activeColour;
        dc.GradientFillLinear(r, bottom_color, top_color, wxNORTH);
    }
    else
    {
        // draw inactive tab

        wxRect r(tab_x, tab_y+1, tab_width, tab_height-3);

        // start the gradient up a bit and leave the inside border inset
        // by a pixel for a 3D look.  Only the top half of the inactive
        // tab will have a slight gradient
        r.x += 3;
        r.y++;
        r.width -= 4;
        r.height /= 2;
        r.height--;

        // -- draw top gradient fill for glossy look
        wxColor top_color = m_baseColour;
        wxColor bottom_color = top_color.ChangeLightness(160);
        if (isdark)
        {
            //dark mode, we go darker
            top_color = m_activeColour.ChangeLightness(70);
            bottom_color = m_baseColour;
        }

        dc.GradientFillLinear(r, bottom_color, top_color, wxNORTH);

        r.y += r.height;
        r.y--;

        // -- draw bottom fill for glossy look
        top_color = m_baseColour;
        bottom_color = m_baseColour;
        dc.GradientFillLinear(r, top_color, bottom_color, wxSOUTH);
    }

    // draw tab outline
    dc.SetPen(m_borderPen);
    dc.SetBrush(m_baseColourBrush);
    dc.DrawPolygon(WXSIZEOF(border_points), border_points);

    // there are two horizontal grey lines at the bottom of the tab control,
    // this gets rid of the top one of those lines in the tab control
    if (page.active)
    {
        if (m_flags &wxAUI_NB_BOTTOM)
            dc.SetPen(wxPen(m_baseColour.ChangeLightness(170)));
        // TODO: else if (m_flags &wxAUI_NB_LEFT) {}
        // TODO: else if (m_flags &wxAUI_NB_RIGHT) {}
        else //for wxAUI_NB_TOP
            dc.SetPen(m_baseColourPen);
        dc.DrawLine(border_points[0].x+1,
                    border_points[0].y,
                    border_points[5].x,
                    border_points[5].y);
    }


    int text_offset;
    int bitmap_offset = 0;
    if (page.bitmap.IsOk())
    {
        bitmap_offset = tab_x + wnd->FromDIP(8);

        const wxBitmap bitmap = page.bitmap.GetBitmapFor(wnd);

        // draw bitmap
        dc.DrawBitmap(bitmap,
                      bitmap_offset,
                      drawn_tab_yoff + (drawn_tab_height/2) - (bitmap.GetLogicalHeight()/2),
                      true);

        text_offset = bitmap_offset + bitmap.GetLogicalWidth();
        text_offset += wnd->FromDIP(3); // bitmap padding
    }
    else
    {
        text_offset = tab_x + wnd->FromDIP(8);
    }

    // draw close button if necessary
    int close_button_width = 0;
    if (close_button_state != wxAUI_BUTTON_STATE_HIDDEN)
    {
        wxBitmapBundle bb = m_disabledCloseBmp;

        if (close_button_state == wxAUI_BUTTON_STATE_HOVER ||
            close_button_state == wxAUI_BUTTON_STATE_PRESSED)
        {
            bb = m_activeCloseBmp;
        }

        const wxBitmap bmp = bb.GetBitmapFor(wnd);

        int offsetY = tab_y-1;
        if (m_flags & wxAUI_NB_BOTTOM)
            offsetY = 1;

        wxRect rect(tab_x + tab_width - bmp.GetLogicalWidth() - wnd->FromDIP(1),
                    offsetY + (tab_height/2) - (bmp.GetLogicalHeight()/2),
                    bmp.GetLogicalWidth(),
                    tab_height);

        IndentPressedBitmap(wnd->FromDIP(wxSize(1, 1)), &rect, close_button_state);
        dc.DrawBitmap(bmp, rect.x, rect.y, true);

        *out_button_rect = rect;
        close_button_width = bmp.GetLogicalWidth();
    }

    wxString draw_text = wxAuiChopText(dc,
                          caption,
                          tab_width - (text_offset-tab_x) - close_button_width);

    // draw tab text
    wxColor sys_color = wxSystemSettings::GetColour(
        page.active ? wxSYS_COLOUR_CAPTIONTEXT : wxSYS_COLOUR_INACTIVECAPTIONTEXT);
    wxColor font_color = wxAuiHasSufficientContrast(back_color, sys_color) ? sys_color
        : wxAuiGetBetterContrastColour(back_color, *wxWHITE, *wxBLACK);
    dc.SetTextForeground(font_color);
    dc.DrawText(draw_text,
                text_offset,
                drawn_tab_yoff + (drawn_tab_height)/2 - (texty/2) - 1);

    // draw focus rectangle except under macOS where it looks out of place
#ifndef __WXOSX__
    if (page.active && (wnd->FindFocus() == wnd))
    {
        wxRect focusRectText(text_offset, (drawn_tab_yoff + (drawn_tab_height)/2 - (texty/2) - 1),
            selected_textx, selected_texty);

        wxRect focusRect;
        wxRect focusRectBitmap;

        if (page.bitmap.IsOk())
        {
            const wxBitmap bitmap = page.bitmap.GetBitmapFor(wnd);

            focusRectBitmap = wxRect(bitmap_offset, drawn_tab_yoff + (drawn_tab_height/2) - (bitmap.GetLogicalHeight()/2),
                                     bitmap.GetLogicalWidth(), bitmap.GetLogicalHeight());
        }

        if (page.bitmap.IsOk() && draw_text.IsEmpty())
            focusRect = focusRectBitmap;
        else if (!page.bitmap.IsOk() && !draw_text.IsEmpty())
            focusRect = focusRectText;
        else if (page.bitmap.IsOk() && !draw_text.IsEmpty())
            focusRect = focusRectText.Union(focusRectBitmap);

        focusRect.Inflate(2, 2);

        wxRendererNative::Get().DrawFocusRect(wnd, dc, focusRect, 0);
    }
#endif // !__WXOSX__

    *out_tab_rect = wxRect(tab_x, tab_y, tab_width, tab_height);

    dc.DestroyClippingRegion();
}

int NesoraTabArt::GetIndentSize()
{
    return wxWindow::FromDIP(5, nullptr);
}

int NesoraTabArt::GetBorderWidth(wxWindow* wnd)
{
    wxAuiManager* mgr = wxAuiManager::GetManager(wnd);
    if (mgr)
    {
        wxAuiDockArt* art = mgr->GetArtProvider();
        if (art)
            return wnd->FromDIP(art->GetMetric(wxAUI_DOCKART_PANE_BORDER_SIZE));
    }
    return 1;
}

int NesoraTabArt::GetAdditionalBorderSpace(wxWindow* WXUNUSED(wnd))
{
    return 0;
}

wxSize NesoraTabArt::GetTabSize(wxReadOnlyDC& dc,
                                      wxWindow* wnd,
                                      const wxString& caption,
                                      const wxBitmapBundle& bitmap,
                                      bool WXUNUSED(active),
                                      int close_button_state,
                                      int* x_extent)
{
    wxCoord measured_textx, measured_texty, tmp;

    dc.SetFont(m_measuringFont);
    dc.GetTextExtent(caption, &measured_textx, &measured_texty);

    dc.GetTextExtent(wxT("ABCDEFXj"), &tmp, &measured_texty);

    // add padding around the text
    wxCoord tab_width = measured_textx;
    wxCoord tab_height = measured_texty;

    // if the close button is showing, add space for it
    if (close_button_state != wxAUI_BUTTON_STATE_HIDDEN)
    {
        // increase by button size plus the padding
        tab_width += m_activeCloseBmp.GetBitmapFor(wnd).GetLogicalWidth() + wnd->FromDIP(3);
    }

    // if there's a bitmap, add space for it
    if (bitmap.IsOk())
    {
        // we need the correct size of the bitmap to be used on this window in
        // logical dimensions for drawing
        const wxSize bitmapSize = bitmap.GetPreferredLogicalSizeFor(wnd);

        // increase by bitmap plus right side bitmap padding
        tab_width += bitmapSize.x + wnd->FromDIP(3);
        tab_height = wxMax(tab_height, bitmapSize.y);
    }

    // add padding
    wxSize padding = wnd->FromDIP(wxSize(16, 10));
    tab_width  += padding.x;
    tab_height += padding.y;

    if (m_flags & wxAUI_NB_TAB_FIXED_WIDTH)
    {
        tab_width = m_fixedTabWidth;
    }

    *x_extent = tab_width;

    return wxSize(tab_width, tab_height);
}


void NesoraTabArt::DrawButton(wxDC& dc,
                                    wxWindow* wnd,
                                    const wxRect& in_rect,
                                    int bitmap_id,
                                    int button_state,
                                    int orientation,
                                    wxRect* out_rect)
{
    wxBitmapBundle bb;
    wxRect rect;

    switch (bitmap_id)
    {
        case wxAUI_BUTTON_CLOSE:
            if (button_state & wxAUI_BUTTON_STATE_DISABLED)
                bb = m_disabledCloseBmp;
            else
                bb = m_activeCloseBmp;
            break;
        case wxAUI_BUTTON_LEFT:
            if (button_state & wxAUI_BUTTON_STATE_DISABLED)
                bb = m_disabledLeftBmp;
            else
                bb = m_activeLeftBmp;
            break;
        case wxAUI_BUTTON_RIGHT:
            if (button_state & wxAUI_BUTTON_STATE_DISABLED)
                bb = m_disabledRightBmp;
            else
                bb = m_activeRightBmp;
            break;
        case wxAUI_BUTTON_WINDOWLIST:
            if (button_state & wxAUI_BUTTON_STATE_DISABLED)
                bb = m_disabledWindowListBmp;
            else
                bb = m_activeWindowListBmp;
            break;
    }


    if (!bb.IsOk())
        return;

    const wxBitmap bmp = bb.GetBitmapFor(wnd);

    rect = in_rect;

    if (orientation == wxLEFT)
    {
        rect.SetX(in_rect.x);
        rect.SetY(((in_rect.y + in_rect.height)/2) - (bmp.GetLogicalHeight()/2));
        rect.SetWidth(bmp.GetLogicalWidth());
        rect.SetHeight(bmp.GetLogicalHeight());
    }
    else
    {
        rect = wxRect(in_rect.x + in_rect.width - bmp.GetLogicalWidth(),
                      ((in_rect.y + in_rect.height)/2) - (bmp.GetLogicalHeight()/2),
                      bmp.GetLogicalWidth(), bmp.GetLogicalHeight());
    }

    IndentPressedBitmap(wnd->FromDIP(wxSize(1, 1)), &rect, button_state);
    dc.DrawBitmap(bmp, rect.x, rect.y, true);

    *out_rect = rect;
}

int NesoraTabArt::ShowDropDown(wxWindow* wnd,
                                     const wxAuiNotebookPageArray& pages,
                                     int /*active_idx*/)
{
    wxMenu menuPopup;

    size_t i, count = pages.GetCount();
    for (i = 0; i < count; ++i)
    {
        const wxAuiNotebookPage& page = pages.Item(i);

        // Preserve ampersands possibly present in the caption string by
        // escaping them before passing the caption to wxMenuItem.
        wxString caption = wxControl::EscapeMnemonics(page.caption);

        // if there is no caption, make it a space.  This will prevent
        // an assert in the menu code.
        if (caption.IsEmpty())
            caption = wxT(" ");

        wxMenuItem* item = new wxMenuItem(nullptr, 1000+i, caption);
        if (page.bitmap.IsOk())
            item->SetBitmap(page.bitmap.GetBitmapFor(wnd));
        menuPopup.Append(item);
    }

    // find out where to put the popup menu of window items
    wxPoint pt = ::wxGetMousePosition();
    pt = wnd->ScreenToClient(pt);

    // find out the screen coordinate at the bottom of the tab ctrl
    wxRect cli_rect = wnd->GetClientRect();
    pt.y = cli_rect.y + cli_rect.height;

    wxAuiCommandCapture* cc = new wxAuiCommandCapture;
    wnd->PushEventHandler(cc);
    wnd->PopupMenu(&menuPopup, pt);
    int command = cc->GetCommandId();
    wnd->PopEventHandler(true);

    if (command >= 1000)
        return command-1000;

    return -1;
}

int NesoraTabArt::GetBestTabCtrlSize(wxWindow* wnd,
                                           const wxAuiNotebookPageArray& pages,
                                           const wxSize& requiredBmp_size)
{
    wxInfoDC dc(wnd);
    dc.SetFont(m_measuringFont);

    // sometimes a standard bitmap size needs to be enforced, especially
    // if some tabs have bitmaps and others don't.  This is important because
    // it prevents the tab control from resizing when tabs are added.
    wxBitmap measureBmp;
    if (requiredBmp_size.IsFullySpecified())
    {
        measureBmp.Create(requiredBmp_size.x,
                           requiredBmp_size.y);
    }


    int max_y = 0;
    size_t i, page_count = pages.GetCount();
    for (i = 0; i < page_count; ++i)
    {
        wxAuiNotebookPage& page = pages.Item(i);

        wxBitmapBundle bmp;
        if (measureBmp.IsOk())
            bmp = measureBmp;
        else
            bmp = page.bitmap;

        // we don't use the caption text because we don't
        // want tab heights to be different in the case
        // of a very short piece of text on one tab and a very
        // tall piece of text on another tab
        int x_ext = 0;
        wxSize s = GetTabSize(dc,
                              wnd,
                              wxT("ABCDEFGHIj"),
                              bmp,
                              true,
                              wxAUI_BUTTON_STATE_HIDDEN,
                              &x_ext);

        max_y = wxMax(max_y, s.y);
    }

    return max_y+2;
}

void NesoraTabArt::SetNormalFont(const wxFont& font)
{
    m_normalFont = font;
}

void NesoraTabArt::SetSelectedFont(const wxFont& font)
{
    m_selectedFont = font;
}

void NesoraTabArt::SetMeasuringFont(const wxFont& font)
{
    m_measuringFont = font;
}

void NesoraTabArt::SetColour(const wxColour& colour)
{
    m_baseColour = colour;
    m_borderPen = wxPen(m_baseColour.ChangeLightness(75));
    m_baseColourPen = wxPen(m_baseColour);
    m_baseColourBrush = wxBrush(m_baseColour);
}

void NesoraTabArt::SetActiveColour(const wxColour& colour)
{
    m_activeColour = colour;
}

wxFont NesoraTabArt::GetNormalFont() const
{
    return m_normalFont;
}

wxFont NesoraTabArt::GetSelectedFont() const
{
    return m_selectedFont;
}
