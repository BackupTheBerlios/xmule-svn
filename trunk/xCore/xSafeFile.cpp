/**
 * xSafeFile.cpp
 */

#include "xSafeFile.h"                 // Class declarations

//////////////////////////////////
// TODO: MOVE AWAY FROM HERE! :/
int utf8towc(const char* pcUtf8, wxUint32 uUtf8Size, wxChar* pwc, wxUint32 uWideCharSize)
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

int ByteStreamToWideChar(const char* pcUtf8, wxUint32 uUtf8Size, wxChar* pwc, wxUint32 uWideCharSize)
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

//////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// xFileDataIO

wxUint8 xFileDataIO::ReadUInt8()
{
    wxUint8 nVal;
    Read(&nVal, sizeof(nVal));
    return nVal;
}

wxUint16 xFileDataIO::ReadUInt16()
{
    wxUint16 nVal;
    Read(&nVal, sizeof(nVal));
    return nVal;
}

wxUint32 xFileDataIO::ReadUInt32()
{
    wxUint32 nVal;
    Read(&nVal, sizeof(nVal));
    return nVal;
}

wxUint64 CFileDataIO::ReadUInt64()
{
	wxUint64 nVal;
	Read(&nVal, sizeof(nVal));
	return nVal;
}

/*void CFileDataIO::ReadUInt128(Kademlia::CUInt128 *pVal)
{
    Read(pVal->GetDataPtr(), 16);
}*/

void xFileDataIO::ReadHash16(unsigned char* pVal)
{
    Read(pVal, 16);
}

wxString xFileDataIO::ReadString(bool bOptUTF8, wxUint32 uRawSize)
{
    const wxUint32 uMaxShortRawSize = SHORT_RAW_ED2K_UTF8_STR;
    if (uRawSize <= uMaxShortRawSize)
    {
        char acRaw[uMaxShortRawSize];
        Read(acRaw, uRawSize);
        if (uRawSize >= 3 && (unsigned char)acRaw[0] == 0xEFU && (unsigned char)acRaw[1] == 0xBBU && (unsigned char)acRaw[2] == 0xBFU)
        {
            wxChar awc[uMaxShortRawSize];
            int iChars = ByteStreamToWideChar(acRaw+3, uRawSize-3, awc, WXSIZEOF(awc));
            if (iChars >= 0)
            {
                return wxString(awc, iChars);
            }
        }
        else if (bOptUTF8)
        {
            wxChar awc[uMaxShortRawSize];
            int iChars = utf8towc(acRaw, uRawSize, awc, WXSIZEOF(awc));
            if (iChars >= 0)
            {
                return wxString(awc, iChars);
            }
        }
        return wxString(acRaw, wxConvLocal, uRawSize); // use local codepage
    }
    else
    {
        Array<char> acRaw(uRawSize);
        Read(acRaw, uRawSize);
        if (uRawSize >= 3 && (unsigned char)acRaw[0] == 0xEFU && (unsigned char)acRaw[1] == 0xBBU && (unsigned char)acRaw[2] == 0xBFU)
        {
            Array<wxChar> awc(uRawSize);
            int iChars = ByteStreamToWideChar(acRaw + 3, uRawSize - 3, awc, uRawSize);
            if (iChars >= 0)
            {
                return wxString(awc, iChars);
            }
        }
        else if (bOptUTF8)
        {
            Array<wxChar> awc(uRawSize);
            //int iChars = ByteStreamToWideChar(acRaw, uRawSize, awc, uRawSize);
            int iChars = utf8towc(acRaw, uRawSize, awc, uRawSize);
            if (iChars >= 0)
            {
                return wxString(awc, iChars);
            }
        }
        return wxString(acRaw, wxConvLocal, uRawSize); // use local codepage
    }
}

wxString xFileDataIO::ReadString(bool bOptUTF8)
{
    wxUint32 uLen = ReadUInt16();
    return ReadString(bOptUTF8, uLen);
}

wxString xFileDataIO::ReadStringUTF8()
{
    wxUint32 uRawSize = ReadUInt16();
    const wxUint32 uMaxShortRawSize = SHORT_RAW_ED2K_UTF8_STR;
    if (uRawSize <= uMaxShortRawSize)
    {
        char acRaw[uMaxShortRawSize];
        Read(acRaw, uRawSize);
        wxChar awc[uMaxShortRawSize];
        int iChars = ByteStreamToWideChar(acRaw, uRawSize, awc, WXSIZEOF(awc));
        if (iChars >= 0)
        {
            return wxString(awc, iChars);
        }
        return wxString(acRaw, wxConvLocal, uRawSize); // use local codepage
    }
    else
    {
        Array<char> acRaw(uRawSize);
        Read(acRaw, uRawSize);
        Array<wxChar> awc(uRawSize);
        int iChars = ByteStreamToWideChar(acRaw, uRawSize, awc, uRawSize);
        if (iChars >= 0)
        {
            return wxString(awc, iChars);
        }
        return wxString(acRaw, wxConvLocal, uRawSize); // use local codepage;
    }
}

void xFileDataIO::WriteUInt8(wxUint8 nVal)
{
    Write(&nVal, sizeof(nVal));
}

void xFileDataIO::WriteUInt16(wxUint16 nVal)
{
    Write(&nVal, sizeof(nVal));
}

void xFileDataIO::WriteUInt32(wxUint32 nVal)
{
    Write(&nVal, sizeof(nVal));
}

void CFileDataIO::WriteUInt64(wxUint64 nVal)
{
	Write(&nVal, sizeof(nVal));
}

/*void CFileDataIO::WriteUInt128(const Kademlia::CUInt128 *pVal)
{
    Write(pVal->GetData(), 16);
}*/

void xFileDataIO::WriteHash16(const unsigned char* pVal)
{
    Write(pVal, 16);
}

/*void CFileDataIO::WriteString(const CString& rstr, EUtf8Str eEncode)
{
#define	WRITE_STR_LEN(n) WriteUInt16((wxUint16)(n))
    if (eEncode == utf8strRaw)
    {
        CUnicodeToUTF8 utf8(rstr);
        WRITE_STR_LEN(utf8.GetLength());
        Write((const char*)utf8, utf8.GetLength());
    }
    else if (eEncode == utf8strOptBOM)
    {
        if (NeedUTF8String(rstr))
        {
            CUnicodeToBOMUTF8 bomutf8(rstr);
            WRITE_STR_LEN(bomutf8.GetLength());
            Write((const char*)bomutf8, bomutf8.GetLength());
        }
        else
        {
            CUnicodeToMultiByte mb(rstr);
            WRITE_STR_LEN(mb.GetLength());
            Write((const char*)mb, mb.GetLength());
        }
    }
    else
    {
        CUnicodeToMultiByte mb(rstr);
        WRITE_STR_LEN(mb.GetLength());
        Write((const char*)mb, mb.GetLength());
    }
#undef WRITE_STR_LEN
}

void CFileDataIO::WriteString(const char* psz)
{
    wxUint32 uLen = strlen(psz);
    WriteUInt16((wxUint16)uLen);
    Write(psz, uLen);
}

void CFileDataIO::WriteLongString(const CString& rstr, EUtf8Str eEncode)
{
#define	WRITE_STR_LEN(n) WriteUInt32((wxUint32)n)
    if (eEncode == utf8strRaw)
    {
        CUnicodeToUTF8 utf8(rstr);
        WRITE_STR_LEN(utf8.GetLength());
        Write((const char*)utf8, utf8.GetLength());
    }
    else if (eEncode == utf8strOptBOM)
    {
        if (NeedUTF8String(rstr))
        {
            CUnicodeToBOMUTF8 bomutf8(rstr);
            WRITE_STR_LEN(bomutf8.GetLength());
            Write((const char*)bomutf8, bomutf8.GetLength());
        }
        else
        {
            CUnicodeToMultiByte mb(rstr);
            WRITE_STR_LEN(mb.GetLength());
            Write((const char*)mb, mb.GetLength());
        }
    }
    else
    {
        CUnicodeToMultiByte mb(rstr);
        WRITE_STR_LEN(mb.GetLength());
        Write((const char*)mb, mb.GetLength());
    }
#undef WRITE_STR_LEN
}

void CFileDataIO::WriteLongString(const char* psz)
{
    wxUint32 uLen = strlen(psz);
    WritewxUint3232(uLen);
    Write(psz, uLen);
}*/

///////////////////////////////////////////////////////////////////////////////
// xSafeBufferedFile

size_t xSafeBufferedFile::Read(void* lpBuf, wxUint32 nCount)
{
    size_t uRead = wxFFile::Read(lpBuf, nCount);
//  if (uRead != nCount)
//      AfxThrowFileException(CFileException::endOfFile, 0, GetFileName());
    return uRead;
}

void xSafeBufferedFile::Write(const void* lpBuf, wxUint32 nCount)
{
    wxFFile::Write(lpBuf, nCount);
}

bool xSafeBufferedFile::Seek(wxFileOffset lOff, wxSeekMode mode)
{
    return wxFFile::Seek(lOff, mode);
}

wxFileOffset xSafeBufferedFile::GetPosition() const
{
    return wxFFile::Tell();
}

wxFileOffset xSafeBufferedFile::GetLength() const
{
    return wxFFile::Length();
}

/*int CSafeBufferedFile::printf(LPCTSTR pszFmt, ...)
{
    va_list args;
    va_start(args, pszFmt);
    int iResult = _vftprintf(m_pStream, pszFmt, args);
    va_end(args);
    if (iResult < 0)
        AfxThrowFileException(CFileException::generic, _doserrno, m_strFileName);
    return iResult;
}*/
