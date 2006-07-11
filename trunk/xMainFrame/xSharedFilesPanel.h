/**
 * xSharedFilesPanel.h
 * xMule's Shared Files Panel
 */

#ifndef _XSHAREDFILESPANEL_H_
#define _XSHAREDFILESPANEL_H_

#include <wx/panel.h>                  // wxPanel

class wxStaticText;
class wxListCtrl;

class xSharedFilesPanel: public wxPanel
{
public:
    xSharedFilesPanel(wxWindow* aParent);
    ~xSharedFilesPanel();

private:
    wxStaticText* SessionRequests;
    wxStaticText* SessionAccepted;
    wxStaticText* SessionTransferred;
    wxStaticText* TotalRequests;
    wxStaticText* TotalAccepted;
    wxStaticText* TotalTransferred;
    wxListCtrl* SharedFilesListCtrl;

    void InitListCtrl();

    DECLARE_EVENT_TABLE()
};

#endif // _XSHAREDFILESPANEL_H_
