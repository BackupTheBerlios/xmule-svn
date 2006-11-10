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

#ifndef _XOPTIONSDIALOG_H_
#define _XOPTIONSDIALOG_H_

#include <wx/dialog.h>                 // wxDialog
#include <wx/intl.h>                   // _()
#include <wx/string.h>                 // wxString
#include <vector>                      // std::vector

class wxBitmap;
class wxListEvent;
class wxListView;
class xOptionsPage;
class wxSizer;

// Default values
const wxString WindowTitle = _("Options");
const long WindowStyle = wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxDOUBLE_BORDER;

class xOptionsDialog: public wxDialog
{
public:
    xOptionsDialog(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& caption = WindowTitle, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = WindowStyle);
    ~xOptionsDialog();

    void CreateControls(); // Creates the controls and sizers

protected:
    void OnPrefsListSelected(wxListEvent& event);
    void OnClickedOK(wxCommandEvent& event);

private:
    wxSize FindMinSize();
    void ShowSelectedPanel(unsigned long ItemIndex=0);

    std::vector<xOptionsPage*> PrefsPages;
    xOptionsPage* CurrentPage;
    wxSizer* MainSizer;
    wxListView* MainListView;

    DECLARE_EVENT_TABLE()
};

#endif // _XOPTIONSDIALOG_H_
