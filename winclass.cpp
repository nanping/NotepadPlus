#include "winclass.h"

const wchar_t * WcharMbcsConvertor::char2wchar(const char * mbcs2Convert, UINT codepage, int lenMbcs, int *pLenWc, int *pBytesNotProcessed)
{
    // Do not process nullptr pointer
    if (!mbcs2Convert)
        return nullptr;

    // Do not process empty strings
    if (lenMbcs == 0 || (lenMbcs == -1 && mbcs2Convert[0] == 0))
    {
        _wideCharStr.empty();
        return _wideCharStr;
    }

    int bytesNotProcessed = 0;
    int lenWc = 0;

    // If length not specified, simply convert without checking
    if (lenMbcs == -1)
    {
        lenWc = MultiByteToWideChar(codepage, 0, mbcs2Convert, lenMbcs, nullptr, 0);
    }
    // Otherwise, test if we are cutting a multi-byte character at end of buffer
    else if (lenMbcs != -1 && codepage == CP_UTF8) // For UTF-8, we know how to test it
    {
        int indexOfLastChar = Utf8::characterStart(mbcs2Convert, lenMbcs-1); // get index of last character
        if (indexOfLastChar != 0 && !Utf8::isValid(mbcs2Convert+indexOfLastChar, lenMbcs-indexOfLastChar)) // if it is not valid we do not process it right now (unless its the only character in string, to ensure that we always progress, e.g. that bytesNotProcessed < lenMbcs)
        {
            bytesNotProcessed = lenMbcs-indexOfLastChar;
        }
        lenWc = MultiByteToWideChar(codepage, 0, mbcs2Convert, lenMbcs-bytesNotProcessed, nullptr, 0);
    }
    else // For other encodings, ask system if there are any invalid characters; note that it will not correctly know if last character is cut when there are invalid characters inside the text
    {
        lenWc = MultiByteToWideChar(codepage, (lenMbcs == -1) ? 0 : MB_ERR_INVALID_CHARS, mbcs2Convert, lenMbcs, nullptr, 0);
        if (lenWc == 0 && GetLastError() == ERROR_NO_UNICODE_TRANSLATION)
        {
            // Test without last byte
            if (lenMbcs > 1) lenWc = MultiByteToWideChar(codepage, MB_ERR_INVALID_CHARS, mbcs2Convert, lenMbcs-1, nullptr, 0);
            if (lenWc == 0) // don't have to check that the error is still ERROR_NO_UNICODE_TRANSLATION, since only the length parameter changed
            {
                // TODO: should warn user about incorrect loading due to invalid characters
                // We still load the file, but the system will either strip or replace invalid characters (including the last character, if cut in half)
                lenWc = MultiByteToWideChar(codepage, 0, mbcs2Convert, lenMbcs, nullptr, 0);
            }
            else
            {
                // We found a valid text by removing one byte.
                bytesNotProcessed = 1;
            }
        }
    }

    if (lenWc > 0)
    {
        _wideCharStr.sizeTo(static_cast<size_t>(lenWc));
        MultiByteToWideChar(codepage, 0, mbcs2Convert, lenMbcs-bytesNotProcessed, _wideCharStr, lenWc);
    }
    else
        _wideCharStr.empty();

    if (pLenWc)
        *pLenWc = lenWc;
    if (pBytesNotProcessed)
        *pBytesNotProcessed = bytesNotProcessed;

    return _wideCharStr;
}


// "mstart" and "mend" are pointers to indexes in mbcs2Convert,
// which are converted to the corresponding indexes in the returned wchar_t string.
const wchar_t * WcharMbcsConvertor::char2wchar(const char * mbcs2Convert, UINT codepage, int *mstart, int *mend)
{
    // Do not process nullptr pointer
    if (!mbcs2Convert) return nullptr;

    int len = MultiByteToWideChar(codepage, 0, mbcs2Convert, -1, nullptr, 0);
    if (len > 0)
    {
        _wideCharStr.sizeTo(static_cast<size_t>(len));
        len = MultiByteToWideChar(codepage, 0, mbcs2Convert, -1, _wideCharStr, len);

        if (static_cast<size_t>(*mstart) < strlen(mbcs2Convert) && static_cast<size_t>(*mend) <= strlen(mbcs2Convert))
        {
            *mstart = MultiByteToWideChar(codepage, 0, mbcs2Convert, *mstart, _wideCharStr, 0);
            *mend   = MultiByteToWideChar(codepage, 0, mbcs2Convert, *mend, _wideCharStr, 0);
            if (*mstart >= len || *mend >= len)
            {
                *mstart = 0;
                *mend = 0;
            }
        }
    }
    else
    {
        _wideCharStr.empty();
        *mstart = 0;
        *mend = 0;
    }
    return _wideCharStr;
}


const char* WcharMbcsConvertor::wchar2char(const wchar_t * wcharStr2Convert, UINT codepage, int lenWc, int *pLenMbcs)
{
    if (nullptr == wcharStr2Convert)
        return nullptr;

    int lenMbcs = WideCharToMultiByte(codepage, 0, wcharStr2Convert, lenWc, nullptr, 0, nullptr, nullptr);
    if (lenMbcs > 0)
    {
        _multiByteStr.sizeTo(static_cast<size_t>(lenMbcs));
        WideCharToMultiByte(codepage, 0, wcharStr2Convert, lenWc, _multiByteStr, lenMbcs, nullptr, nullptr);
    }
    else
        _multiByteStr.empty();

    if (pLenMbcs)
        *pLenMbcs = lenMbcs;
    return _multiByteStr;
}


const char * WcharMbcsConvertor::wchar2char(const wchar_t * wcharStr2Convert, UINT codepage, long *mstart, long *mend)
{
    if (nullptr == wcharStr2Convert)
        return nullptr;

    int len = WideCharToMultiByte(codepage, 0, wcharStr2Convert, -1, nullptr, 0, nullptr, nullptr);
    if (len > 0)
    {
        _multiByteStr.sizeTo(static_cast<size_t>(len));
        len = WideCharToMultiByte(codepage, 0, wcharStr2Convert, -1, _multiByteStr, len, nullptr, nullptr); // not needed?

        if (*mstart < lstrlenW(wcharStr2Convert) && *mend < lstrlenW(wcharStr2Convert))
        {
            *mstart = WideCharToMultiByte(codepage, 0, wcharStr2Convert, *mstart, nullptr, 0, nullptr, nullptr);
            *mend = WideCharToMultiByte(codepage, 0, wcharStr2Convert, *mend, nullptr, 0, nullptr, nullptr);
            if (*mstart >= len || *mend >= len)
            {
                *mstart = 0;
                *mend = 0;
            }
        }
    }
    else
        _multiByteStr.empty();

    return _multiByteStr;
}
