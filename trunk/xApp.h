/**
 * xApp - xMule's Main Application Class
 */

#ifndef _XAPP_H_
#define _XAPP_H_

#include <wx/app.h>                    // wxApp
#include <msvc/wx/setup.h>             // Library Names! :)

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
