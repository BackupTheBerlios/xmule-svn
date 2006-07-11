/**
 * xMuleApp.cpp
 */

#include "xApp.h"                      // xApp
#include "xCore/xSafeFile.h"           // xSafeFile
#include "xCore/xServer.h"             // xServer
#include "xMainFrame/xMainFrame.h"     // xMainFrame
#include "xMainFrame/xServersPanel.h"  // xServersPanel
#include "xMainFrame/XPMs/SplashScreen.xpm"    // Splash Screen Image

#include <wx/bitmap.h>                 // wxBitmap
#include <wx/filefn.h>                 // wxFileExists
#include <wx/listctrl.h>               // wxListCtrl
#include <wx/msgdlg.h>                 // wxMessageBox
#include <wx/splash.h>                 // wxSplashScreen
#include <wx/tooltip.h>                // wxToolTip
#include <wx/xrc/xmlres.h>             // wxXmlResource

#define MET_HEADER 0x0E
bool AddServerMetToList(const wxString& strFile)
{
    xApp* theApp = &wxGetApp();
    wxListCtrl* ServersListCtrl = theApp->GetMainFrame()->GetServersPanel()->GetServersListCtrl();
    if (!wxFileExists(strFile))
    {
        return false;
    }
    xSafeBufferedFile servermet;
    if (!servermet.Open(strFile, wxT("rb")))
    {
        return false;
    }
    wxUint8 version = servermet.ReadUInt8();
    if (version != 0xE0 && version != MET_HEADER)
    {
        servermet.Close();
        return false;
    }
    wxUint32 fservercount = servermet.ReadUInt32();

    ServerMet_Struct sbuffer;
    wxUint32 iAddCount = 0;
    ServersListCtrl->Freeze();
    for (wxUint32 j = 0; j < fservercount; j++)
    {
        // get server
        servermet.Read(&sbuffer, sizeof(ServerMet_Struct));
        xServer* newserver = new xServer(&sbuffer);

        // add tags
        for (wxUint32 i = 0; i < sbuffer.tagcount; i++)
        {
            newserver->AddTagFromFile(&servermet);
        }

        // set listname for server
        if (newserver->GetListName().empty())
        {
            wxString listname;
            listname.Printf(wxT("Server %s"), newserver->GetAddress());
            newserver->SetListName(listname);
        }
        iAddCount++;

        //Insert to the list
        ServersListCtrl->InsertItem(j, newserver->GetListName(), 0);
        ServersListCtrl->SetItem(j, 1, wxString::Format(wxT("%s : %i"), newserver->GetAddress(), newserver->GetPort()));
        ServersListCtrl->SetItem(j, 2, newserver->GetDescription());
        if (newserver->GetPing())
        {
            ServersListCtrl->SetItem(j, 3, wxString::Format(wxT("%i"), newserver->GetPing()));
        }
        if (newserver->GetUsers())
        {
            ServersListCtrl->SetItem(j, 4, wxString::Format(wxT("%i"), newserver->GetUsers()));
        }
        if (newserver->GetMaxUsers())
        {
            ServersListCtrl->SetItem(j, 5, wxString::Format(wxT("%i"), newserver->GetMaxUsers()));
        }
        if (newserver->GetFiles())
        {
            ServersListCtrl->SetItem(j, 6, wxString::Format(wxT("%i"), newserver->GetFiles()));
        }
        switch (newserver->GetPreferences())
        {
            case SRV_PR_LOW:
                ServersListCtrl->SetItem(j, 7, wxT("Low"));
                break;
            case SRV_PR_NORMAL:
                ServersListCtrl->SetItem(j, 7, wxT("Normal"));
                break;
            case SRV_PR_HIGH:
                ServersListCtrl->SetItem(j, 7, wxT("High"));
                break;
            default:
                ServersListCtrl->SetItem(j, 7, wxT("No Pref"));
        }
        ServersListCtrl->SetItem(j, 8, wxString::Format(wxT("%i"), newserver->GetFailedCount()));
        if (newserver->IsStaticMember())
            ServersListCtrl->SetItem(j, 9, wxT("Yes"));
        else
            ServersListCtrl->SetItem(j, 9, wxT("No"));
        if (newserver->GetSoftFiles())
        {
            ServersListCtrl->SetItem(j, 10, wxString::Format(wxT("%i"), newserver->GetSoftFiles()));
        }
        if (newserver->GetHardFiles())
        {
            ServersListCtrl->SetItem(j, 11, wxString::Format(wxT("%i"), newserver->GetHardFiles()));
        }
        ServersListCtrl->SetItem(j, 12, newserver->GetVersion());
        if (newserver->GetLowIDUsers())
        {
            ServersListCtrl->SetItem(j, 13, wxString::Format(wxT("%i"), newserver->GetLowIDUsers()));
        }
        delete newserver;
    }
    ServersListCtrl->Thaw();
    servermet.Close();
    wxString toShow;
    toShow << wxT("Servers (") << iAddCount << wxT(")");
    theApp->GetMainFrame()->SetServersLabel(toShow);
    return true;
}

IMPLEMENT_APP(xApp)

const wxString AppName = wxT("xMule");

bool xApp::OnInit()
{
    if (!InitResources()) // Something went wrong with resources loading
    {
        return false;
    }
    SetAppName(AppName);

    wxToolTip::Enable(true); // Enable tooltips globally
    wxToolTip::SetDelay(500);

    wxBitmap SplashScreenImage(SplashScreen_xpm);
    if (SplashScreenImage.Ok())
    {
        wxSplashScreen* Splash = new wxSplashScreen(SplashScreenImage, wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_TIMEOUT, 3000, NULL, wxID_ANY);
    }
    MainFrame = new xMainFrame(); // Create the main frame
    SetTopWindow(MainFrame);
    MainFrame->Show();
    AddServerMetToList(wxT("server.met"));

    // Everything is alright and we are ready-to-go :)
    return true;
}

int xApp::OnExit()
{
    return true;
}

bool xApp::InitResources()
{
    //Check that the XRC resources are available
    if (!wxFileExists(wxT("xMainFrame.xrc")) && !wxFileExists(wxT("../xMainFrame.xrc")))
    {
        wxMessageBox(wxT("xMainFrame.xrc could not be found. Shuting down!"));
        return false; // Terminate app
    }
    if (!wxFileExists(wxT("xOptions.xrc")) && !wxFileExists(wxT("../xOptions.xrc")))
    {
        wxMessageBox(wxT("xOptions.xrc could not be found. Shuting down!"));
        return false; // Terminate app
    }

    // Load xMainFrame.xrc
    wxXmlResource::Get()->InitAllHandlers();
    if (wxFileExists(wxT("xMainFrame.xrc")))
    {
        wxXmlResource::Get()->Load(wxT("xMainFrame.xrc"));
    }
    else
    {
        wxXmlResource::Get()->Load(wxT("../xMainFrame.xrc"));
    }

    // Load xOptions.xrc
    if (wxFileExists(wxT("xOptions.xrc")))
    {
        wxXmlResource::Get()->Load(wxT("xOptions.xrc"));
    }
    else
    {
        wxXmlResource::Get()->Load(wxT("../xOptions.xrc"));
    }
    return true;
}

void xApp::Log(const wxString& toLog)
{
    GetMainFrame()->SetStatusText(toLog);
}
