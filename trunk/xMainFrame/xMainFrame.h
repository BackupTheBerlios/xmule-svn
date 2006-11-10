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
