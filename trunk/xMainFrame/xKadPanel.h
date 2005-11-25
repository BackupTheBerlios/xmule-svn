/**
 * xKadPanel.h
 * xMule's Kad Panel
 */

#ifndef _XKADPANEL_H_
#define _XKADPANEL_H_

#include <wx/panel.h>                  // wxPanel
#include <wx/string.h>                 // wxString
#include <wx/wxchar.h>                 // wxT()
#include <wx/stattext.h>               // wxStaticText

class wxListCtrl;

class xKadPanel: public wxPanel
{
public:
    xKadPanel(wxWindow* aParent);
    ~xKadPanel();

    void SetContactsLabel(const wxString& newLabel) { ContactsLabel->SetLabel(newLabel); }
    void SetSearchesLabel(const wxString& newLabel) { SearchesLabel->SetLabel(newLabel); }

private:
    void InitListCtrls();

    wxStaticText* ContactsLabel;
    wxListCtrl* ContactsListCtrl;
    wxStaticText* SearchesLabel;
    wxListCtrl* SearchesListCtrl;

    DECLARE_EVENT_TABLE()
};

#endif // _XKADPANEL_H_
