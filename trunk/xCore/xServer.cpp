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

#include "xServer.h"                   // xServer
#include "../xApp.h"                   // wxGetApp()
#include "xTag.h"
#include "xUtils.h"                    // ipstr()

#ifdef __UNIX__
#include <arpa/inet.h>                 // inet_addr()
#endif

xServer::xServer(const ServerMet_Struct* in_data)
{
    port = in_data->port;
    ip = in_data->ip;
    wxStrcpy(ipfull, ipstr(ip));
    files = 0;
    users = 0;
    m_uPreference = 0;
    ping = 0;
    failedcount = 0;
    lastpinged = 0;
    lastpingedtime = 0;
    staticservermember = false;
    maxusers = 0;
    softfiles = 0;
    hardfiles = 0;
    lastdescpingedcout = 0;
    m_uTCPFlags = 0;
    m_uUDPFlags = 0;
    m_uDescReqChallenge = 0;
    m_uLowIDUsers = 0;
    challenge = 0;
}

xServer::xServer(wxUint16 in_port, const wxChar* i_addr)
{
    port = in_port;
    if ((ip = inet_addr(wxConvLibc.cWC2MB(i_addr))) == INADDR_NONE && wxStrcmp(i_addr, wxT("255.255.255.255")) != 0)
    {
        m_strDynIP = i_addr;
        ip = 0;
    }
    wxStrcpy(ipfull, ipstr(ip));
    files = 0;
    users = 0;
    m_uPreference = 0;
    ping = 0;
    failedcount = 0;
    lastpinged = 0;
    lastpingedtime = 0;
    staticservermember = false;
    maxusers = 0;
    softfiles = 0;
    hardfiles = 0;
    lastdescpingedcout = 0;
    m_uTCPFlags = 0;
    m_uUDPFlags = 0;
    m_uDescReqChallenge = 0;
    m_uLowIDUsers = 0;
    challenge = 0;
}

xServer::xServer(const xServer* pOld)
{
    port = pOld->port;
    ip = pOld->ip;
    staticservermember = pOld->IsStaticMember();
    wxStrcpy(ipfull, pOld->ipfull);
    files = pOld->files;
    users = pOld->users;
    m_uPreference = pOld->m_uPreference;
    ping = pOld->ping;
    failedcount = pOld->failedcount;
    lastpinged = pOld->lastpinged;
    lastpingedtime = pOld->lastpingedtime;
    maxusers = pOld->maxusers;
    softfiles = pOld->softfiles;
    hardfiles = pOld->hardfiles;
    lastdescpingedcout = pOld->lastdescpingedcout;
    m_strDescription = pOld->m_strDescription;
    m_strName = pOld->m_strName;
    m_strDynIP = pOld->m_strDynIP;
    m_strVersion = pOld->m_strVersion;
    m_uTCPFlags = pOld->m_uTCPFlags;
    m_uUDPFlags = pOld->m_uUDPFlags;
    m_uDescReqChallenge = pOld->m_uDescReqChallenge;
    m_uLowIDUsers = pOld->m_uLowIDUsers;
    challenge = pOld->challenge;
}

xServer::~xServer()
{
}

bool xServer::AddTagFromFile(xFileDataIO* servermet)
{
    xTag* tag = new xTag(servermet, false);
    switch(tag->GetNameID())
    {
    case ST_SERVERNAME:
        wxASSERT( tag->IsStr() );
        if (tag->IsStr()){
            if (m_strName.empty())
                m_strName = tag->GetStr();
        }
        break;
    case ST_DESCRIPTION:
        wxASSERT( tag->IsStr() );
        if (tag->IsStr()){
            if (m_strDescription.empty())
                m_strDescription = tag->GetStr();
        }
        break;
    case ST_PING:
        wxASSERT( tag->IsInt() );
        if (tag->IsInt())
            ping = tag->GetInt();
        break;
    case ST_FAIL:
        wxASSERT( tag->IsInt() );
        if (tag->IsInt())
            failedcount = tag->GetInt();
        break;
    case ST_PREFERENCE:
        wxASSERT( tag->IsInt() );
        if (tag->IsInt())
            m_uPreference = tag->GetInt();
        break;
    case ST_DYNIP:
        wxASSERT( tag->IsStr() );
        if (tag->IsStr())
        {
            if (m_strDynIP.empty())
                m_strDynIP = tag->GetStr();
        }
        break;
    case ST_MAXUSERS:
        wxASSERT( tag->IsInt() );
        if (tag->IsInt())
            maxusers = tag->GetInt();
        break;
    case ST_SOFTFILES:
        wxASSERT( tag->IsInt() );
        if (tag->IsInt())
            softfiles = tag->GetInt();
        break;
    case ST_HARDFILES:
        wxASSERT( tag->IsInt() );
        if (tag->IsInt())
            hardfiles = tag->GetInt();
        break;
    case ST_LASTPING:
        wxASSERT( tag->IsInt() );
        if (tag->IsInt())
            lastpingedtime = tag->GetInt();
        break;
    case ST_VERSION:
        if (tag->IsStr()){
            if (m_strVersion.empty())
                m_strVersion = tag->GetStr();
        }
        else if (tag->IsInt())
            m_strVersion.Printf(wxT("%u.%u"), tag->GetInt() >> 16, tag->GetInt() & 0xFFFF);
        else
            wxASSERT(0);
        break;
    case ST_UDPFLAGS:
        wxASSERT( tag->IsInt() );
        if (tag->IsInt())
            m_uUDPFlags = tag->GetInt();
        break;
    case ST_LOWIDUSERS:
        wxASSERT( tag->IsInt() );
        if (tag->IsInt())
            m_uLowIDUsers = tag->GetInt();
        break;
    case ST_PORT:
        wxASSERT( tag->IsInt() );
        break;
    case ST_IP:
        wxASSERT( tag->IsInt() );
        break;
    default:
        if (tag->GetNameID()==0 && !CmpED2KTagName(tag->GetName(), "files")){
            wxASSERT( tag->IsInt() );
            if (tag->IsInt())
                files = tag->GetInt();
        }
        else if (tag->GetNameID()==0 && !CmpED2KTagName(tag->GetName(), "users")){
            wxASSERT( tag->IsInt() );
            if (tag->IsInt())
                users = tag->GetInt();
        }
        else
        {
            wxString toLog(wxT("Unknown tag in server.met: "));
            toLog<<tag->GetFullInfo();
            wxGetApp().Log(toLog);
        }
    }
    delete tag;
    return true;
}

const wxChar* xServer::GetAddress() const
{
    if (!m_strDynIP.empty())
    {
        return m_strDynIP.c_str();
    }
    else
    {
        return ipfull;
    }
}

void xServer::SetIP(wxUint32 newip)
{
    ip = newip;
    wxStrcpy(ipfull, ipstr(ip));
}

void xServer::SetLastDescPingedCount(bool bReset)
{
    if (bReset)
    {
        lastdescpingedcout = 0;
    }
    else
    {
        lastdescpingedcout++;
    }
}

bool xServer::IsEqual(const xServer* pServer) const
{
    if (GetPort() != pServer->GetPort())
        return false;
    if (HasDynIP() && pServer->HasDynIP())
        return (GetDynIP().CmpNoCase(pServer->GetDynIP()) == 0);
    if (HasDynIP() || pServer->HasDynIP())
        return false;
    return (GetIP() == pServer->GetIP());
}
