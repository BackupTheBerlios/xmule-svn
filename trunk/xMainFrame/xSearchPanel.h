/**
 * xSearchPanel.h
 * xMule's Search Panel
 */

#ifndef _XSEARCHPANEL_H_
#define _XSEARCHPANEL_H_

#include <wx/panel.h>                  // wxPanel

class wxTextCtrl;
class wxCheckBox;
class wxChoice;
class wxButton;

class xSearchPanel: public wxPanel
{
public:
    xSearchPanel(wxWindow* aParent);
    ~xSearchPanel();

private:
    wxTextCtrl* SearchText;
    wxButton* SearchTextHistory;

    wxCheckBox* SearchUnicode;
    wxChoice* SearchType;
    wxChoice* SearchMethod;

    DECLARE_EVENT_TABLE()
};

#endif // _XSEARCHPANEL_H_
