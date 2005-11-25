/**
 * xSearchPanel.cpp
 * xMule's Search Panel
 */

#include "xSearchPanel.h"              // xSearchPanel
#include "xResources.h"                // IDs and XPMs

#include <wx/xrc/xmlres.h>             // wxXmlResource
#include <wx/statbmp.h>                // wxStaticBitmap
#include <wx/textctrl.h>               // wxTextCtrl
#include <wx/checkbox.h>               // wxCheckBox
#include <wx/choice.h>                 // wxChoice
#include <wx/button.h>                 // wxButton
#include <wx/font.h>                   // wxFont

BEGIN_EVENT_TABLE(xSearchPanel, wxPanel)
END_EVENT_TABLE()

xSearchPanel::xSearchPanel(wxWindow* aParent)
{
    wxXmlResource::Get()->LoadPanel(this, aParent, wxT("SEARCH_PANEL"));
    SearchText=XRCCTRL(*this, "ID_NAMETEXT", wxTextCtrl);
    SearchUnicode=XRCCTRL(*this, "ID_UNICODECHECK", wxCheckBox);
    SearchType=XRCCTRL(*this, "ID_TYPECHOICE", wxChoice);
    SearchMethod=XRCCTRL(*this, "ID_METHODCHOICE", wxChoice);

    XRCCTRL(*this, "SB_RESULTS", wxStaticBitmap)->SetBitmap(wxBitmap(searchresults_xpm));

#ifdef __WXMSW__
    SearchTextHistory=XRCCTRL(*this, "ID_NAMEBUTTON", wxButton);
    wxFont SymbolFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Marlett"));
    SearchTextHistory->SetFont(SymbolFont);
    SearchTextHistory->SetLabel(wxT("6"));
#endif // __WXMSW__
}

xSearchPanel::~xSearchPanel()
{
}
