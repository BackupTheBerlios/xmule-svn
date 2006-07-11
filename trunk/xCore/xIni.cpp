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

#include <wx/defs.h>              // wxWidgets types
#include <wx/gdicmn.h>            // wxRect
#include <wx/textfile.h>          // wxTextFile
#include <wx/tokenzr.h>           // wxStringTokenizer

#include "xIni.h"                 // Interface declarations

xIni::xIni(wxString const& FileName)
{
    LoadIni(FileName);
}

bool xIni::LoadIni(wxString const& FileName)
{
    if (!wxFileExists(FileName))
    {
        return false;
    }
    wxTextFile iniFile(FileName);
    iniFile.Open();

    wxString KeyName, ValueName, Value;
    wxUint32 pLeft, pRight;
    wxInt32 NumLines=iniFile.GetLineCount();
    for (wxInt32 i=0; i < NumLines; i++)
    {
        wxString Line = iniFile.GetLine(i);
        if ((Line.length() > 3) && (pLeft = Line.find_first_of(wxT("[="))) != wxString::npos)
        {
            switch (Line.GetChar(pLeft))
            {
                case wxT('['):
                {
                    if ((pRight = Line.find_last_of(wxT(']'))) != wxString::npos && (pRight > pLeft))
                    {
                        KeyName=Line.substr(pLeft + 1, pRight - pLeft - 1);
                        AddKeyName(KeyName);
                    }
                    break;
                }
                case wxT('='):
                {
                    ValueName = Line.substr(0, pLeft);
                    Value = Line.substr(pLeft + 1);
                    SetValue(KeyName, ValueName, Value);
                    break;
                }
            } // Close switch statement
        } // Close if statement
    } // Close for loop
    iniFile.Close();
    if (Keys.size())
    {
        return true;
    }
    return false;
}

bool xIni::SaveIni(wxString const& FileName)
{
    if (wxFileExists(FileName))
    {
        if (!wxRemoveFile(FileName))
        {
            return false;
        }
    }
    wxTextFile iniFile(FileName);
    iniFile.Create();

    // Write Keys and Values.
    wxInt32 NumKeys=Keys.size();
    for (wxInt32 keyID = 0; keyID < NumKeys; keyID++)
    {
        wxString KeyLine = wxT('[') + Keys.at(keyID).KeyName + wxT(']');
        if (keyID != 0)
        {
            iniFile.AddLine(wxT(""),wxTextFileType_Dos);
        }
        iniFile.AddLine(KeyLine,wxTextFileType_Dos);
        wxInt32 NumValues=Keys.at(keyID).ValueNames.size();
        for (wxInt32 ValueID = 0; ValueID < NumValues; ValueID++)
        {
            wxString ValueLine = Keys.at(keyID).ValueNames.at(ValueID) +wxT('=') + Keys.at(keyID).Values.at(ValueID);
            iniFile.AddLine(ValueLine, wxTextFileType_Dos);
        }
    }
    return (iniFile.Write(wxTextFileType_Dos));
}

void xIni::Clear()
{
    Keys.clear();
}

wxInt32 xIni::AddKeyName(wxString const& aKeyName)
{
    wxInt32 Find=FindKeyID(aKeyName);
    if (Find >= 0)
    {
        return Find;
    }
    Key NewKey;
    NewKey.KeyName=aKeyName;
    Keys.push_back(NewKey);
    return (Keys.size() - 1);
}

wxInt32 xIni::FindKeyID(wxString const& aKeyName) const
{
    for (wxUint32 i = 0; i < Keys.size(); i++)
    {
        if (Keys.at(i).KeyName==aKeyName)
        {
            return i;
        }
    }
    return ((wxInt32)-1);
}

wxInt32 xIni::FindValueID(wxInt32 const keyID, wxString const& aValueName) const
{
    for (wxUint32 i = 0; i < Keys.at(keyID).ValueNames.size(); i++)
    {
        if (Keys.at(keyID).ValueNames.at(i) == aValueName)
        {
            return i;
        }
    }
    return ((wxInt32)-1);
}


// Value Mutators

bool xIni::SetValue(wxString const& KeyName, wxString const& ValueName, wxString const& Value)
{
    wxInt32 keyID = FindKeyID(KeyName);
    Keys.at(keyID).ValueNames.push_back(ValueName);
    Keys.at(keyID).Values.push_back(Value);
    return true;
}

bool xIni::SetValue(wxString const& KeyName, wxString const& ValueName, wxInt32 const Value)
{
    wxString ValueToSet= wxString::Format(wxT("%d"), Value);
    return SetValue(KeyName, ValueName, ValueToSet);
}

bool xIni::SetValue(wxString const& KeyName, wxString const& ValueName, wxUint32 const Value)
{
    wxString ValueToSet= wxString::Format(wxT("%d"), Value);
    return SetValue(KeyName, ValueName, ValueToSet);
}

bool xIni::SetValue(wxString const& KeyName, wxString const& ValueName, float const Value)
{
    wxString ValueToSet= wxString::Format(wxT("%f"), Value);
    return SetValue(KeyName, ValueName, ValueToSet);
}

bool xIni::SetValue(wxString const& KeyName, wxString const& ValueName, double const Value)
{
    wxString ValueToSet= wxString::Format(wxT("%f"), Value);
    return SetValue(KeyName, ValueName, ValueToSet);
}

bool xIni::SetValue(wxString const& KeyName, wxString const& ValueName, wxRect const& Value)
{
    wxString ValueToSet=wxString::Format(wxT("%d,%d,%d,%d"), Value.GetX(), Value.GetY(), Value.GetWidth(), Value.GetHeight());
    return SetValue(KeyName, ValueName, ValueToSet);
}

// Values accessors

wxString xIni::GetValue(wxString const& KeyName, wxString const& ValueName, wxString const& defValue) const
{
    wxInt32 keyID = FindKeyID(KeyName);
    if (keyID == -1)
    {
        return defValue;
    }
    wxInt32 valueID = FindValueID(keyID, ValueName);
    if (valueID == -1)
    {
        return defValue;
    }
    return Keys.at(keyID).Values.at(valueID);
}

wxInt32 xIni::GetValue(wxString const& KeyName, wxString const& ValueName, wxInt32 const defValue) const
{
    wxString defStValue=wxString::Format(wxT("%d"), defValue);
    wxString value=GetValue(KeyName, ValueName, defStValue);
    long result;
    value.ToLong(&result);
    return (wxInt32)result;
}

wxUint32 xIni::GetValue(wxString const& KeyName, wxString const& ValueName, wxUint32 const defValue) const
{
    wxString defStValue=wxString::Format(wxT("%d"), defValue);
    wxString value=GetValue(KeyName, ValueName, defStValue);
    unsigned long result;
    value.ToULong(&result);
    return (wxUint32)result;
}

float xIni::GetValue(wxString const& KeyName, wxString const& ValueName, float const defValue) const
{
    wxString defStValue=wxString::Format(wxT("%f"), defValue);
    wxString value=GetValue(KeyName, ValueName, defStValue);
    double result;
    value.ToDouble(&result);
    return (float)result;
}

double xIni::GetValue(wxString const& KeyName, wxString const& ValueName, double const defValue) const
{
    wxString defStValue=wxString::Format(wxT("%f"), defValue);
    wxString value=GetValue(KeyName, ValueName, defStValue);
    double result;
    value.ToDouble(&result);
    return result;
}

wxRect xIni::GetValue(wxString const& KeyName, wxString const& ValueName, wxRect const& defValue) const
{
    wxString defStValue=wxString::Format(wxT("%d,%d,%d,%d"), defValue.GetX(), defValue.GetY(), defValue.GetWidth(), defValue.GetHeight());
    wxString value=GetValue(KeyName, ValueName, defStValue);
    wxStringTokenizer tkz(value, wxT(","));
    wxRect toReturn;
    wxInt8 Flag=1;
    while (tkz.HasMoreTokens())
    {
        wxString token = tkz.GetNextToken();
        long Number;
        token.ToLong(&Number);
        switch (Flag)
        {
            case 1:
            {
                toReturn.SetX(Number);
                break;
            }
            case 2:
            {
                toReturn.SetY(Number);
                break;
            }
            case 3:
            {
                toReturn.SetWidth(Number);
                break;
            }
            case 4:
            {
                toReturn.SetHeight(Number);
                break;
            }
        }
        Flag++;
    }
    return toReturn;
}
