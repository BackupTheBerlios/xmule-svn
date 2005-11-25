/**
 * xSharedFilesPanel.cpp
 * xMule's Shared Files Panel
 */

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
