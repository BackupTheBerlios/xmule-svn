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

// Status: eMule 0.47c (TODO:KAD, TODO:FILE COMMENTS)

#include "xAbstractFile.h"             // xAbstractFile
#include "xUtils.h"                    // md4cpy(), md4clr()

//#include "OtherFunctions.h"
//#include "Kademlia/Kademlia/Entry.h"
//#include "ini2.h"
//#include "Preferences.h"
//#include "Packets.h"

xAbstractFile::xAbstractFile()
{
    md4clr(m_abyFileHash);
    m_nFileSize = (wxUint64)0;
    m_uRating = 0;
    m_bCommentLoaded = false;
    m_uUserRating = 0;
    m_bHasComment = false;
    // m_bKadCommentSearchRunning = false; TODO:KAD
}

xAbstractFile::xAbstractFile(const xAbstractFile* pAbstractFile)
{
    m_strFileName = pAbstractFile->m_strFileName;
    md4cpy(m_abyFileHash, pAbstractFile->GetFileHash());
    m_nFileSize = pAbstractFile->m_nFileSize;
    m_strComment = pAbstractFile->m_strComment;
    m_uRating = pAbstractFile->m_uRating;
    m_bCommentLoaded = pAbstractFile->m_bCommentLoaded;
    m_uUserRating = pAbstractFile->m_uUserRating;
    m_bHasComment = pAbstractFile->m_bHasComment;
    m_strFileType = pAbstractFile->m_strFileType;
/*	m_bKadCommentSearchRunning = pAbstractFile->m_bKadCommentSearchRunning; TODO:KAD

    const CTypedPtrList<CPtrList, Kademlia::CEntry*>& list = pAbstractFile->getNotes();
    for(POSITION pos = list.GetHeadPosition(); pos != NULL; )
    {
        Kademlia::CEntry* entry = list.GetNext(pos);
        m_kadNotes.AddTail(entry->Copy());
    }*/

    CopyTags(pAbstractFile->GetTags());
}

xAbstractFile::~xAbstractFile()
{
    ClearTags();
/*    for(POSITION pos = m_kadNotes.GetHeadPosition(); pos != NULL; ) TODO:KAD
    {
        Kademlia::CEntry* entry = m_kadNotes.GetNext(pos);
        delete entry;
    }*/
}

/*bool xAbstractFile::AddNote(Kademlia::CEntry* pEntry) TODO:KAD
{
    for(POSITION pos = m_kadNotes.GetHeadPosition(); pos != NULL; )
    {
        Kademlia::CEntry* entry = m_kadNotes.GetNext(pos);
        if(entry->m_uSourceID == pEntry->m_uSourceID)
        {
            ASSERT(entry != pEntry);
            return false;
        }
    }
    m_kadNotes.AddHead(pEntry);
    UpdateFileRatingCommentAvail();
    return true;
}*/

wxUint32 xAbstractFile::GetFileRating()
{
    if (!m_bCommentLoaded)
    {
        LoadComment();
    }
    return m_uRating;
}

const wxString& xAbstractFile::GetFileComment()
{
    if (!m_bCommentLoaded)
    {
        LoadComment();
    }
    return m_strComment;
}

void xAbstractFile::LoadComment()
{
/*    CIni ini(thePrefs.GetFileCommentsFilePath(), md4str(GetFileHash())); TODO:FILE COMMENTS
    m_strComment = ini.GetStringUTF8(_T("Comment")).Left(MAXFILECOMMENTLEN);
    m_uRating = ini.GetInt(_T("Rate"), 0);
    m_bCommentLoaded = true;*/
}

void xAbstractFile::CopyTags(const std::vector<xTag*>& tags)
{
    for (int i = 0; i < tags.size(); i++)
    {
        taglist.push_back(new xTag(*tags[i]));
    }
}

void xAbstractFile::ClearTags()
{
    for (int i = 0; i < taglist.size(); i++)
    {
        delete taglist[i];
    }
    taglist.clear();
}

void xAbstractFile::AddTagUnique(xTag* pTag)
{
    for (int i = 0; i < taglist.size(); i++)
    {
        const xTag* pCurTag = taglist[i];
        if ((  (pCurTag->GetNameID()!=0 && pCurTag->GetNameID()==pTag->GetNameID())
            || (pCurTag->GetName()!=NULL && pTag->GetName()!=NULL && CmpED2KTagName(pCurTag->GetName(), pTag->GetName())==0)
            )
            && pCurTag->GetType() == pTag->GetType())
        {
            delete pCurTag;
            taglist[i]=pTag;
            return;
        }
    }
    taglist.push_back(pTag);
}

void xAbstractFile::SetFileName(const wxChar* pszFileName, bool bReplaceInvalidFileSystemChars, bool bAutoSetFileType)
{
    m_strFileName = pszFileName;
    if (bReplaceInvalidFileSystemChars)
    {
        m_strFileName.Replace(wxT('/'), wxT('-'));
        m_strFileName.Replace(wxT('>'), wxT('-'));
        m_strFileName.Replace(wxT('<'), wxT('-'));
        m_strFileName.Replace(wxT('*'), wxT('-'));
        m_strFileName.Replace(wxT(':'), wxT('-'));
        m_strFileName.Replace(wxT('?'), wxT('-'));
        m_strFileName.Replace(wxT('\"'), wxT('-'));
        m_strFileName.Replace(wxT('\\'), wxT('-'));
        m_strFileName.Replace(wxT('|'), wxT('-'));
    }
    if (bAutoSetFileType)
    {
        SetFileType(GetFileTypeByName(m_strFileName));
    }
}

void xAbstractFile::SetFileType(const wxChar* pszFileType)
{
    m_strFileType = pszFileType;
}

wxString xAbstractFile::GetFileTypeDisplayStr()const
{
    wxString strFileTypeDisplayStr(GetFileTypeDisplayStrFromED2KFileType(GetFileType()));
    if (strFileTypeDisplayStr.empty())
    {
        strFileTypeDisplayStr = GetFileType();
    }
    return strFileTypeDisplayStr;
}


void xAbstractFile::SetFileHash(const unsigned char* pucFileHash)
{
    md4cpy(m_abyFileHash, pucFileHash);
}

bool xAbstractFile::HasNullHash() const
{
    return isnulmd4(m_abyFileHash);
}

wxUint32 xAbstractFile::GetIntTagValue(wxUint8 tagname) const
{
    for (int i = 0; i < taglist.size(); i++)
    {
        const xTag* pTag = taglist[i];
        if (pTag->GetNameID() == tagname && pTag->IsInt())
        {
            return pTag->GetInt();
        }
    }
    return 0;
}

bool xAbstractFile::GetIntTagValue(wxUint8 tagname, wxUint32& ruValue) const
{
    for (int i = 0; i < taglist.size(); i++)
    {
        const xTag* pTag = taglist[i];
        if (pTag->GetNameID() == tagname && pTag->IsInt())
        {
            ruValue = pTag->GetInt();
            return true;
        }
    }
    return false;
}

wxUint64 xAbstractFile::GetInt64TagValue(const char* tagname) const
{
    for (int i = 0; i < taglist.size(); i++)
    {
        const xTag* pTag = taglist[i];
        if (pTag->GetNameID() == 0 && pTag->IsInt64(true) && CmpED2KTagName(pTag->GetName(), tagname) == 0)
        {
            return pTag->GetInt64();
        }
    }
    return 0;
}

wxUint64 xAbstractFile::GetInt64TagValue(wxUint8 tagname) const
{
    for (int i = 0; i < taglist.size(); i++)
    {
        const xTag* pTag = taglist[i];
        if (pTag->GetNameID() == tagname && pTag->IsInt64(true))
        {
            return pTag->GetInt64();
        }
    }
    return 0;
}

bool xAbstractFile::GetInt64TagValue(wxUint8 tagname, wxUint64& ruValue) const
{
    for (int i = 0; i < taglist.size(); i++)
    {
        const xTag* pTag = taglist[i];
        if (pTag->GetNameID() == tagname && pTag->IsInt64(true))
        {
            ruValue = pTag->GetInt64();
            return true;
        }
    }
    return false;
}

wxUint32 xAbstractFile::GetIntTagValue(const char* tagname) const
{
    for (int i = 0; i < taglist.size(); i++)
    {
        const xTag* pTag = taglist[i];
        if (pTag->GetNameID() == 0 && pTag->IsInt() && CmpED2KTagName(pTag->GetName(), tagname) == 0)
        {
            return pTag->GetInt();
        }
    }
    return 0;
}

void xAbstractFile::SetIntTagValue(wxUint8 tagname, wxUint32 uValue)
{
    for (int i = 0; i < taglist.size(); i++)
    {
        xTag* pTag = taglist[i];
        if (pTag->GetNameID() == tagname && pTag->IsInt())
        {
            pTag->SetInt(uValue);
            return;
        }
    }
    xTag* pTag = new xTag(tagname, uValue);
    taglist.push_back(pTag);
}

void xAbstractFile::SetInt64TagValue(wxUint8 tagname, wxUint64 uValue)
{
    for (int i = 0; i < taglist.size(); i++)
    {
        xTag* pTag = taglist[i];
        if (pTag->GetNameID() == tagname && pTag->IsInt64(true))
        {
            pTag->SetInt64(uValue);
            return;
        }
    }
    xTag* pTag = new xTag(tagname, uValue);
    taglist.push_back(pTag);
}

const wxString& xAbstractFile::GetStrTagValue(wxUint8 tagname) const
{
    for (int i = 0; i < taglist.size(); i++)
    {
        const xTag* pTag = taglist[i];
        if (pTag->GetNameID() == tagname && pTag->IsStr())
        {
            return pTag->GetStr();
        }
    }
    return wxEmptyString;
}

const wxString& xAbstractFile::GetStrTagValue(const char* tagname) const
{
    for (int i = 0; i < taglist.size(); i++)
    {
        const xTag* pTag = taglist[i];
        if (pTag->GetNameID() == 0 && pTag->IsStr() && CmpED2KTagName(pTag->GetName(), tagname) == 0)
        {
            return pTag->GetStr();
        }
    }
    return wxEmptyString;
}

void xAbstractFile::SetStrTagValue(wxUint8 tagname, const wxChar* pszValue)
{
    for (int i = 0; i < taglist.size(); i++)
    {
        xTag* pTag = taglist[i];
        if (pTag->GetNameID() == tagname && pTag->IsStr())
        {
            pTag->SetStr(pszValue);
            return;
        }
    }
    xTag* pTag = new xTag(tagname, pszValue);
    taglist.push_back(pTag);
}

xTag* xAbstractFile::GetTag(wxUint8 tagname, wxUint8 tagtype) const
{
    for (int i = 0; i < taglist.size(); i++)
    {
        xTag* pTag = taglist[i];
        if (pTag->GetNameID() == tagname && pTag->GetType() == tagtype)
        {
            return pTag;
        }
    }
    return NULL;
}

xTag* xAbstractFile::GetTag(const char* tagname, wxUint8 tagtype) const
{
    for (int i = 0; i < taglist.size(); i++)
    {
        xTag* pTag = taglist[i];
        if (pTag->GetNameID() == 0 && pTag->GetType() == tagtype && CmpED2KTagName(pTag->GetName(), tagname) == 0)
        {
            return pTag;
        }
    }
    return NULL;
}

xTag* xAbstractFile::GetTag(wxUint8 tagname) const
{
    for (int i = 0; i < taglist.size(); i++)
    {
        xTag* pTag = taglist[i];
        if (pTag->GetNameID() == tagname)
        {
            return pTag;
        }
    }
    return NULL;
}

xTag* xAbstractFile::GetTag(const char* tagname) const
{
    for (int i = 0; i < taglist.size(); i++)
    {
        xTag* pTag = taglist[i];
        if (pTag->GetNameID() == 0 && CmpED2KTagName(pTag->GetName(), tagname) == 0)
        {
            return pTag;
        }
    }
    return NULL;
}

void xAbstractFile::DeleteTag(xTag* pTag)
{
    for (int i = 0; i < taglist.size(); i++)
    {
        if (taglist[i] == pTag)
        {
            taglist.RemoveAt(i);
            delete pTag;
            return;
        }
    }
}

void xAbstractFile::DeleteTag(wxUint8 tagname)
{
	for (int i = 0; i < taglist.GetSize(); i++)
    {
        xTag* pTag = taglist[i];
        if (pTag->GetNameID() == tagname)
        {
            taglist.RemoveAt(i);
            delete pTag;
            return;
        }
    }
}

/*void xAbstractFile::SetKadCommentSearchRunning(bool bVal){ TODO:KAD
	if (bVal != m_bKadCommentSearchRunning){
		m_bKadCommentSearchRunning = bVal;
		UpdateFileRatingCommentAvail(true);
	}
}*/
