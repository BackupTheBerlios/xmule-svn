/**
 * xTransfersPanel.cpp
 * xMule's Transfers Panel
 */

#include "xTransfersPanel.h"           // xTransfersPanel
#include "xResources.h"                // IDs and XPMs
#include "xAdvListCtrl.h"              // xAdvListCtrl

#include <wx/listctrl.h>               // wxListCtrl
#include <wx/notebook.h>               // wxNotebook
#include <wx/sizer.h>                  // wxBoxSizer
#include <wx/splitter.h>               // wxSplitterWindow
#include <wx/toolbar.h>                // wxToolBar
#include <wx/xrc/xmlres.h>             // wxXmlResource

BEGIN_EVENT_TABLE(xTransfersPanel, wxPanel)
END_EVENT_TABLE()

xTransfersPanel::xTransfersPanel(wxWindow* aParent) : wxPanel(aParent)
{
    wxBoxSizer* MainSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(MainSizer);
    wxBoxSizer* ToolbarsSizer = new wxBoxSizer(wxHORIZONTAL);
    MainSizer->Add(ToolbarsSizer, 0, wxGROW|wxRIGHT|wxLEFT, 10);

    // First ToolBar
    wxToolBar* SwitchToolBar = new wxToolBar( this, ID_SWITCHTOOLBAR, wxDefaultPosition, wxDefaultSize, wxTB_FLAT|wxTB_HORIZONTAL|wxTB_TEXT|wxTB_NODIVIDER|wxTB_HORZ_LAYOUT );
    SwitchToolBar->SetBackgroundColour(GetBackgroundColour());
    SwitchToolBar->SetToolBitmapSize(wxSize(16, 16));
    SwitchToolBar->AddTool(ID_SWITCH1, wxT("Downloads (0)                    "), wxBitmap(downloads_xpm), _T(""), wxITEM_NORMAL);
    SwitchToolBar->Realize();
    ToolbarsSizer->Add(SwitchToolBar, 0, wxALIGN_CENTER_VERTICAL|wxALL, 0);

    // Second ToolBar
    wxToolBar* ViewsToolBar = new wxToolBar( this, ID_VIEWSTOOLBAR, wxDefaultPosition, wxDefaultSize, wxTB_FLAT|wxTB_HORIZONTAL|wxTB_NODIVIDER );
    ViewsToolBar->SetBackgroundColour(GetBackgroundColour());
    ViewsToolBar->SetToolBitmapSize(wxSize(16, 16));
    ViewsToolBar->AddTool(ID_SPLITWINDOW, _T(""), wxBitmap(splitwindow_xpm), _T("Split Window"), wxITEM_RADIO);
    ViewsToolBar->AddTool(ID_DOWNLOADS, _T(""), wxBitmap(downloads_xpm), _T("Downloads"), wxITEM_RADIO);
    ViewsToolBar->AddTool(ID_UPLOADING, _T(""), wxBitmap(uploading_xpm), _T("Uploading"), wxITEM_RADIO);
    ViewsToolBar->AddTool(ID_DOWNLOADING, _T(""), wxBitmap(downloading_xpm), _T("Downloading"), wxITEM_RADIO);
    ViewsToolBar->AddTool(ID_ONQUEUE, _T(""), wxBitmap(onqueue_xpm), _T("On Queue"), wxITEM_RADIO);
    ViewsToolBar->AddTool(ID_KNOWNCLIENTS, _T(""), wxBitmap(knownclients_xpm), _T("Known Clients"), wxITEM_RADIO);
    ViewsToolBar->Realize();
    ToolbarsSizer->Add(ViewsToolBar, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxSplitterWindow* Splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3DSASH|wxSP_LIVE_UPDATE|wxNO_BORDER);
    MainSizer->Add(Splitter, 1, wxGROW|wxLEFT|wxRIGHT|wxBOTTOM, 10);
    Layout();
    DownloadListCtrl = new xAdvListCtrl(Splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_VIRTUAL);
    UploadListCtrl = new wxListCtrl(Splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
    Splitter->SplitHorizontally(DownloadListCtrl, UploadListCtrl);
    Splitter->SetMinimumPaneSize(1);

    InitListCtrls();
}

xTransfersPanel::~xTransfersPanel()
{
}

void xTransfersPanel::InitListCtrls()
{
    DownloadListCtrl->InsertColumn(0, wxT("File Name"));
    DownloadListCtrl->InsertColumn(1, wxT("Size"));
    DownloadListCtrl->InsertColumn(2, wxT("Completed"));
    DownloadListCtrl->InsertColumn(3, wxT("Speed"));
    DownloadListCtrl->InsertColumn(4, wxT("Progress"));
    DownloadListCtrl->InsertColumn(5, wxT("Sources"));
    DownloadListCtrl->InsertColumn(6, wxT("Priority"));
    DownloadListCtrl->InsertColumn(7, wxT("Status"));
    DownloadListCtrl->InsertColumn(8, wxT("Remaining"));

    UploadListCtrl->InsertColumn(0, wxT("User Name"));
    UploadListCtrl->InsertColumn(1, wxT("File"));
    UploadListCtrl->InsertColumn(2, wxT("Speed"));
    UploadListCtrl->InsertColumn(3, wxT("Transferred"));
    UploadListCtrl->InsertColumn(4, wxT("Waited"));
    UploadListCtrl->InsertColumn(5, wxT("Upload Time"));
    UploadListCtrl->InsertColumn(6, wxT("Status"));
    UploadListCtrl->InsertColumn(7, wxT("Obtained Parts"));
}
