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

#ifndef _XKADPANEL_H_
#define _XKADPANEL_H_

#include <wx/panel.h>                  // wxPanel
#include <wx/string.h>                 // wxString
#include <wx/wxchar.h>                 // wxT()
#include <wx/stattext.h>               // wxStaticText

class wxListCtrl;

class xKadPanel: public wxPanel
{
public:
    xKadPanel(wxWindow* aParent);
    ~xKadPanel();

    void SetContactsLabel(const wxString& newLabel) { ContactsLabel->SetLabel(newLabel); }
    void SetSearchesLabel(const wxString& newLabel) { SearchesLabel->SetLabel(newLabel); }

private:
    void InitListCtrls();

    wxStaticText* ContactsLabel;
    wxListCtrl* ContactsListCtrl;
    wxStaticText* SearchesLabel;
    wxListCtrl* SearchesListCtrl;

    DECLARE_EVENT_TABLE()
};

#endif // _XKADPANEL_H_
