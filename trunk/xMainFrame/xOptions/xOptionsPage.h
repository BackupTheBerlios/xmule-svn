#ifndef _XOPTIONSPAGE_
#define _XOPTIONSPAGE_

#include <wx/defs.h>                   // Needed for wxWidgets types
#include <wx/panel.h>                  // Needed for wxPanel
#include <wx/gdicmn.h>                 // Needed for wxSize
#include <wx/xrc/xmlres.h>             // Needed for wxXmlResource

class wxString;
class wxWindow;

class xOptionsPage
{
public:
    xOptionsPage(wxUint8 const& aImageIndex, wxString const& aPanelResName, wxString const& aListName)
    {
        ListName=aListName;
        ImageIndex=aImageIndex;
        PanelResName=aPanelResName;
        thePanel=NULL;
    }
    ~xOptionsPage() { DestroyCurrentPanel(); }

    void LoadResourcePanel(wxWindow* ParentWindow)
    {
        DestroyCurrentPanel();
        thePanel = wxXmlResource::Get()->LoadPanel(ParentWindow, PanelResName);
        thePanel->Hide();
    }
    wxUint8 GetImageIndex() const { return ImageIndex; }
    wxString GetListName() const
    {
        return ListName;
    }
    wxPanel* GetPanel() const { return thePanel; }

private:
    void DestroyCurrentPanel() { if (thePanel) { thePanel->Destroy(); } }

    wxUint8 ImageIndex;
    wxString ListName;  // The name to appear on the preferences listbox
    wxString PanelResName;
    wxPanel* thePanel;  // Pointer to the wxPanel itself
};

#endif // _XOPTIONSPAGE_
