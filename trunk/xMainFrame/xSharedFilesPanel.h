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

#ifndef _XSHAREDFILESPANEL_H_
#define _XSHAREDFILESPANEL_H_

#include <wx/panel.h>                  // wxPanel

class wxStaticText;
class wxListCtrl;

class xSharedFilesPanel: public wxPanel
{
public:
    xSharedFilesPanel(wxWindow* aParent);
    ~xSharedFilesPanel();

private:
    wxStaticText* SessionRequests;
    wxStaticText* SessionAccepted;
    wxStaticText* SessionTransferred;
    wxStaticText* TotalRequests;
    wxStaticText* TotalAccepted;
    wxStaticText* TotalTransferred;
    wxListCtrl* SharedFilesListCtrl;

    void InitListCtrl();

    DECLARE_EVENT_TABLE()
};

#endif // _XSHAREDFILESPANEL_H_
