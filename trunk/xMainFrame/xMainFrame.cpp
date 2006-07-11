/**
 * xMainFrame.cpp
 * xMule's main frame class
 */

#include "xMainFrame.h"                // xMainFrame
#include "xOptions/xOptionsDialog.h"   // xOptionsDialog
#include "xResources.h"                // IDs and XPMs for toolbar
#include "xKadPanel.h"                 // xKadPanel
#include "xServersPanel.h"             // xServersPanel
#include "xTransfersPanel.h"           // xTransfersPanel
#include "xSearchPanel.h"              // xSearchPanel
#include "xSharedFilesPanel.h"         // xSharedFilesPanel

#include <wx/icon.h>                   // wxIcon
#include <wx/sizer.h>                  // wxSizer
#include <wx/toolbar.h>                // wxToolBar

BEGIN_EVENT_TABLE(xMainFrame, wxFrame)
    EVT_TOOL_RANGE(TB_KAD, TB_STATISTICS, xMainFrame::OnSwitchPanel)
    EVT_TOOL(TB_OPTIONS, xMainFrame::OnClickedOptions) // Clicked options
END_EVENT_TABLE()

xMainFrame::xMainFrame() : wxFrame(NULL, wxID_ANY, MainFrameTitle)
{
    OptionsDialog=NULL;
    CurrentPanel=NULL;

    SetIcon(wxIcon(xmule_xpm));

    CreateToolBar();
    CreateStatusBar();
    SetStatusBarPane(-1);
    CreateControls();

    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);

    wxSize TempSize(800,600);
    SetSize(TempSize);
    Center();
}

xMainFrame::~xMainFrame()
{
}

void xMainFrame::CreateControls()
{
    // Create the main sizer of the xMainFrame
    wxBoxSizer* MainSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(MainSizer);

    // Create the Kad panel
    KadPanel = new xKadPanel(this);
    KadPanel->Hide();
    MainSizer->Add(KadPanel, 1, wxGROW, 0);

    // Create the Servers panel
    ServersPanel = new xServersPanel(this);
    MainSizer->Add(ServersPanel, 1, wxGROW, 0);

    // Create the Transfers panel
    TransfersPanel = new xTransfersPanel(this);
    TransfersPanel->Hide();
    MainSizer->Add(TransfersPanel, 1, wxGROW, 0);

    // Create the Search panel
    SearchPanel = new xSearchPanel(this);
    SearchPanel->Hide();
    MainSizer->Add(SearchPanel, 1, wxGROW, 0);

    // Create the Shared Files panel
    SharedFilesPanel = new xSharedFilesPanel(this);
    SharedFilesPanel->Hide();
    MainSizer->Add(SharedFilesPanel, 1, wxGROW, 0);

    CurrentPanel=ServersPanel;
}

void xMainFrame::CreateToolBar()
{
    wxToolBar* myToolBar = new wxToolBar( this, ID_MAINTOOLBAR, wxDefaultPosition, wxDefaultSize, wxTB_FLAT|wxTB_HORIZONTAL|wxTB_TEXT|wxTB_NODIVIDER );
    myToolBar->SetToolBitmapSize(wxSize(32, 32));
    myToolBar->AddTool(TB_CONNECT, wxT("Connect"), wxBitmap(connect_xpm), _T(""), wxITEM_NORMAL);
    myToolBar->AddSeparator();
    myToolBar->AddTool(TB_KAD, wxT("Kad"), wxBitmap(kad_xpm), _T(""), wxITEM_RADIO);
    myToolBar->AddTool(TB_SERVERS, wxT("Servers"), wxBitmap(servers_xpm), _T(""), wxITEM_RADIO);
    myToolBar->AddTool(TB_TRANSFERS, wxT("Transfers"), wxBitmap(transfers_xpm), _T(""), wxITEM_RADIO);
    myToolBar->AddTool(TB_SEARCH, wxT("Search"), wxBitmap(search_xpm), _T(""), wxITEM_RADIO);
    myToolBar->AddTool(TB_SHAREDFILES, wxT("Shared Files"), wxBitmap(sharedfiles_xpm), _T(""), wxITEM_RADIO);
    myToolBar->AddTool(TB_STATISTICS, wxT("Statistics"), wxBitmap(statistics_xpm), _T(""), wxITEM_RADIO);
    myToolBar->AddSeparator();
    myToolBar->AddTool(TB_OPTIONS, wxT("Options"), wxBitmap(options_xpm), _T(""), wxITEM_NORMAL);
    myToolBar->AddTool(TB_TOOLS, wxT("Tools"), wxBitmap(tools_xpm), _T(""), wxITEM_NORMAL);
    myToolBar->Realize();
    myToolBar->ToggleTool(TB_SERVERS, true);
    SetToolBar(myToolBar);
}

wxSize xMainFrame::FindMinSize()
{
/*    int MinWidth, MinHeight;
    MinWidth=MinHeight=0;
    for (unsigned int i=0; i < PrefsPages.size(); ++i)
    {
        ShowSelectedPanel(i);
        Fit();
        Layout();
        wxSize CurSize = GetSize();
        if (CurSize.GetWidth() > MinWidth)
        {
            MinWidth = CurSize.GetWidth();
        }
        if (CurSize.GetHeight() > MinHeight)
        {
            MinHeight = CurSize.GetHeight();
        }
    }
    return wxSize(MinWidth, MinHeight);*/
    return wxSize();
}

void xMainFrame::OnClickedOptions(wxCommandEvent& WXUNUSED(event))
{
    if (!OptionsDialog)
    {
        OptionsDialog = new xOptionsDialog(this);
    }
    OptionsDialog->ShowModal();
}

void xMainFrame::OnSwitchPanel(wxCommandEvent& event)
{
    switch (event.GetId())
    {
    case TB_KAD:
        {
        if (CurrentPanel==KadPanel)
        {
            break;
        }
        CurrentPanel->Hide();
        KadPanel->Show();
        CurrentPanel=KadPanel;
        break;
        }
    case TB_SERVERS:
        {
        if (CurrentPanel==ServersPanel)
        {
            break;
        }
        CurrentPanel->Hide();
        ServersPanel->Show();
        CurrentPanel=ServersPanel;
        break;
        }
    case TB_TRANSFERS:
        {
        if (CurrentPanel==TransfersPanel)
        {
            break;
        }
        CurrentPanel->Hide();
        TransfersPanel->Show();
        CurrentPanel=TransfersPanel;
        break;
        }
    case TB_SEARCH:
        {
        if (CurrentPanel==SearchPanel)
        {
            break;
        }
        CurrentPanel->Hide();
        SearchPanel->Show();
        CurrentPanel=SearchPanel;
        break;
        }
    case TB_SHAREDFILES:
        {
        if (CurrentPanel==SharedFilesPanel)
        {
            break;
        }
        CurrentPanel->Hide();
        SharedFilesPanel->Show();
        CurrentPanel=SharedFilesPanel;
        break;
        }
    default:
        {
        break;
        }
    }
    Layout();
}

void xMainFrame::SetServersLabel(const wxString& toSet)
{
    GetServersPanel()->SetServersLabel(toSet);
}
