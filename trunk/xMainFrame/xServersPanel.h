/**
 * xServersPanel.h
 * xMule's Servers Panel
 */

#ifndef _XSERVERSPANEL_H_
#define _XSERVERSPANEL_H_

#include <wx/panel.h>                  // wxPanel
#include <wx/string.h>                 // wxString
#include <wx/stattext.h>               // wxStaticText

class wxListCtrl;
class wxImageList;

class xServersPanel: public wxPanel
{
public:
    xServersPanel(wxWindow* aParent);
    ~xServersPanel();

    void SetServersLabel(const wxString& newLabel) { ServersLabel->SetLabel(newLabel); }
    wxListCtrl* GetServersListCtrl() { return ServersListCtrl; }

private:
    void InitListCtrl();

    wxStaticText* ServersLabel;
    wxListCtrl* ServersListCtrl;
    wxImageList* ListCtrlImages;
    wxImageList* NoteBookImages;

    DECLARE_EVENT_TABLE()
};

#endif // _XSERVERSPANEL_H_
