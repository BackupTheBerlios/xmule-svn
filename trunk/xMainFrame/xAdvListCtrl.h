// The xMule Project - A Peer-2-Peer File Sharing Program
//
// Copyright (C) 2004-2006 Avi Vahl ( avivahl [AT] gmail.com )
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of Version 2 of the GNU General Public
// License as published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA

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
