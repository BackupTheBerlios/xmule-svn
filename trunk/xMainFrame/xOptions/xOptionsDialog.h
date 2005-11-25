/**
 * xOptionsDialog.h
 * xMule's options dialog class
 */

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
