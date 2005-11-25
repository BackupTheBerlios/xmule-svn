/**
 * xKadPanel.cpp
 * xMule's Kad Panel
 */

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
