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

#ifndef _XRESOURCES_H_
#define _XRESOURCES_H_

// Main frame's Icon
#include "XPMs/xMule.xpm"

// Main ToolBar XPMs
#include "XPMs/ToolBar/Connect.xpm"
#include "XPMs/ToolBar/Kad.xpm"
#include "XPMs/ToolBar/Servers.xpm"
#include "XPMs/ToolBar/Transfers.xpm"
#include "XPMs/ToolBar/Search.xpm"
#include "XPMs/ToolBar/SharedFiles.xpm"
#include "XPMs/ToolBar/Statistics.xpm"
#include "XPMs/ToolBar/Options.xpm"
#include "XPMs/ToolBar/Tools.xpm"

// Main ToolBar IDs
enum ToolBarIDs
{
    ID_MAINTOOLBAR = 10020,

    TB_CONNECT,
    TB_KAD,
    TB_SERVERS,
    TB_TRANSFERS,
    TB_SEARCH,
    TB_SHAREDFILES,
    TB_STATISTICS,
    TB_OPTIONS,
    TB_TOOLS
};

// xKadPanel XPMs
#include "XPMs/KadPanel/Contacts.xpm"
#include "XPMs/KadPanel/CurrentSearches.xpm"
#include "XPMs/KadPanel/Bootstrap.xpm"

// xTransfersPanel XPMs
#include "XPMs/TransfersPanel/SplitWindow.xpm"
#include "XPMs/TransfersPanel/Downloads.xpm"
#include "XPMs/TransfersPanel/Uploading.xpm"
#include "XPMs/TransfersPanel/Downloading.xpm"
#include "XPMs/TransfersPanel/OnQueue.xpm"
#include "XPMs/TransfersPanel/KnownClients.xpm"

// xTransferPanel's IDs
enum SwitchToolBarIDs
{
    ID_SWITCHTOOLBAR = 10050,

    ID_SWITCH1,
    ID_VIEWSTOOLBAR,
    ID_SPLITWINDOW,
    ID_DOWNLOADS,
    ID_UPLOADING,
    ID_DOWNLOADING,
    ID_ONQUEUE,
    ID_KNOWNCLIENTS
};

// xSearchPanel XPMs
#include "XPMs/SearchPanel/SearchResults.xpm"

// xShareFilesPanel XPMs
#include "XPMs/SharedFilesPanel/SharedFilesList.xpm"

#endif // _XRESOURCES_H_
