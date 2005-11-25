/**
 * xOptionsDialog.cpp
 * xMule's preferences dialog class
 */

#include "xOptionsDialog.h"            // xOptionsDialog
#include "xOptionsPage.h"              // xOptionsPage
#include "xOptionsIcons.h"             // Icon XPM resources

#include <wx/button.h>                 // wxButton
#include <wx/imaglist.h>               // wxImageList
#include <wx/listctrl.h>               // wxListView
#include <wx/msgdlg.h>                 // wxMessageBox
#include <wx/sizer.h>                  // wxSizer
#include <wx/xrc/xmlres.h>             // wxXmlResource

const int ListViewId = 10000;

BEGIN_EVENT_TABLE(xOptionsDialog, wxDialog)
    EVT_LIST_ITEM_SELECTED(ListViewId, xOptionsDialog::OnPrefsListSelected )
//    EVT_CHECKBOX(XRCID("ID_BEEP"), PrefsDialog::OnClickedOK)
END_EVENT_TABLE()

xOptionsDialog::xOptionsDialog(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style)
    : wxDialog(parent, id, caption, pos, size, style)
{
    CurrentPage=NULL;
    MainSizer=NULL;
    MainListView=NULL;

    SetExtraStyle(GetExtraStyle() | wxWS_EX_BLOCK_EVENTS);

    CreateControls();
    Centre();

    wxSize MinSize = FindMinSize();
    SetSize(MinSize);
    SetSizeHints(MinSize);
    MainListView->Select(0); //Initially Select The First Item
    ShowSelectedPanel();
}

xOptionsDialog::~xOptionsDialog()
{
    for (unsigned int i=0; i < PrefsPages.size(); ++i)
    {
        delete PrefsPages[i];
    }
}

void xOptionsDialog::CreateControls()
{
    // Initialize all the pages
    PrefsPages.push_back(new xOptionsPage(0, wxT("GeneralPanel"),_("General")));
    PrefsPages.push_back(new xOptionsPage(1, wxT("DisplayPanel"),_("Display")));
    PrefsPages.push_back(new xOptionsPage(2, wxT("ConnectionPanel"),_("Connection")));
    PrefsPages.push_back(new xOptionsPage(3, wxT("ProxyPanel"), _("Proxy")));
    PrefsPages.push_back(new xOptionsPage(4, wxT("ServerPanel"), _("Server")));
    PrefsPages.push_back(new xOptionsPage(5, wxT("DirectoriesPanel"), _("Directories")));
    PrefsPages.push_back(new xOptionsPage(6, wxT("FilesPanel"), _("Files")));
    PrefsPages.push_back(new xOptionsPage(7, wxT("NotificationsPanel"), _("Notifications")));
    PrefsPages.push_back(new xOptionsPage(8, wxT("StatisticsPanel"), _("Statistics")));
    PrefsPages.push_back(new xOptionsPage(9, wxT("SecurityPanel"), _("Security")));
    PrefsPages.push_back(new xOptionsPage(10, wxT("WebInterfacePanel"), _("Web Interface")));

    xOptionsDialog* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);
    itemDialog1->SetAutoLayout(TRUE);
    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    MainSizer = itemBoxSizer3;
    itemBoxSizer2->Add(itemBoxSizer3, 1, wxGROW|wxALL, 5);
    wxImageList* PrefsImageList = new wxImageList(16,16);
    PrefsImageList->Add(wxIcon(general_xpm));
    PrefsImageList->Add(wxIcon(display_xpm));
    PrefsImageList->Add(wxIcon(connection_xpm));
    PrefsImageList->Add(wxIcon(proxy_xpm));
    PrefsImageList->Add(wxIcon(server_xpm));
    PrefsImageList->Add(wxIcon(directories_xpm));
    PrefsImageList->Add(wxIcon(files_xpm));
    PrefsImageList->Add(wxIcon(notifications_xpm));
    PrefsImageList->Add(wxIcon(statistics_xpm));
    PrefsImageList->Add(wxIcon(security_xpm));
    PrefsImageList->Add(wxIcon(webinterface_xpm));
    wxListView* itemListView = new wxListView( itemDialog1, ListViewId, wxDefaultPosition, wxSize(120, -1), wxLC_SINGLE_SEL|wxLC_REPORT|wxRAISED_BORDER|wxLC_NO_HEADER);
    MainListView=itemListView;
    itemListView->AssignImageList(PrefsImageList, wxIMAGE_LIST_SMALL);
    itemListView->InsertColumn(0, wxEmptyString, wxLIST_FORMAT_LEFT, itemListView->GetSize().GetWidth()-5);
    for (unsigned int i=0; i < PrefsPages.size(); ++i)
    {
        xOptionsPage* CurPage=PrefsPages.at(i);
        CurPage->LoadResourcePanel(this);
        itemListView->InsertItem(i, CurPage->GetListName(), CurPage->GetImageIndex());
    }
    itemBoxSizer3->Add(itemListView, 0, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer6, 0, wxGROW|wxALL, 5);
    itemBoxSizer6->Add(5, 5, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton8 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer6->Add(itemButton8, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton9 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer6->Add(itemButton9, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemBoxSizer6->Add(5, 5, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);
}

void xOptionsDialog::OnPrefsListSelected( wxListEvent& event )
{
    ShowSelectedPanel(event.GetIndex());
    event.Skip();
}

void xOptionsDialog::ShowSelectedPanel(unsigned long ItemIndex)
{
    if (ItemIndex > (PrefsPages.size()-1) || PrefsPages[ItemIndex] == CurrentPage)
        return;
    if (CurrentPage)
    {
        MainSizer->Detach(CurrentPage->GetPanel());
        CurrentPage->GetPanel()->Hide();
    }
    CurrentPage=PrefsPages[ItemIndex];
    if (CurrentPage->GetPanel())
    {
        MainSizer->Add(CurrentPage->GetPanel(), 1, wxGROW|wxALL, 5);
        CurrentPage->GetPanel()->Show();
        MainSizer->Layout();
    }
}

void xOptionsDialog::OnClickedOK(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(wxT("You clicked OK! :)"));
}

wxSize xOptionsDialog::FindMinSize()
{
    int MinWidth, MinHeight;
    MinWidth=MinHeight=0;
    for (unsigned int i=0; i < PrefsPages.size(); ++i)
    {
        ShowSelectedPanel(i);
        Fit();
        Layout();
        wxSize CurSize = GetSize();
        if (CurSize.GetWidth() > MinWidth)
        {
            MinWidth = CurSize.GetWidth();
        }
        if (CurSize.GetHeight() > MinHeight)
        {
            MinHeight = CurSize.GetHeight();
        }
    }
    return wxSize(MinWidth, MinHeight);
}
