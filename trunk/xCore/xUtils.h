#ifndef _XUTILS_H_
#define _XUTILS_H_

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
