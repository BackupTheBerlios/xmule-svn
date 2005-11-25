#ifndef _XTAG_H_
#define _XTAG_H_

#include <wx/defs.h>                   // wxWidgets definitions

class xFileDataIO;

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

#define TAGTYPE_STR1			0x11
#define TAGTYPE_STR2			0x12
#define TAGTYPE_STR3			0x13
#define TAGTYPE_STR4			0x14
#define TAGTYPE_STR5			0x15
#define TAGTYPE_STR6			0x16
#define TAGTYPE_STR7			0x17
#define TAGTYPE_STR8			0x18
#define TAGTYPE_STR9			0x19
#define TAGTYPE_STR10			0x1A
#define TAGTYPE_STR11			0x1B
#define TAGTYPE_STR12			0x1C
#define TAGTYPE_STR13			0x1D
#define TAGTYPE_STR14			0x1E
#define TAGTYPE_STR15			0x1F
#define TAGTYPE_STR16			0x20
#define TAGTYPE_STR17			0x21	// accepted by eMule 0.42f (02-Mai-2004) in receiving code only because of a flaw, those tags are handled correctly, but should not be handled at all
#define TAGTYPE_STR18			0x22	// accepted by eMule 0.42f (02-Mai-2004) in receiving code only because of a flaw, those tags are handled correctly, but should not be handled at all
#define TAGTYPE_STR19			0x23	// accepted by eMule 0.42f (02-Mai-2004) in receiving code only because of a flaw, those tags are handled correctly, but should not be handled at all
#define TAGTYPE_STR20			0x24	// accepted by eMule 0.42f (02-Mai-2004) in receiving code only because of a flaw, those tags are handled correctly, but should not be handled at all
#define TAGTYPE_STR21			0x25	// accepted by eMule 0.42f (02-Mai-2004) in receiving code only because of a flaw, those tags are handled correctly, but should not be handled at all
#define TAGTYPE_STR22			0x26	// accepted by eMule 0.42f (02-Mai-2004) in receiving code only because of a flaw, those tags are handled correctly, but should not be handled at all

class xTag
{
public:
    xTag(const char* pszName, wxUint32 uVal);
    xTag(wxUint8 uName, wxUint32 uVal);

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

    wxUint32 GetInt() const { wxASSERT(IsInt()); return m_uVal; }
    const wxString& GetStr() const { wxASSERT(IsStr()); return* m_pstrVal; }
    float GetFloat() const { wxASSERT(IsFloat()); return m_fVal; }
    const wxByte* GetHash() const { wxASSERT(IsHash()); return m_pData; }
    wxUint32 GetBlobSize() const { wxASSERT(IsBlob()); return m_nBlobSize; }
    const wxByte* GetBlob() const { wxASSERT(IsBlob()); return m_pData; }

    void SetInt(wxUint32 uVal);
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
        wxUint32 m_uVal;
        float m_fVal;
        wxByte* m_pData;
    };
};

// TODO: Move this function away
inline char* nstrdup(const char* todup)
{
   size_t len = strlen(todup) + 1;
   return (char*)memcpy(new char[len], todup, len);
}
#endif // _XTAG_H_
