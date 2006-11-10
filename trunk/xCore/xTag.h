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

#ifndef _XTAG_H_
#define _XTAG_H_

#include "xOpCodes.h"                  // xTag opcodes

#include <wx/defs.h>                   // wxWidgets definitions

class xFileDataIO;

class xTag
{
public:
    xTag(const char* pszName, wxUint64 uVal, bool bInt64 = false);
    xTag(wxUint8 uName, wxUint64 uVal, bool bInt64 = false);

    xTag(const char* pszName, const wxChar* pszVal);
    xTag(wxUint8 uName, const wxChar* pszVal);

    xTag(const char* pszName, const wxString& rstrVal);
    xTag(wxUint8 uName, const wxString& rstrVal);

    xTag(wxUint8 uName, const wxByte* pucHash);
    xTag(wxUint8 uName, wxUint32 nSize, const wxByte* pucData);

    xTag(const xTag& rTag);

    xTag(xFileDataIO* data, bool bOptUTF8);
    ~xTag();

    wxUint32 GetType() const { return m_uType; }
    wxUint32 GetNameID() const { return m_uName; }
    const char* GetName() const { return m_pszName; }

    bool IsStr() const { return m_uType == TAGTYPE_STRING; }
    bool IsInt() const { return m_uType == TAGTYPE_UINT32; }
    bool IsFloat() const { return m_uType == TAGTYPE_FLOAT32; }
    bool IsHash() const { return m_uType == TAGTYPE_HASH; }
    bool IsBlob() const { return m_uType == TAGTYPE_BLOB; }
    bool IsInt64(bool bOrInt32 = true) const { return m_uType == TAGTYPE_UINT64 || (bOrInt32 && IsInt()); }

    wxUint32 GetInt() const { wxASSERT(IsInt()); return (wxUint32)m_uVal; }
    wxUint64 GetInt64() const { wxASSERT(IsInt64(true)); return m_uVal; }
    const wxString& GetStr() const { wxASSERT(IsStr()); return* m_pstrVal; }
    float GetFloat() const { wxASSERT(IsFloat()); return m_fVal; }
    const wxByte* GetHash() const { wxASSERT(IsHash()); return m_pData; }
    wxUint32 GetBlobSize() const { wxASSERT(IsBlob()); return m_nBlobSize; }
    const wxByte* GetBlob() const { wxASSERT(IsBlob()); return m_pData; }

    void SetInt(wxUint32 uVal);
    void SetInt64(wxUint64 uVal);
    void SetStr(const wxChar* pszVal);

    xTag* CloneTag() { return new xTag(*this); }

/*    bool WriteTagToFile(CFileDataIO* file, EUtf8Str eStrEncode = utf8strNone) const;    // old eD2K tags
    bool WriteNewEd2kTag(CFileDataIO* file, EUtf8Str eStrEncode = utf8strNone) const;   // new eD2K tags*/

    wxString GetFullInfo() const;

protected:
    wxUint8 m_uType;
    wxUint8 m_uName;
    char* m_pszName;
    wxUint32 m_nBlobSize;
    union
    {
        wxString* m_pstrVal;
        wxUint64 m_uVal;
        float m_fVal;
        wxByte* m_pData;
    };
};

#endif // _XTAG_H_
