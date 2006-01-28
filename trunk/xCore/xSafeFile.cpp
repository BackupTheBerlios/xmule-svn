/**
 * xSafeFile.cpp
 */

#include "xSafeFile.h"                 // Class declarations
#include "xUtils.h"                    // String convertion functions
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

wxUint64 xFileDataIO::ReadUInt64()
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

void xFileDataIO::WriteUInt64(wxUint64 nVal)
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
