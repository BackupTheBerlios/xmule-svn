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
