#ifndef WINCLASS_H
#define WINCLASS_H

#include <windows.h>
#include "Utf8.h"

class WcharMbcsConvertor final
{
public:
    static WcharMbcsConvertor& getInstance() {
        static WcharMbcsConvertor instance;
        return instance;
    }

    const wchar_t * char2wchar(const char *mbStr, UINT codepage, int lenIn=-1, int *pLenOut=nullptr, int *pBytesNotProcessed=nullptr);
    const wchar_t * char2wchar(const char *mbcs2Convert, UINT codepage, int *mstart, int *mend);
    const char * wchar2char(const wchar_t *wcStr, UINT codepage, int lenIn = -1, int *pLenOut = nullptr);
    const char * wchar2char(const wchar_t *wcStr, UINT codepage, long *mstart, long *mend);

    const char * encode(UINT fromCodepage, UINT toCodepage, const char *txt2Encode, int lenIn=-1, int *pLenOut=nullptr, int *pBytesNotProcessed=nullptr)
    {
        int lenWc = 0;
        const wchar_t * strW = char2wchar(txt2Encode, fromCodepage, lenIn, &lenWc, pBytesNotProcessed);
        return wchar2char(strW, toCodepage, lenWc, pLenOut);
    }

protected:
    WcharMbcsConvertor() = default;
    ~WcharMbcsConvertor() = default;

    // Since there's no public ctor, we need to void the default assignment operator and copy ctor.
    // Since these are marked as deleted does not matter under which access specifier are kept
    WcharMbcsConvertor(const WcharMbcsConvertor&) = delete;
    WcharMbcsConvertor& operator= (const WcharMbcsConvertor&) = delete;

    // No move ctor and assignment
    WcharMbcsConvertor(WcharMbcsConvertor&&) = delete;
    WcharMbcsConvertor& operator= (WcharMbcsConvertor&&) = delete;

    template <class T>
    class StringBuffer final
    {
    public:
        ~StringBuffer() { if (_allocLen) delete[] _str; }

        void sizeTo(size_t size)
        {
            if (_allocLen < size)
            {
                if (_allocLen)
                    delete[] _str;
                _allocLen =size>initSize ? size:initSize;
                _str = new T[_allocLen];
            }
        }

        void empty()
        {
            static T nullStr = 0; // routines may return an empty string, with null terminator, without allocating memory; a pointer to this null character will be returned in that case
            if (_allocLen == 0)
                _str = &nullStr;
            else
                _str[0] = 0;
        }

        operator T* () { return _str; }
        operator const T* () const { return _str; }

    protected:
        static const int initSize = 1024;
        size_t _allocLen = 0;
        T* _str = nullptr;
    };

    StringBuffer<char> _multiByteStr;
    StringBuffer<wchar_t> _wideCharStr;
};


#endif // WINCLASS_H
