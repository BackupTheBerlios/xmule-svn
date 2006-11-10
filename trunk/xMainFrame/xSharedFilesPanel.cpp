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

#include "xSharedFilesPanel.h"         // xSharedFilesPanel
#include "xResources.h"                // IDs and XPMs

#include <wx/xrc/xmlres.h>             // wxXmlResource
#include <wx/statbmp.h>                // wxStaticBitmap
#include <wx/stattext.h>               // wxStaticText
#include <wx/listctrl.h>               // wxListCtrl

BEGIN_EVENT_TABLE(xSharedFilesPanel, wxPanel)
END_EVENT_TABLE()

xSharedFilesPanel::xSharedFilesPanel(wxWindow* aParent)
{
    wxXmlResource::Get()->LoadPanel(this, aParent, wxT("SHAREDFILES_PANEL"));

    XRCCTRL(*this, "SB_SHAREDFILES", wxStaticBitmap)->SetBitmap(wxBitmap(sharedfileslist_xpm));

    SessionRequests=XRCCTRL(*this, "ST_SESREQUESTS", wxStaticText);
    SessionAccepted=XRCCTRL(*this, "ST_SESACCEPTED", wxStaticText);
    SessionTransferred=XRCCTRL(*this, "ST_SESTRANSFERRED", wxStaticText);
    TotalRequests=XRCCTRL(*this, "ST_TOTREQUESTS", wxStaticText);
    TotalAccepted=XRCCTRL(*this, "ST_TOTACCEPTED", wxStaticText);
    TotalTransferred=XRCCTRL(*this, "ST_TOTTRANSFERRED", wxStaticText);

    SharedFilesListCtrl=XRCCTRL(*this, "LC_SHAREDFILES", wxListCtrl);
    InitListCtrl();
}

xSharedFilesPanel::~xSharedFilesPanel()
{
}

void xSharedFilesPanel::InitListCtrl()
{
    SharedFilesListCtrl->InsertColumn(0, wxT("File Name"));
    SharedFilesListCtrl->InsertColumn(1, wxT("Size"));
    SharedFilesListCtrl->InsertColumn(2, wxT("Type"));
    SharedFilesListCtrl->InsertColumn(3, wxT("Priority"));
    SharedFilesListCtrl->InsertColumn(4, wxT("File ID"));
    SharedFilesListCtrl->InsertColumn(5, wxT("Requests"));
    SharedFilesListCtrl->InsertColumn(6, wxT("Accepted Requests"));
    SharedFilesListCtrl->InsertColumn(7, wxT("Transfered Data"));
    SharedFilesListCtrl->InsertColumn(8, wxT("Shared Parts"));
    SharedFilesListCtrl->InsertColumn(9, wxT("Folder"));
    SharedFilesListCtrl->InsertColumn(10, wxT("Complete Sources"));
    SharedFilesListCtrl->InsertColumn(11, wxT("Shared eD2K|Kad"));
}
