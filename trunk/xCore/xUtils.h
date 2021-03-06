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

#ifndef _XUTILS_H_
#define _XUTILS_H_

#include <wx/defs.h>                   // wxWidgets definitions
#include <wx/string.h>                 // wxString

// Takes a C-style string and makes a copy of it. Returns a pointer to the new string.
inline char* nstrdup(const char* todup)
{
   size_t len = strlen(todup) + 1;
   return (char*)memcpy(new char[len], todup, len);
}

// Gives the same string as 'inet_ntoa(*(in_addr*)&nIP)' but is not restricted to ASCII strings
inline wxString ipstr(wxUint32 nIP)
{
    const wxByte* pucIP = (wxByte*)&nIP;
    wxString strIP = wxString::Format(wxT("%u.%u.%u.%u"), pucIP[0], pucIP[1], pucIP[2], pucIP[3]);
    return strIP;
}


/////////////////////////////////////
// MD4 Helper Functions
/////////////////////////////////////

// md4clr -- replacement for memset(hash,0,16)
inline void md4clr(const void* hash)
{
    ((wxUint32*)hash)[0] = ((wxUint32*)hash)[1] = ((wxUint32*)hash)[2] = ((wxUint32*)hash)[3] = 0;
}

// md4cpy -- replacement for memcpy(dst,src,16)
inline void md4cpy(void* dst, const void* src)
{
    ((wxUint32*)dst)[0] = ((wxUint32*)src)[0];
    ((wxUint32*)dst)[1] = ((wxUint32*)src)[1];
    ((wxUint32*)dst)[2] = ((wxUint32*)src)[2];
    ((wxUint32*)dst)[3] = ((wxUint32*)src)[3];
}

inline bool isnulmd4(const void* hash)
{
    return  (((wxUint32*)hash)[0] == 0 &&
             ((wxUint32*)hash)[1] == 0 &&
             ((wxUint32*)hash)[2] == 0 &&
             ((wxUint32*)hash)[3] == 0);
}

/////////////////////////////////////
// File Types - TODO
/////////////////////////////////////

inline wxString GetFileTypeByName(const wxString& WXUNUSED(notUsed))
{
    return wxString(wxT("GetFileTypeByName() TODO"));
}

inline wxString GetFileTypeDisplayStrFromED2KFileType(const wxString& WXUNUSED(notUsed))
{
    return wxString(wxT("GetFileTypeDisplayStrFromED2KFileType() TODO"));
}

/////////////////////////////////////
// String convertion/comparison
/////////////////////////////////////

inline int CmpED2KTagName(const char* pszTagName1, const char* pszTagName2)
{
    return wxString(pszTagName1, wxConvLibc).Cmp(wxString(pszTagName2, wxConvLibc));
}

inline int utf8towc(const char* pcUtf8, wxUint32 uUtf8Size, wxChar* pwc, wxUint32 uWideCharSize)
{
    wxChar* pwc0 = pwc;

    while (uUtf8Size && uWideCharSize)
    {
        wxByte ucChar = *pcUtf8++;
        if (ucChar < 0x80)
        {
            uUtf8Size--;
            uWideCharSize--;
            *(pwc++) = ucChar;
        }
        else if ((ucChar & 0xC0) != 0xC0)
        {
            return -1; // Invalid UTF8 string..
        }
        else
        {
            wxByte ucMask = 0xE0;
            wxUint32 uExpectedBytes = 1;
            while ((ucChar & ucMask) == ucMask)
            {
                ucMask |= ucMask >> 1;
                if (++uExpectedBytes > 3)
                {
                    return -1; // Invalid UTF8 string..
                }
            }

            if (uUtf8Size <= uExpectedBytes)
                return -1; // Invalid UTF8 string..

            wxUint32 uProcessedBytes = 1 + uExpectedBytes;
            wxUint32 uWideChar = (wxUint32)(ucChar & ~ucMask);
            if (uExpectedBytes == 1)
            {
                if ((uWideChar & 0x1E) == 0)
                {
                    return -1; // Invalid UTF8 string..
                }
            }
            else
            {
                if (uWideChar == 0 && ((wxByte)*pcUtf8 & 0x3F & (ucMask << 1)) == 0)
                {
                    return -1; // Invalid UTF8 string..
                }
                if (uExpectedBytes == 2)
                {
                    //if (uWideChar == 0x0D && ((wxByte)*pcUtf8 & 0x20))
                    //    return -1;
                }
                else if (uExpectedBytes == 3)
                {
                    if (uWideChar > 4)
                    {
                        return -1; // Invalid UTF8 string..
                    }
                    if (uWideChar == 4 && ((wxByte)*pcUtf8 & 0x30))
                    {
                        return -1; // Invalid UTF8 string..
                    }
                }
            }

            if (uWideCharSize < (wxUint32)(uExpectedBytes > 2) + 1)
            {
                break; // buffer full
            }

            while (uExpectedBytes--)
            {
                if (((ucChar = (wxByte)*(pcUtf8++)) & 0xC0) != 0x80)
                {
                    return -1; // Invalid UTF8 string..
                }
                uWideChar <<= 6;
                uWideChar |= (ucChar & 0x3F);
            }
            uUtf8Size -= uProcessedBytes;

            if (uWideChar < 0x10000)
            {
                uWideCharSize--;
                *(pwc++) = uWideChar;
            }
            else
            {
                uWideCharSize -= 2;
                uWideChar -= 0x10000;
                *(pwc++) = 0xD800 | (uWideChar >> 10);
                *(pwc++) = 0xDC00 | (uWideChar & 0x03FF);
            }
        }
    }
    return pwc - pwc0;
}

inline int ByteStreamToWideChar(const char* pcUtf8, wxUint32 uUtf8Size, wxChar* pwc, wxUint32 uWideCharSize)
{
    int iWideChars = utf8towc(pcUtf8, uUtf8Size, pwc, uWideCharSize);
    if (iWideChars < 0)
    {
        wxChar* pwc0 = pwc;
        while (uUtf8Size && uWideCharSize)
        {
            if ((*pwc++ = (wxByte)*pcUtf8++) == wxT('\0'))
            {
                break;
            }
            uUtf8Size--;
            uWideCharSize--;
        }
        iWideChars = pwc - pwc0;
    }
    return iWideChars;
}
#endif // _XUTILS_H_
