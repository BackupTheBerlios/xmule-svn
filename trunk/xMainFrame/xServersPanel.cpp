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

#include "xServersPanel.h"             // xServersPanel

// XPM Images used in this panel
#include "XPMs/ServersPanel/Servers.xpm"
#include "XPMs/ServersPanel/ServerInfo.xpm"
#include "XPMs/ServersPanel/Log.xpm"
#include "XPMs/ServersPanel/Server.xpm"

#include <wx/xrc/xmlres.h>             // wxXmlResource
#include <wx/statbmp.h>                // wxStaticBitmap
#include <wx/listctrl.h>               // wxListCtrl
#include <wx/imaglist.h>               // wxImageList
#include <wx/icon.h>                   // wxIcon
#include <wx/notebook.h>               // wxNotebook
#include <wx/splitter.h>               // wxSplitterWindow

BEGIN_EVENT_TABLE(xServersPanel, wxPanel)
END_EVENT_TABLE()

xServersPanel::xServersPanel(wxWindow* aParent)
{
    if (!wxXmlResource::Get()->LoadPanel(this, aParent, wxT("SERVERS_PANEL")))
    {
        return;
    }

    ServersLabel=XRCCTRL(*this, "ST_SERVERS", wxStaticText);
    ServersListCtrl=XRCCTRL(*this, "LC_SERVERS", wxListCtrl);

    XRCCTRL(*this, "SB_SERVERS", wxStaticBitmap)->SetBitmap(wxBitmap(servers_xpm));

    NoteBookImages=new wxImageList(16, 16);
    NoteBookImages->Add(wxIcon(serverinfo_xpm));
    NoteBookImages->Add(wxIcon(log_xpm));

    wxNotebook* LogsNotebook=XRCCTRL(*this, "LOGS_NOTEBOOK", wxNotebook);
    LogsNotebook->SetImageList(NoteBookImages);
    LogsNotebook->SetPageImage(0, 0);
    LogsNotebook->SetPageImage(1, 1);
    LogsNotebook->SetSelection(1);

    wxSplitterWindow* ServersSash=XRCCTRL(*this, "SERVERS_SASH", wxSplitterWindow);
    ServersSash->SetMinimumPaneSize(1);

    InitListCtrl();
}

xServersPanel::~xServersPanel()
{
    delete NoteBookImages;
    delete ListCtrlImages;
}

void xServersPanel::InitListCtrl()
{
    ServersListCtrl->InsertColumn(0, wxT("Server Name"));
    ServersListCtrl->InsertColumn(1, wxT("IP"));
    ServersListCtrl->InsertColumn(2, wxT("Description"));
    ServersListCtrl->InsertColumn(3, wxT("Ping"));
    ServersListCtrl->InsertColumn(4, wxT("Users"));
    ServersListCtrl->InsertColumn(5, wxT("Max Users"));
    ServersListCtrl->InsertColumn(6, wxT("Files"));
    ServersListCtrl->InsertColumn(7, wxT("Preference"));
    ServersListCtrl->InsertColumn(8, wxT("Failed"));
    ServersListCtrl->InsertColumn(9, wxT("Static"));
    ServersListCtrl->InsertColumn(10, wxT("Soft File Limit"));
    ServersListCtrl->InsertColumn(11, wxT("Hard File Limit"));
    ServersListCtrl->InsertColumn(12, wxT("Version"));
    ServersListCtrl->InsertColumn(13, wxT("Low ID"));

    // The image for each server in the list
    ListCtrlImages=new wxImageList(16, 16);
    ListCtrlImages->Add(wxIcon(server_xpm));
    ServersListCtrl->SetImageList(ListCtrlImages, wxIMAGE_LIST_SMALL);
}
