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

#include "xKadPanel.h"                 // xKadPanel
#include "xResources.h"                // IDs and XPMs

#include <wx/xrc/xmlres.h>             // wxXmlResource
#include <wx/statbmp.h>                // wxStaticBitmap
#include <wx/listctrl.h>               // wxListCtrl

BEGIN_EVENT_TABLE(xKadPanel, wxPanel)
END_EVENT_TABLE()

xKadPanel::xKadPanel(wxWindow* aParent)
{
    wxXmlResource::Get()->LoadPanel(this, aParent, wxT("KAD_PANEL"));

    ContactsLabel=XRCCTRL(*this, "ST_CONTACTS", wxStaticText);
    SearchesLabel=XRCCTRL(*this, "ST_SEARCHES", wxStaticText);
    ContactsListCtrl=XRCCTRL(*this, "LC_CONTACTS", wxListCtrl);
    SearchesListCtrl=XRCCTRL(*this, "LC_SEARCHES", wxListCtrl);

    XRCCTRL(*this, "SB_CONTACTS", wxStaticBitmap)->SetBitmap(wxBitmap(contacts_xpm));
    XRCCTRL(*this, "SB_SEARCHES", wxStaticBitmap)->SetBitmap(wxBitmap(currentsearches_xpm));

    InitListCtrls();
}

xKadPanel::~xKadPanel()
{
}

void xKadPanel::InitListCtrls()
{
    ContactsListCtrl->InsertColumn(0, wxT("ID"));
    ContactsListCtrl->InsertColumn(1, wxT("Type"));
    ContactsListCtrl->InsertColumn(2, wxT("Distance"));

    SearchesListCtrl->InsertColumn(0, wxT("Number"));
    SearchesListCtrl->InsertColumn(1, wxT("Key"));
    SearchesListCtrl->InsertColumn(2, wxT("Type"));
    SearchesListCtrl->InsertColumn(3, wxT("Name"));
    SearchesListCtrl->InsertColumn(4, wxT("Status"));
    SearchesListCtrl->InsertColumn(5, wxT("Load"));
    SearchesListCtrl->InsertColumn(6, wxT("Packets Sent"));
    SearchesListCtrl->InsertColumn(7, wxT("Responses"));
}
