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

#ifndef _XAPP_H_
#define _XAPP_H_

#ifdef __WXMSW__
    #include <msvc/wx/setup.h>         // Library file names
#endif

#include <wx/app.h>                    // wxApp

class xMainFrame;

class xApp : public wxApp
{
public:
    virtual bool OnInit();
    virtual int OnExit();

    void Log(const wxString& toLog);
    xMainFrame* GetMainFrame() { return MainFrame; }
private:
    bool InitResources();

    xMainFrame* MainFrame;
};

DECLARE_APP(xApp)

#endif // _XAPP_H_
