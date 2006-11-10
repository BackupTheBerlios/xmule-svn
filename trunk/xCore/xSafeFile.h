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

#ifndef _XSAFEFILE_H_
#define _XSAFEFILE_H_

#include <wx/defs.h>                   // wxWidgets definitions
#include <wx/ffile.h>                  // wxFFile

#define SHORT_ED2K_STR          256
#define SHORT_RAW_ED2K_MB_STR   (SHORT_ED2K_STR*2)
#define SHORT_RAW_ED2K_UTF8_STR (SHORT_ED2K_STR*4)

enum EUtf8Str
{
    utf8strNone,
    utf8strOptBOM,
    utf8strRaw
};

///////////////////////////////////////////////////////////////////////////////
// xFileDataIO

class xFileDataIO
{
public:
    virtual size_t Read(void* lpBuf, wxUint32 nCount) = 0;
    virtual void Write(const void* lpBuf, wxUint32 nCount) = 0;
    virtual bool Seek(wxFileOffset lOff, wxSeekMode mode) = 0;
    virtual wxFileOffset GetPosition() const = 0;
    virtual wxFileOffset GetLength() const = 0;

    virtual wxUint8 ReadUInt8();
    virtual wxUint16 ReadUInt16();
    virtual wxUint32 ReadUInt32();
    virtual wxUint64 ReadUInt64();
//  virtual void ReadUInt128(Kademlia::CUInt128 *pVal); // TODO:KAD
    virtual void ReadHash16(unsigned char* pVal);
    virtual wxString ReadString(bool bOptUTF8);
    virtual wxString ReadString(bool bOptUTF8, wxUint32 uRawSize);
    virtual wxString ReadStringUTF8();

    virtual void WriteUInt8(wxUint8 nVal);
    virtual void WriteUInt16(wxUint16 nVal);
    virtual void WriteUInt32(wxUint32 nVal);
    virtual void WriteUInt64(wxUint64 nVal);
//  virtual void WriteUInt128(const Kademlia::CUInt128 *pVal); // TODO:KAD
    virtual void WriteHash16(const unsigned char* pVal);
//  virtual void WriteString(const CString& rstr, EUtf8Str eEncode = utf8strNone);
//  virtual void WriteString(LPCSTR psz);
//  virtual void WriteLongString(const CString& rstr, EUtf8Str eEncode = utf8strNone);
//  virtual void WriteLongString(LPCSTR psz);
};

///////////////////////////////////////////////////////////////////////////////
// xSafeBufferedFile

class xSafeBufferedFile : public wxFFile, public xFileDataIO
{
public:
    xSafeBufferedFile() : wxFFile() {}
    xSafeBufferedFile(const wxChar* lpszFileName, const wxChar* mode) : wxFFile(lpszFileName, mode) {}

    virtual size_t Read(void* lpBuf, wxUint32 nCount);
    virtual void Write(const void* lpBuf, wxUint32 nCount);
    virtual bool Seek(wxFileOffset lOff, wxSeekMode mode);
    virtual wxFileOffset GetPosition() const;
    virtual wxFileOffset GetLength() const;
};

///////////////////////////////////////////////////////////////////////////////
// Peek - helper functions for read-accessing memory without modifying the memory pointer

inline wxUint8 PeekUInt8(const void* p)
{
    return *((wxUint8*)p);
}

inline wxUint16 PeekUInt16(const void* p)
{
    return *((wxUint16*)p);
}

inline wxUint32 PeekUInt32(const void* p)
{
    return *((wxUint32*)p);
}

inline wxUint64 PeekUInt64(const void* p)
{
    return *((wxUint64*)p);
}

///////////////////////////////////////////////////////////////////////////////
// Poke - helper functions for write-accessing memory without modifying the memory pointer

inline void PokeUInt8(void* p, wxUint8 nVal)
{
    *((wxUint8*)p) = nVal;
}

inline void PokeUInt16(void* p, wxUint16 nVal)
{
    *((wxUint16*)p) = nVal;
}

inline void PokeUInt32(void* p, wxUint32 nVal)
{
    *((wxUint32*)p) = nVal;
}

inline void PokeUInt64(void* p, wxUint64 nVal)
{
    *((wxUint64*)p) = nVal;
}

///////////////////////////////////////////////////////////////////////////////
// Array

template<class T>
class Array
{
public:
    Array(wxUint32 nCount)
    {
        m_aT = new T[nCount];
    }
    ~Array()
    {
        delete[] m_aT;
    }

    operator T* ()
    {
        return m_aT;
    }

protected:
    T* m_aT;
};

#endif // _XSAFEFILE_H_
