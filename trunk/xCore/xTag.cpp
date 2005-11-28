#include "../xApp.h"                   // wxGetApp()
#include "xTag.h"
#include "xSafeFile.h"

xTag::xTag(const char* pszName, wxUint32 uVal)
{
    m_uType = TAGTYPE_UINT32;
    m_uName = 0;
    m_pszName = nstrdup(pszName);
    m_uVal = uVal;
    m_nBlobSize = 0;
}

xTag::xTag(wxUint8 uName, wxUint32 uVal)
{
    m_uType = TAGTYPE_UINT32;
    m_uName = uName;
    m_pszName = NULL;
    m_uVal = uVal;
    m_nBlobSize = 0;
}

xTag::xTag(const char* pszName, const wxChar* pszVal)
{
    m_uType = TAGTYPE_STRING;
    m_uName = 0;
    m_pszName = nstrdup(pszName);
    m_pstrVal = new wxString(pszVal);
    m_nBlobSize = 0;
}

xTag::xTag(wxUint8 uName, const wxChar* pszVal)
{
    m_uType = TAGTYPE_STRING;
    m_uName = uName;
    m_pszName = NULL;
    m_pstrVal = new wxString(pszVal);
    m_nBlobSize = 0;
}

xTag::xTag(const char* pszName, const wxString& rstrVal)
{
    m_uType = TAGTYPE_STRING;
    m_uName = 0;
    m_pszName = nstrdup(pszName);
    m_pstrVal = new wxString(rstrVal);
    m_nBlobSize = 0;
}

xTag::xTag(wxUint8 uName, const wxString& rstrVal)
{
    m_uType = TAGTYPE_STRING;
    m_uName = uName;
    m_pszName = NULL;
    m_pstrVal = new wxString(rstrVal);
    m_nBlobSize = 0;
}

xTag::xTag(wxUint8 uName, const wxByte* pucHash)
{
    m_uType = TAGTYPE_HASH;
    m_uName = uName;
    m_pszName = NULL;
    m_pData = new wxByte[16];
    memcpy(m_pData, pucHash, 16);
    m_nBlobSize = 0;
}

xTag::xTag(wxUint8 uName, wxUint32 nSize, const wxByte* pucData)
{
    m_uType = TAGTYPE_BLOB;
    m_uName = uName;
    m_pszName = NULL;
    m_pData = new wxByte[nSize];
    memcpy(m_pData, pucData, nSize);
    m_nBlobSize = nSize;
}

xTag::xTag(const xTag& rTag)
{
    m_uType = rTag.m_uType;
    m_uName = rTag.m_uName;
    m_pszName = rTag.m_pszName!=NULL ? nstrdup(rTag.m_pszName) : NULL;
    m_nBlobSize = 0;
    if (rTag.IsStr())
        m_pstrVal = new wxString(rTag.GetStr());
    else if (rTag.IsInt())
        m_uVal = rTag.GetInt();
    else if (rTag.IsFloat())
        m_fVal = rTag.GetFloat();
    else if (rTag.IsHash()){
        m_pData = new wxByte[16];
        memcpy(m_pData, rTag.GetHash(), 16);
    }
    else if (rTag.IsBlob())
    {
        m_nBlobSize = rTag.GetBlobSize();
        m_pData = new wxByte[rTag.GetBlobSize()];
        memcpy(m_pData, rTag.GetBlob(), rTag.GetBlobSize());
    }
    else
    {
        wxASSERT(0);
        m_uVal = 0;
    }
}

xTag::xTag(xFileDataIO* data, bool bOptUTF8)
{
    m_uType = data->ReadUInt8();
    if (m_uType & 0x80)
    {
        m_uType &= 0x7F;
        m_uName = data->ReadUInt8();
        m_pszName = NULL;
    }
    else
    {
        wxUint32 length = data->ReadUInt16();
        if (length == 1)
        {
            m_uName = data->ReadUInt8();
            m_pszName = NULL;
        }
        else
        {
            m_uName = 0;
            m_pszName = new char[length+1];
//            try{
                data->Read(m_pszName, length);
//            }
/*            catch(CFileException* ex){
                delete[] m_pszName;
                throw ex;
            }*/
            m_pszName[length] = '\0';
        }
    }

    m_nBlobSize = 0;

    // NOTE: It's very important that we read the *entire* packet data, even if we do
    // not use each tag. Otherwise we will get troubles when the packets are returned in
    // a list - like the search results from a server.
    if (m_uType == TAGTYPE_STRING)
    {
        m_pstrVal = new wxString(data->ReadString(bOptUTF8));
    }
    else if (m_uType == TAGTYPE_UINT32)
    {
        m_uVal = data->ReadUInt32();
    }
    else if (m_uType == TAGTYPE_UINT16)
    {
        m_uVal = data->ReadUInt16();
        m_uType = TAGTYPE_UINT32;
    }
    else if (m_uType == TAGTYPE_UINT8)
    {
        m_uVal = data->ReadUInt8();
        m_uType = TAGTYPE_UINT32;
    }
    else if (m_uType == TAGTYPE_FLOAT32)
    {
        data->Read(&m_fVal, 4);
    }
    else if (m_uType >= TAGTYPE_STR1 && m_uType <= TAGTYPE_STR16)
    {
        wxUint32 length = m_uType - TAGTYPE_STR1 + 1;
        m_pstrVal = new wxString(data->ReadString(bOptUTF8, length));
        m_uType = TAGTYPE_STRING;
    }
    else if (m_uType == TAGTYPE_HASH)
    {
        m_pData = new wxByte[16];
//        try{
            data->Read(m_pData, 16);
//        }
/*        catch(CFileException* ex)
        {
            delete[] m_pData;
            throw ex;
        }*/
    }
    else if (m_uType == TAGTYPE_BOOL)
    {
//        TRACE("***NOTE: %s; Reading BOOL tag\n", __FUNCTION__);
        data->Seek(1, wxFromCurrent);
    }
    else if (m_uType == TAGTYPE_BOOLARRAY)
    {
//        TRACE("***NOTE: %s; Reading BOOL Array tag\n", __FUNCTION__);
        wxUint16 len;
        data->Read(&len, 2);
        // 07-Apr-2004: eMule versions prior to 0.42e.29 used the formula "(len+7)/8"!
        data->Seek((len/8)+1, wxFromCurrent);
    }
    else if (m_uType == TAGTYPE_BLOB)
    {
        // 07-Apr-2004: eMule versions prior to 0.42e.29 handled the "len" as int16!
        m_nBlobSize = data->ReadUInt32();
        if (m_nBlobSize <= data->GetLength() - data->GetPosition()){
            m_pData = new wxByte[m_nBlobSize];
            data->Read(m_pData, m_nBlobSize);
        }
        else
        {
            wxASSERT( false );
            m_nBlobSize = 0;
            m_pData = NULL;
        }
    }
    else
    {
        if (m_uName != 0)
            wxGetApp().Log(wxString::Format(wxT("%s; Unknown tag: type=0x%02X  specialtag=%u\n"), __FUNCTION__, m_uType, m_uName));
        else
            wxGetApp().Log(wxString::Format(wxT("%s; Unknown tag: type=0x%02X  name=\"%s\"\n"), __FUNCTION__, m_uType, m_pszName));
        m_uVal = 0;
    }
}

xTag::~xTag()
{
    delete[] m_pszName;
    if (IsStr())
        delete m_pstrVal;
    else if (IsHash())
        delete[] m_pData;
    else if (IsBlob())
        delete[] m_pData;
}

/*bool xTag::WriteNewEd2kTag(CFileDataIO* data, EUtf8Str eStrEncode) const
{
    ASSERT_VALID(this);

    // Write tag type
    wxUint8 uType;
    wxUint32 uStrValLen = 0;
    const char* pszValA = NULL;
    CStringA* pstrValA = NULL;
    if (IsInt())
    {
        if (m_uVal <= 0xFF)
            uType = TAGTYPE_UINT8;
        else if (m_uVal <= 0xFFFF)
            uType = TAGTYPE_UINT16;
        else
            uType = TAGTYPE_UINT32;
    }
    else if (IsStr())
    {
        if (eStrEncode == utf8strRaw)
        {
            CUnicodeToUTF8 utf8(*m_pstrVal);
            pstrValA = new CStringA((const char*)utf8, utf8.GetLength());
        }
        else if (eStrEncode == utf8strOptBOM)
        {
            if (NeedUTF8String(*m_pstrVal))
            {
                CUnicodeToBOMUTF8 bomutf8(*m_pstrVal);
                pstrValA = new CStringA((const char*)bomutf8, bomutf8.GetLength());
            }
            else
            {
                CUnicodeToMultiByte mb(*m_pstrVal);
                pstrValA = new CStringA((const char*)mb, mb.GetLength());
            }
        }
        else
        {
            CUnicodeToMultiByte mb(*m_pstrVal);
            pstrValA = new CStringA((const char*)mb, mb.GetLength());
        }
        uStrValLen = pstrValA->GetLength();
        pszValA = *pstrValA;
        if (uStrValLen >= 1 && uStrValLen <= 16)
            uType = TAGTYPE_STR1 + uStrValLen - 1;
        else
            uType = TAGTYPE_STRING;
    }
    else
        uType = m_uType;

    // Write tag name
    if (m_pszName)
    {
        data->WriteUInt8(uType);
        wxUint32 uTagNameLen = strlen(m_pszName);
        data->WriteUInt16(uTagNameLen);
        data->Write(m_pszName, uTagNameLen);
    }
    else
    {
        ASSERT( m_uName != 0 );
        data->WriteUInt8(uType | 0x80);
        data->WriteUInt8(m_uName);
    }

    // Write tag data
    if (uType == TAGTYPE_STRING)
    {
        data->WriteUInt16(uStrValLen);
        data->Write(pszValA, uStrValLen);
    }
    else if (uType >= TAGTYPE_STR1 && uType <= TAGTYPE_STR16)
    {
        data->Write(pszValA, uStrValLen);
    }
    else if (uType == TAGTYPE_UINT32)
    {
        data->WriteUInt32(m_uVal);
    }
    else if (uType == TAGTYPE_UINT16)
    {
        data->WriteUInt16(m_uVal);
    }
    else if (uType == TAGTYPE_UINT8)
    {
        data->WriteUInt8(m_uVal);
    }
    else if (uType == TAGTYPE_FLOAT32)
    {
        data->Write(&m_fVal, 4);
    }
    else if (uType == TAGTYPE_HASH)
    {
        data->WriteHash16(m_pData);
    }
    else if (uType == TAGTYPE_BLOB)
    {
        data->WriteUInt32(m_nBlobSize);
        data->Write(m_pData, m_nBlobSize);
    }
    else
    {
        TRACE("%s; Unknown tag: type=0x%02X\n", __FUNCTION__, uType);
        ASSERT(0);
        return false;
    }

    delete pstrValA;
    return true;
}

bool xTag::WriteTagToFile(CFileDataIO* file, EUtf8Str eStrEncode) const
{
    ASSERT_VALID(this);

    // don't write tags of unknown types, we wouldn't be able to read them in again
    // and the met file would be corrupted
    if (IsStr() || IsInt() || IsFloat() || IsBlob())
    {
        file->WriteUInt8(m_uType);

        if (m_pszName)
        {
            wxUint32 taglen = strlen(m_pszName);
            file->WriteUInt16(taglen);
            file->Write(m_pszName, taglen);
        }
        else
        {
            file->WriteUInt16(1);
            file->WriteUInt8(m_uName);
        }

        if (IsStr())
        {
            file->WriteString(GetStr(), eStrEncode);
        }
        else if (IsInt())
        {
            file->WriteUInt32(m_uVal);
        }
        else if (IsFloat())
        {
            file->Write(&m_fVal, 4);
        }
        else if (IsBlob())
        {
            // NOTE: This will break backward compatibility with met files for eMule versions prior to 0.44a
            file->WriteUInt32(m_nBlobSize);
            file->Write(m_pData, m_nBlobSize);
        }
        //TODO: Support more tag types
        else
        {
            TRACE("%s; Unknown tag: type=0x%02X\n", __FUNCTION__, m_uType);
            ASSERT(0);
            return false;
        }
        return true;
    }
    else
    {
        TRACE("%s; Ignored tag with unknown type=0x%02X\n", __FUNCTION__, m_uType);
        ASSERT(0);
        return false;
    }
}*/

void xTag::SetInt(wxUint32 uVal)
{
    wxASSERT( IsInt() );
    if (IsInt())
        m_uVal = uVal;
}

void xTag::SetStr(const wxChar* pszVal)
{
    wxASSERT( IsStr() );
    if (IsStr())
    {
        delete m_pstrVal;
        m_pstrVal = NULL;
        m_pstrVal = new wxString(pszVal);
    }
}

wxString xTag::GetFullInfo() const
{
    wxString strTag;
    if (m_pszName)
    {
        strTag = wxT('\"');
        strTag += wxString(m_pszName, wxConvLocal);
        strTag += wxT('\"');
    }
    else
    {
        strTag.Printf(wxT("0x%02X"), m_uName);
    }
    strTag += wxT("=");
    if (m_uType == TAGTYPE_STRING)
    {
        strTag += wxT("\"");
        strTag += *m_pstrVal;
        strTag += wxT("\"");
    }
    else if (m_uType >= TAGTYPE_STR1 && m_uType <= TAGTYPE_STR16)
    {
        strTag.Append(wxString::Format(wxT("(Str%u)\"%s\""), m_uType - TAGTYPE_STR1 + 1, m_pstrVal));
    }
    else if (m_uType == TAGTYPE_UINT32)
    {
        strTag.Append(wxString::Format(wxT("(Int32)%u"), m_uVal));
    }
    else if (m_uType == TAGTYPE_UINT16)
    {
        strTag.Append(wxString::Format(wxT("(Int16)%u"), m_uVal));
    }
    else if (m_uType == TAGTYPE_UINT8)
    {
        strTag.Append(wxString::Format(wxT("(Int8)%u"), m_uVal));
    }
    else if (m_uType == TAGTYPE_FLOAT32)
    {
        strTag.Append(wxString::Format(wxT("(Float32)%f"), m_fVal));
    }
    else if (m_uType == TAGTYPE_BLOB)
    {
        strTag.Append(wxString::Format(wxT("(Blob)%u"), m_nBlobSize));
    }
    else
    {
        strTag.Append(wxString::Format(wxT("Type=%u"), m_uType));
    }
    return strTag;
}
