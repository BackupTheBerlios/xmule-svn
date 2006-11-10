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

#ifndef _XSERVER_H_
#define _XSERVER_H_

#include "xOpCodes.h"                  // xServer opcodes

#include <wx/defs.h>                   // wxWidgets definitions
#include <wx/string.h>                 // wxString

class xTag;
class xFileDataIO;

#define SRV_PR_LOW    2
#define SRV_PR_NORMAL 0
#define SRV_PR_HIGH   1

class xServer
{
public:
    xServer(const ServerMet_Struct* in_data);
    xServer(wxUint16 in_port, const wxChar* i_addr);
    xServer(const xServer* pOld);
    ~xServer();

    bool AddTagFromFile(xFileDataIO* servermet);

    const wxString& GetListName() const { return m_strName; }
    void SetListName(const wxChar* newname) { m_strName = newname; }

    const wxString& GetDescription() const { return m_strDescription; }
    void SetDescription(const wxChar* newdescription) { m_strDescription = newdescription; }

    wxUint32 GetIP() const { return ip; }
    void SetIP(wxUint32 newip);

    const wxString& GetDynIP() const { return m_strDynIP; }
    bool HasDynIP() const { return !m_strDynIP.empty(); }
    void SetDynIP(const wxChar* newdynip) { m_strDynIP = newdynip; }

    const wxChar* GetFullIP() const { return ipfull; }
    const wxChar* GetAddress() const;
    wxUint16 GetPort() const { return port; }

    wxUint32 GetFiles() const { return files; }
    void SetFileCount(wxUint32 in_files) { files = in_files; }

    wxUint32 GetUsers() const { return users; }
    void SetUserCount(wxUint32 in_users) { users = in_users; }

    wxUint32 GetPreferences() const { return m_uPreference; }
    void SetPreference(wxUint32 in_preferences) { m_uPreference = in_preferences; }

    wxUint32 GetPing() const {return ping;}
    void SetPing(wxUint32 in_ping) { ping = in_ping; }

    wxUint32 GetMaxUsers() const { return maxusers; }
    void SetMaxUsers(wxUint32 in_maxusers) { maxusers = in_maxusers; }

    wxUint32 GetFailedCount() const { return failedcount; }
    void SetFailedCount(wxUint32 nCount) { failedcount = nCount; }
    void AddFailedCount() { failedcount++; }
    void ResetFailedCount() { failedcount = 0; }

    wxUint32 GetLastPingedTime() const { return lastpingedtime; }
    void SetLastPingedTime(wxUint32 in_lastpingedtime) { lastpingedtime = in_lastpingedtime; }

    wxUint32 GetLastPinged() const { return lastpinged; }
    void SetLastPinged(wxUint32 in_lastpinged) { lastpinged = in_lastpinged; }

    wxUint8 GetLastDescPingedCount() const { return lastdescpingedcout; }
    void SetLastDescPingedCount(bool reset);

    bool IsStaticMember() const { return staticservermember; }
    void SetIsStaticMember(bool in) { staticservermember = in; }

    wxUint32 GetChallenge() const { return challenge; }
    void SetChallenge(wxUint32 in_challenge) { challenge = in_challenge; }

    wxUint32 GetDescReqChallenge() const { return m_uDescReqChallenge; }
    void SetDescReqChallenge(wxUint32 uDescReqChallenge) { m_uDescReqChallenge = uDescReqChallenge; }

    wxUint32 GetSoftFiles() const { return softfiles; }
    void SetSoftFiles(wxUint32 in_softfiles) { softfiles = in_softfiles; }

    wxUint32 GetHardFiles() const { return hardfiles; }
    void SetHardFiles(wxUint32 in_hardfiles) { hardfiles = in_hardfiles; }

    const wxString& GetVersion() const { return m_strVersion; }
    void SetVersion(const wxChar* pszVersion) { m_strVersion = pszVersion; }

    wxUint32 GetTCPFlags() const { return m_uTCPFlags; }
    void SetTCPFlags(wxUint32 uFlags) { m_uTCPFlags = uFlags; }

    wxUint32 GetUDPFlags() const { return m_uUDPFlags; }
    void SetUDPFlags(wxUint32 uFlags) { m_uUDPFlags = uFlags; }

    wxUint32 GetLowIDUsers() const { return m_uLowIDUsers; }
    void SetLowIDUsers(wxUint32 uLowIDUsers) { m_uLowIDUsers = uLowIDUsers; }

    bool GetUnicodeSupport() const { return (GetTCPFlags() & SRV_TCPFLG_UNICODE)!=0; }
    bool GetRelatedSearchSupport() const { return (GetTCPFlags() & SRV_TCPFLG_RELATEDSEARCH)!=0; }
    bool SupportsLargeFilesTCP() const { return (GetTCPFlags() & SRV_TCPFLG_LARGEFILES)!=0; }
    bool SupportsLargeFilesUDP() const { return (GetUDPFlags() & SRV_UDPFLG_LARGEFILES)!=0; }

    bool IsEqual(const xServer* pServer) const;

private:
    wxUint32 challenge;
    wxUint32 m_uDescReqChallenge;
    wxUint32 lastpinged; //This is to get the ping delay.
    wxUint32 lastpingedtime; //This is to decided when we retry the ping.
    wxUint8 lastdescpingedcout;
    wxUint32 files;
    wxUint32 users;
    wxUint32 maxusers;
    wxUint32 softfiles;
    wxUint32 hardfiles;
    wxUint32 m_uPreference;
    wxUint32 ping;
    wxString m_strDescription;
    wxString m_strName;
    wxString m_strDynIP;
    wxChar ipfull[3+1+3+1+3+1+3+1]; // 16
    wxUint32 ip;
    wxUint16 port;
    bool staticservermember;
    wxUint32 failedcount;
    wxString m_strVersion;
    wxUint32 m_uTCPFlags;
    wxUint32 m_uUDPFlags;
    wxUint32 m_uLowIDUsers;
};

#endif // _XSERVER_H_
