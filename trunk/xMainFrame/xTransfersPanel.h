/**
 * xTransfersPanel.h
 * xMule's Transfers Panel
 */

#ifndef _XTRANSFERSPANEL_H_
#define _XTRANSFERSPANEL_H_

#include <wx/panel.h>                  // wxPanel

class wxNotebook;
class wxListCtrl;

class xTransfersPanel: public wxPanel
{
public:
    xTransfersPanel(wxWindow* aParent);
    ~xTransfersPanel();

    wxNotebook* GetCategoriesNotebook() { return CategoriesNotebook; }

private:
    void InitListCtrls();

    wxNotebook* CategoriesNotebook;
    wxListCtrl* DownloadListCtrl;
    wxListCtrl* UploadListCtrl;

    DECLARE_EVENT_TABLE()
};

#endif // _XTRANSFERSPANEL_H_
