#include "tools.h"


void msgboxWarn(const QString &text, const QString &title,QWidget *parent)
{
    QMessageBox::warning(parent,title,text);
}

void msgboxInfo(const QString &text, const QString &title, QWidget *parent)
{
    QMessageBox::information(parent,title,text);
}

void msgboxErr(const QString &text, const QString &title, QWidget *parent)
{
    QMessageBox::critical(parent,title,text);
}

int msgboxQst(const QString &text, const QString &title, QWidget *parent,QMessageBox::StandardButtons buttons,QMessageBox::StandardButton defaultButton)
{
    return QMessageBox::question(parent,title,text,buttons,defaultButton);
}

const QString pathCombine(std::initializer_list<QString> lst) noexcept
{
    QString result="";
    for(auto &a:lst)
    {
        if(a.isEmpty()) continue;
        if(!a.startsWith(QDir::separator()))
        {
            if(!result.isEmpty() && !result.endsWith(QDir::separator()))
            {
                result.append(QDir::separator());
            }
            result.append(a);
        }else{
            result.append(a.mid(1));
        }
    }
    return result;
}

bool fileExists(const QString &fileName)
{
    QFileInfo file(fileName);
    if(!file.exists()) return false;
    return file.isFile();
}

bool pathExists(const QString &fileName)
{
    QFileInfo file(fileName);
    if(!file.exists()) return false;
    return file.isDir();
}

bool encodeConvert(const char *codeFrom,const char *codeTo,const char *inbuf,const size_t inlen, std::string &out,int *pBytesNotProcessed)
{
    //    size_t tmplen=inlen;
    //    int bytesNotProcessed = 0;//没有转换的字符个数
    //    if(compare(codeFrom,"UTF-8"))
    //    {
    //        int indexOfLastChar=Utf8::characterStart(inbuf,static_cast<int>(inlen)-1);//获取最后一个字符的位置
    //        if(indexOfLastChar!=0 && !Utf8::isValid(inbuf+indexOfLastChar,static_cast<int>(inlen)-indexOfLastChar))//判断indexOfLastChar之后的字符是否有效
    //        {
    //            bytesNotProcessed=static_cast<int>(inlen)-indexOfLastChar;//从indexOfLastChar开始无效的字符数
    //        }
    //        tmplen=inlen-static_cast<size_t>(bytesNotProcessed);//实际要处理的字符长度(不包含无效字符)
    //    }
    //    /* 目的编码, TRANSLIT ：遇到无法转换的字符就找相近字符替换
    //     *          IGNORE  ：遇到无法转换字符跳过*/
    //    std::string encTo=codeTo;
    //    encTo+="//IGNORE";

    //    //获得转换句柄
    //    iconv_t cd = iconv_open(encTo.c_str(), codeFrom);
    //    if(cd==(iconv_t)-1) return false;

    //    size_t outlen=inlen*2;
    //    char *outbuf=new char[outlen];
    //    memset(outbuf,0,outlen);

    //    //由于iconv()函数会修改指针，所以要保存源指针
    //    char *tmpin =const_cast<char *>(inbuf);
    //    char *tmpout = outbuf;


    //    size_t ret = iconv(cd, &tmpin, &tmplen, &tmpout, &outlen);
    //    out=outbuf;
    //    if(pBytesNotProcessed)
    //    {
    //        *pBytesNotProcessed=bytesNotProcessed;
    //    }
    //    /*
    //        1.inbuf中碰到非法的多字节序
    //        这种状况下,会设置errno为EILSEQ,并返回-1;
    //        2.inbuf字节被完全转换
    //        这种状况下,返回转换的字节数
    //        3.inbuf中碰到不完整的多字节序
    //        这种状况下,设置errno为EINVAL,并返回-1;
    //        4.outbuf中没有足够的空间以进行下一次的字符转换
    //        这种状况下,设置errno为E2BIG,并返回-1;
    //    */
    //    iconv_close(cd);
    //    return (ret !=(size_t)-1);
    return true;
}

const std::string ws2s( const std::wstring& src,bool &success,const std::locale &sys_locale)
{
    const wchar_t* data_from = src.c_str();
    const wchar_t* data_from_end = src.c_str() + src.size();
    const wchar_t* data_from_next = nullptr;

    unsigned int wchar_size = 4;
    char* data_to = new char[(src.size() + 1) * wchar_size];
    char* data_to_end = data_to + (src.size() + 1) * wchar_size;
    char* data_to_next = nullptr;

    memset( data_to, 0, (src.size() + 1) * wchar_size );

    typedef std::codecvt<wchar_t, char, mbstate_t> convert_facet;
    mbstate_t out_state = 0;
    auto result = std::use_facet<convert_facet>(sys_locale).out(
                out_state, data_from, data_from_end, data_from_next,
                data_to, data_to_end, data_to_next );
    if( result == convert_facet::ok )
    {
        success=true;
        std::string dst = data_to;
        delete[] data_to;
        return dst;
    }
    else
    {
        success=false;
        delete[] data_to;
        return std::string("");
    }
}

const std::wstring s2ws( const std::string& src,bool &success,const std::locale &sys_locale)
{
    const char* data_from = src.c_str();
    const char* data_from_end = src.c_str() + src.size();
    const char* data_from_next = nullptr;

    wchar_t* data_to = new wchar_t[src.size() + 1];
    wchar_t* data_to_end = data_to + src.size() + 1;
    wchar_t* data_to_next = nullptr;

    wmemset( data_to, 0, src.size() + 1 );

    typedef std::codecvt<wchar_t, char, mbstate_t> convert_facet;
    mbstate_t in_state = 0;
    auto result = std::use_facet<convert_facet>(sys_locale).in(
                in_state, data_from, data_from_end, data_from_next,
                data_to, data_to_end, data_to_next );
    if( result == convert_facet::ok )
    {
        success=true;
        std::wstring dst = data_to;
        delete[] data_to;
        return dst;
    }
    else
    {
        success=false;
        delete[] data_to;
        return std::wstring(L"");
    }
}
//unicode转换成UTF-8
const std::string ws2utf8( const std::wstring& src )
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    return conv.to_bytes( src );
}
//UTF-8转换成unicode
const std::wstring utf8_2_ws( const std::string& src )
{
    std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
    return conv.from_bytes( src );
}

const QString detectEncode(const char *buf, const size_t len)
{
    uchardet_t ud=uchardet_new();
    //如果样本字符不够，有可能分析失败
    if(uchardet_handle_data(ud, buf, len)!=0)
    {
        uchardet_delete(ud);
        return QString("");
    }
    uchardet_data_end(ud);
    const char* cs = uchardet_get_charset(ud);
    uchardet_delete(ud);
    return QString(cs);
}

bool compare(const std::string &str1,const std::string &str2,const bool ignoreCase)
{
    if(str1.size()!=str2.size()) return false;
    auto it1=str1.begin();
    auto it2=str2.begin();
    if(ignoreCase)
    {
        while(it1!=str1.end() && it2!=str2.end() && (*it1==*it2 || ::toupper(*it1)==::toupper(*it2)))
        {
            ++it1;
            ++it2;
        }
    }
    else{
        while(it1!=str1.end() && it2!=str2.end() && (*it1==*it2))
        {
            ++it1;
            ++it2;
        }
    }
    return (it1==str1.end() && it2==str2.end());
}

const std::string encode(const char *fromCode, const char *toCode, const char *txt2Encode, int lenIn, int *pBytesNotProcessed)
{
#ifdef Q_OS_WIN
    int fromCodepage=EncodingMapper::getInstance().getEncodingFromString(fromCode);
    int toCodepage=EncodingMapper::getInstance().getEncodingFromString(toCode);
    WcharMbcsConvertor& wmc = WcharMbcsConvertor::getInstance();
    int newDataLen = 0;
    const char *newData = wmc.encode(static_cast<UINT>(fromCodepage), static_cast<UINT>(toCodepage), txt2Encode, static_cast<int32_t>(lenIn), &newDataLen, pBytesNotProcessed);
    return std::string(newData);
#else
    return std::string(txt2Encode);//暂未实现
#endif
}

