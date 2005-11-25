/**
 * xAdvListCtrl - Advanced wxListCtrl
 */

#ifndef _XADVLISTCTRL_H_
#define _XADVLISTCTRL_H_

#include "../xApp.h"                   // wxGetApp()

#include <wx/listctrl.h>               // wxListCtrl
#include <wx/dcclient.h>               // wxPaintDC

class xAdvListCtrl : public wxListCtrl
{
public:
    xAdvListCtrl() : wxListCtrl() { }
    xAdvListCtrl(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxLC_ICON)
        : wxListCtrl(parent, id, pos, size, style) { }

protected:
    void OnPaint(wxPaintEvent& event);
    void OnErase(wxEraseEvent&) { wxClientDC dc(this); dc.Clear(); dc.DrawIcon(wxIcon(xmule_xpm),0,50); }
    
    DECLARE_EVENT_TABLE()
};

void xAdvListCtrl::OnPaint(wxPaintEvent&)
{
    static int avi=0;
    avi++;
    wxString toStatus(wxT("Paint Event #"));
    toStatus<<avi;
    wxGetApp().Log(toStatus);
    wxPaintDC dc(this);
}

BEGIN_EVENT_TABLE(xAdvListCtrl, wxListCtrl)
    EVT_PAINT(xAdvListCtrl::OnPaint)
    EVT_ERASE_BACKGROUND(xAdvListCtrl::OnErase)
END_EVENT_TABLE()

#endif // _XADVLISTCTRL_H_
