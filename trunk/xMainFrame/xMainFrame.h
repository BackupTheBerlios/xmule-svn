/**
 * xMainFrame.h
 * xMule's main frame class
 */

#ifndef _XMAINFRAME_H_
#define _XMAINFRAME_H_

#include <wx/frame.h>                  // wxFrame
#include <wx/string.h>                 // wxString
#include <wx/wxchar.h>                 // wxT()

class wxPanel;
class xOptionsDialog;
class xKadPanel;
class xServersPanel;
class xTransfersPanel;
class xSearchPanel;
class xSharedFilesPanel;

// Main frame's title
const wxString MainFrameTitle = wxT("xMule2 Alpha");

class xMainFrame: public wxFrame
{
public:
    xMainFrame();
    ~xMainFrame();

    xKadPanel* GetKadPanel() { return KadPanel; }
    xServersPanel* GetServersPanel() { return ServersPanel; }
    xTransfersPanel* GetTransfersPanel() { return TransfersPanel; }
    xSearchPanel* GetSearchPanel() { return SearchPanel; }
    xSharedFilesPanel* GetSharedFilesPanel() { return SharedFilesPanel; }

    void SetServersLabel(const wxString& toSet);

protected:
    void OnClickedOptions(wxCommandEvent& event);
    void OnSwitchPanel(wxCommandEvent& event);

private:
    void CreateControls(); // Controls creation
    void CreateToolBar();  // ToolBar creation
    wxSize FindMinSize();

    xKadPanel* KadPanel;
    xServersPanel* ServersPanel;
    xTransfersPanel* TransfersPanel;
    xSearchPanel* SearchPanel;
    xSharedFilesPanel* SharedFilesPanel;

    wxPanel* CurrentPanel;
    xOptionsDialog* OptionsDialog;

    DECLARE_EVENT_TABLE()
};

#endif // _XMAINFRAME_H_
