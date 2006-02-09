#ifndef _XOPCODES_H_
#define _XOPCODES_H_

#include <wx/defs.h>                   // wxWidgets Definitions

///////////////////////////////////////////
// Server TCP flags
///////////////////////////////////////////

#define SRV_TCPFLG_COMPRESSION    0x00000001
#define SRV_TCPFLG_NEWTAGS        0x00000008
#define SRV_TCPFLG_UNICODE        0x00000010
#define SRV_TCPFLG_RELATEDSEARCH  0x00000040
#define SRV_TCPFLG_TYPETAGINTEGER 0x00000080
#define SRV_TCPFLG_LARGEFILES     0x00000100

///////////////////////////////////////////
// Server UDP flags
///////////////////////////////////////////

#define SRV_UDPFLG_EXT_GETSOURCES  0x00000001
#define SRV_UDPFLG_EXT_GETFILES    0x00000002
#define SRV_UDPFLG_NEWTAGS         0x00000008
#define SRV_UDPFLG_UNICODE         0x00000010
#define SRV_UDPFLG_EXT_GETSOURCES2 0x00000020
#define SRV_UDPFLG_LARGEFILES      0x00000100

///////////////////////////////////////////
// server.met
///////////////////////////////////////////

#define ST_SERVERNAME           0x01    // <string>
#define ST_DESCRIPTION          0x0B    // <string>
#define ST_PING                 0x0C    // <uint32>
#define ST_FAIL                 0x0D    // <uint32>
#define ST_PREFERENCE           0x0E    // <uint32>
#define ST_PORT                 0x0F    // <uint32>
#define ST_IP                   0x10    // <uint32>
#define ST_DYNIP                0x85    // <string>
#define ST_MAXUSERS             0x87    // <uint32>
#define ST_SOFTFILES            0x88    // <uint32>
#define ST_HARDFILES            0x89    // <uint32>
#define ST_LASTPING             0x90    // <uint32>
#define ST_VERSION              0x91    // <string>|<uint32>
#define ST_UDPFLAGS             0x92    // <uint32>
#define ST_AUXPORTSLIST         0x93    // <string>
#define ST_LOWIDUSERS           0x94    // <uint32>

#pragma pack(1)
struct ServerMet_Struct
{
    wxUint32 ip;
    wxUint16 port;
    wxUint32 tagcount;
};
#pragma pack()

///////////////////////////////////////////
// xTag Types
///////////////////////////////////////////

#define TAGTYPE_HASH            0x01
#define TAGTYPE_STRING          0x02
#define TAGTYPE_UINT32          0x03
#define TAGTYPE_FLOAT32         0x04
#define TAGTYPE_BOOL            0x05
#define TAGTYPE_BOOLARRAY       0x06
#define TAGTYPE_BLOB            0x07
#define TAGTYPE_UINT16          0x08
#define TAGTYPE_UINT8           0x09
#define TAGTYPE_BSOB            0x0A
#define TAGTYPE_UINT64          0x0B

#define TAGTYPE_STR1            0x11
#define TAGTYPE_STR2            0x12
#define TAGTYPE_STR3            0x13
#define TAGTYPE_STR4            0x14
#define TAGTYPE_STR5            0x15
#define TAGTYPE_STR6            0x16
#define TAGTYPE_STR7            0x17
#define TAGTYPE_STR8            0x18
#define TAGTYPE_STR9            0x19
#define TAGTYPE_STR10           0x1A
#define TAGTYPE_STR11           0x1B
#define TAGTYPE_STR12           0x1C
#define TAGTYPE_STR13           0x1D
#define TAGTYPE_STR14           0x1E
#define TAGTYPE_STR15           0x1F
#define TAGTYPE_STR16           0x20
// The following 6 tag types are accepted by eMule 0.42f (02-Mai-2004) in receiving
// code only because of a flaw, those tags are handled correctly, but should not be
// handled at all
#define TAGTYPE_STR17           0x21
#define TAGTYPE_STR18           0x22
#define TAGTYPE_STR19           0x23
#define TAGTYPE_STR20           0x24
#define TAGTYPE_STR21           0x25
#define TAGTYPE_STR22           0x26

#define MAX_EMULE_FILE_SIZE 0x4000000000ui64 // = 2^38 = 256GB
#define OLD_MAX_EMULE_FILE_SIZE 4290048000ui64  // (4294967295/PARTSIZE)*PARTSIZE = ~4GB

#define ED2KFTSTR_AUDIO         "Audio" // value for eD2K tag FT_FILETYPE
#define ED2KFTSTR_VIDEO         "Video" // value for eD2K tag FT_FILETYPE
#define ED2KFTSTR_IMAGE         "Image" // value for eD2K tag FT_FILETYPE
#define ED2KFTSTR_DOCUMENT      "Doc"   // value for eD2K tag FT_FILETYPE
#define ED2KFTSTR_PROGRAM       "Pro"   // value for eD2K tag FT_FILETYPE
#define ED2KFTSTR_ARCHIVE       "Arc"   // eMule internal use only
#define ED2KFTSTR_CDIMAGE       "Iso"   // eMule internal use only
#define ED2KFTSTR_EMULECOLLECTION "EmuleCollection" // Value for eD2K tag FT_FILETYPE

#endif // _XOPCODES_H_
