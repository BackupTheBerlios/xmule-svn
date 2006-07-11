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

#ifndef XINI_H
#define XINI_H

#include <vector>

class xIni
{
public:
    xIni() { }
    xIni(wxString const& FileName);
    ~xIni() { Keys.clear(); }

    bool LoadIni(wxString const& FileName);
    bool SaveIni(wxString const& FileName);

    void Clear(); // Deletes all stored ini buffer.

    wxInt32 AddKeyName(wxString const& aKeyName);

    wxInt32 FindKeyID(wxString const& aKeyName) const;
    wxInt32 FindValueID(wxInt32 const keyID, wxString const& aValueName) const;

    bool SetValue(wxString const& KeyName, wxString const& ValueName, wxString const& Value);
    bool SetValue(wxString const& KeyName, wxString const& ValueName, wxInt32 const Value);
    bool SetValue(wxString const& KeyName, wxString const& ValueName, wxUint32 const Value);
    bool SetValue(wxString const& KeyName, wxString const& ValueName, float const Value);
    bool SetValue(wxString const& KeyName, wxString const& ValueName, double const Value);
    bool SetValue(wxString const& KeyName, wxString const& ValueName, wxRect const& Value);

    wxString GetValue(wxString const& KeyName, wxString const& ValueName, wxString const& defValue) const;
    wxInt32 GetValue(wxString const& KeyName, wxString const& ValueName, wxInt32 const defValue) const;
    wxUint32 GetValue(wxString const& KeyName, wxString const& ValueName, wxUint32 const defValue) const;
    float GetValue(wxString const& KeyName, wxString const& ValueName, float const defValue) const;
    double GetValue(wxString const& KeyName, wxString const& ValueName, double const defValue) const;
    wxRect GetValue(wxString const& KeyName, wxString const& ValueName, wxRect const& defValue) const;

private:
    struct Key
    {
        wxString KeyName;
        std::vector<wxString>ValueNames;
        std::vector<wxString>Values;
    };
    std::vector<Key> Keys;
};

#endif // XINI_H
