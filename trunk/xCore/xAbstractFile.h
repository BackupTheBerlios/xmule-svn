#ifndef _XABSTRACTFILE_H_
#define _XABSTRACTFILE_H_

#include "xOpCodes.h"

#include <wx/defs.h>                   // wxWidgets definitions
#include <vector>                      // std::vector

//#include <list>                        // std::list TODO:KAD
/*namespace Kademlia TODO:KAD
{
class CUInt128;
class CEntry;
typedef std::list<CStringW> WordList;
};*/

class xTag;

// typedef CTypedPtrList<CPtrList, Kademlia::CEntry*> CKadEntryPtrList; TODO:KAD

class xAbstractFile
{
public:
    xAbstractFile();
    xAbstractFile(const xAbstractFile* pAbstractFile);
    virtual ~xAbstractFile();

    const wxString& GetFileName() const { return m_strFileName; }
    virtual void SetFileName(const wxChar* pszFileName, bool bReplaceInvalidFileSystemChars = false, bool bAutoSetFileType = true); // 'bReplaceInvalidFileSystemChars' is set to 'false' for backward compatibility!

    // returns the ED2K file type
    const wxString& GetFileType() const { return m_strFileType; }
    virtual void SetFileType(const wxChar* pszFileType);

    // returns the file type which is used to be shown in the GUI
    wxString GetFileTypeDisplayStr() const;

    const unsigned char* GetFileHash() const { return m_abyFileHash; }
    void SetFileHash(const unsigned char* pucFileHash);
    bool HasNullHash() const;

    wxUint64 GetFileSize() const { return m_nFileSize; }
    virtual void SetFileSize(wxUint64 nFileSize) { m_nFileSize = nFileSize; }
    bool IsLargeFile() const { return m_nFileSize > (wxUint64)OLD_MAX_EMULE_FILE_SIZE; }

    uint32 GetIntTagValue(wxUint8 tagname) const;
    uint32 GetIntTagValue(const char* tagname) const;
    bool GetIntTagValue(wxUint8 tagname, wxUint32& ruValue) const;
    wxUint64 GetInt64TagValue(wxUint8 tagname) const;
    wxUint64 GetInt64TagValue(const char* tagname) const;
    bool GetInt64TagValue(wxUint8 tagname, wxUint64& ruValue) const;
    void SetIntTagValue(wxUint8 tagname, wxUint32 uValue);
    void SetInt64TagValue(wxUint8 tagname, wxUint64 uValue);
    const wxString& GetStrTagValue(wxUint8 tagname) const;
    const wxString& GetStrTagValue(const char* tagname) const;
    void SetStrTagValue(wxUint8 tagname, const wxChar*);
    xTag* GetTag(wxUint8 tagname, wxUint8 tagtype) const;
    xTag* GetTag(const char* tagname, wxUint8 tagtype) const;
    xTag* GetTag(wxUint8 tagname) const;
    xTag* GetTag(const char* tagname) const;
    const std::vector<xTag*>& GetTags() const { return taglist; }
    void AddTagUnique(xTag* pTag);
    void ClearTags();
    void CopyTags(const std::vector<xTag*>& tags);
    virtual bool IsPartFile()const { return false; }

    bool HasComment() const { return m_bHasComment; }
    void SetHasComment(bool in) { m_bHasComment = in; }
    wxUint32 UserRating() const { return m_uUserRating; }
    bool HasRating() const { return m_uUserRating > 0; }
    bool HasBadRating() const { return ( HasRating() && (m_uUserRating < 2)); }
    void SetUserRating(UINT in) { m_uUserRating = in; }
    const wxString& GetFileComment();
    wxUint32 GetFileRating();
    void LoadComment();
    virtual void UpdateFileRatingCommentAvail() = 0;

    // bool AddNote(Kademlia::CEntry* pEntry); TODO:KAD
    // const CKadEntryPtrList& getNotes() const { return m_kadNotes; }

protected:
    wxString m_strFileName;
    unsigned char m_abyFileHash[16];
    wxUint64 m_nFileSize;
    wxString m_strComment;
    wxUint32 m_uRating;
    bool m_bCommentLoaded;
    wxUint32 m_uUserRating;
    bool m_bHasComment;
    wxString m_strFileType;
    std::vector<xTag*> taglist;
    // CKadEntryPtrList m_kadNotes; TODO:KAD
};

#endif // _XABSTRACTFILE_H_
