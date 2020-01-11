#include "buffer.h"
#include "tools.h"


static Parameters *pParameter=Parameters::getInstancePtr();

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

const int blockSize=128*1024+4;
const int CR=0x0D;
const int LF=0x0A;

const unsigned char k_Boms[][3] = {
    {0x00, 0x00, 0x00},  // Unknown
    {0xEF, 0xBB, 0xBF},  // UTF8
    {0xFE, 0xFF, 0x00},  // Big endian
    {0xFF, 0xFE, 0x00},  // Little endian
};

namespace // anonymous
{
static EolType getEOLFormatForm(const char* const data, size_t length, EolType defvalue = EolType::osdefault)
{
    assert(length == 0 or data != nullptr && "invalid buffer for getEOLFormatForm()");

    for (size_t i = 0; i != length; ++i)
    {
        if (data[i] == CR)
        {
            if (i + 1 < length && data[i + 1] == LF)
                return EolType::windows;

            return EolType::macos;
        }

        if (data[i] == LF)
            return EolType::unix;
    }

    return defvalue; // fallback unknown
}
} // anonymous namespace

void FileManager::init(QsciScintilla *_pEdit)
{
    pEdit=_pEdit;
    pEdit->SendScintilla(QsciScintilla::SCI_SETUNDOCOLLECTION,false);
    _scratchDocDefault=pEdit->SendScintillaPtrResult(QsciScintilla::SCI_GETDOCPOINTER);
    pEdit->SendScintilla(QsciScintilla::SCI_ADDREFDOCUMENT,0,_scratchDocDefault);
}

LangType FileManager::detectLanguageFromTextBegining(const unsigned char *data, const size_t dataLen)
{
    struct FirstLineLanguages
    {
        std::string pattern;
        LangType lang;
    };

    // Is the buffer at least the size of a BOM?
    if (dataLen <= 3)
        return L_TEXT;

    // Eliminate BOM if present
    size_t i = 0;
    if ((data[0] == 0xEF && data[1] == 0xBB && data[2] == 0xBF) || // UTF8 BOM
            (data[0] == 0xFE && data[1] == 0xFF && data[2] == 0x00) || // UTF16 BE BOM
            (data[0] == 0xFF && data[1] == 0xFE && data[2] == 0x00))   // UTF16 LE BOM
        i += 3;

    // Skip any space-like char
    for (; i < dataLen; ++i)
    {
        if (data[i] != ' ' && data[i] != '\t' && data[i] != '\n' && data[i] != '\r')
            break;
    }

    // Create the buffer to need to test
    const size_t longestLength = 40; // shebangs can be large
    std::string buf2Test = std::string((const char *)data + i, longestLength);

    // Is there a \r or \n in the buffer? If so, truncate it
    auto cr = buf2Test.find("\r");
    auto nl = buf2Test.find("\n");
    auto crnl = min(cr, nl);
    if (crnl != std::string::npos && crnl < longestLength)
        buf2Test = std::string((const char *)data + i, crnl);

    // First test for a Unix-like Shebang
    // See https://en.wikipedia.org/wiki/Shebang_%28Unix%29 for more details about Shebang
    std::string shebang = "#!";

    size_t foundPos = buf2Test.find(shebang);
    if (foundPos == 0)
    {
        // Make a list of the most commonly used languages
        const size_t NB_SHEBANG_LANGUAGES = 6;
        FirstLineLanguages ShebangLangs[NB_SHEBANG_LANGUAGES] = {
            { "sh",		L_BASH },
            { "python", L_PYTHON },
            { "perl",	L_PERL },
            { "php",	L_PHP },
            { "ruby",	L_RUBY },
            { "node",	L_JAVASCRIPT }
        };

        // Go through the list of languages
        for (i = 0; i < NB_SHEBANG_LANGUAGES; ++i)
        {
            if (buf2Test.find(ShebangLangs[i].pattern) != std::string::npos)
            {
                return ShebangLangs[i].lang;
            }
        }

        // Unrecognized shebang (there is always room for improvement ;-)
        return L_TEXT;
    }

    // Are there any other patterns we know off?
    const size_t NB_FIRST_LINE_LANGUAGES = 5;
    FirstLineLanguages languages[NB_FIRST_LINE_LANGUAGES] = {
        { "<?xml",			L_XML },
        { "<?php",			L_PHP },
        { "<html",			L_HTML },
        { "<!DOCTYPE html",	L_HTML },
        { "<?",				L_PHP } // MUST be after "<?php" and "<?xml" to get the result as accurate as possible
    };

    for (i = 0; i < NB_FIRST_LINE_LANGUAGES; ++i)
    {
        foundPos = buf2Test.find(languages[i].pattern);
        if (foundPos == 0)
        {
            return languages[i].lang;
        }
    }

    // Unrecognized first line, we assume it is a text file for now
    return L_TEXT;
}

Buffer *FileManager::loadFile(const QString &fileName,Document doc,const QString &encoding)
{
    bool ownDoc = false;
    if(!doc)
    {
        doc=pEdit->SendScintillaPtrResult(QsciScintilla::SCI_CREATEDOCUMENT);
        ownDoc=true;
    }
    FileFormat fileFmt;
    fileFmt.encoding=encoding;
    fileFmt.eolFormat=EolType::unknown;
    fileFmt.language=L_TEXT;
    bool res=loadFileData(doc,fileName,fileFmt);
    if(res)
    {
        //Buffer *newBuf=new Buffer();

    }
    return nullptr;
}

Buffer *FileManager::newEmptyDocument()
{
    //    Buffer *buf=new Buffer();
    //    buf->doc= pEdit->SendScintillaPtrResult(QsciScintilla::SCI_CREATEDOCUMENT);
    //    buf->fileName=QString("new %1").arg(++uSaveNewFileCount);
    //    buf->currentStatus=DOC_UNNAMED;
    //    _buffers.push_back(buf);
    //    return buf;
    return nullptr;
}

bool FileManager::loadFileData(Document doc, const QString &filename, FileManager::FileFormat &fileFormat)
{
    FILE *fp=_wfopen(filename.toStdWString().c_str(),L"rb");
    if(!fp) return false;
    //获取文件大小
    _fseeki64(fp,0,SEEK_END);
    auto fileSize=_ftelli64(fp);
    rewind(fp);//将位置从新定位到文件的开头
    auto bufferSizeRequested=fileSize+min(1<<20,fileSize/6);//1<<20是1MB
    if(bufferSizeRequested>INT_MAX)
    {
        fclose(fp);
        msgboxErr(QString("文件太大，无法开启！\r\nsize:%1 MB").arg(fileSize/1024/1024));
        return false;
    }

    //设置edit指向新的数据源
    pEdit->SendScintilla(QsciScintilla::SCI_SETSTATUS, QsciScintilla::SC_STATUS_OK);
    pEdit->SendScintilla(QsciScintilla::SCI_SETDOCPOINTER,0,doc);
    bool ro=(pEdit->SendScintilla(QsciScintilla::SCI_GETREADONLY)!=0);
    if(ro) pEdit->SendScintilla(QsciScintilla::SCI_SETREADONLY,false);
    pEdit->SendScintilla(QsciScintilla::SCI_CLEARALL);//清空文本框

    //设置编辑器语言类别
    if(fileFormat.language<L_EXTERNAL)
    {
        //pEdit->SendScintilla(QsciScintilla::SCI_SETLEXER,Buffer::langNames[fileFormat.language].lexerID);
    }
    else{
        //自定义语言类别:暂不实现
        //pName是自定义语言的类别名称
        //pEdit->SendScintilla(QsciScintilla::SCI_SETLEXERLANGUAGE,0,reinterpret_cast<long>(pName));
    }
    if(!fileFormat.encoding.isEmpty()) pEdit->SendScintilla(QsciScintilla::SCI_SETCODEPAGE,QsciScintilla::SC_CP_UTF8);
    bool success=true;
    EolType format=EolType::unknown;
    size_t lenFile=0;
    int incompleteMultibyteChar = 0;
    bool isFirstTime=true;
    char data[blockSize+8];// +8 for incomplete multibyte char
    memset(data,0,sizeof(data));
    QString tmp;
    QT_TRY
    {
        pEdit->SendScintilla(QsciScintilla::SCI_ALLOCATE,static_cast<unsigned long>(bufferSizeRequested));
        if(pEdit->SendScintilla(QsciScintilla::SCI_GETSTATUS)!=QsciScintilla::SC_STATUS_OK) throw;
        do
        {
            lenFile=fread(data+incompleteMultibyteChar,1,blockSize-static_cast<size_t>(incompleteMultibyteChar),fp)+static_cast<size_t>(incompleteMultibyteChar);
            if(lenFile==0) break;
            if(isFirstTime)
            {
                if(determineEncoding(reinterpret_cast<unsigned char *>(data),static_cast<size_t>(lenFile))!=uni8Bit)
                {
                    //如果文件包含任何BOM，编码将被删除，文档将解析为UTF
                    fileFormat.encoding="";
                }
                else if(fileFormat.encoding.isEmpty())
                {
                    //探测字符串编码
                    if(detectEncoding) {
                        fileFormat.encoding=detectEncode(data,static_cast<size_t>(lenFile));
                    }
                }
                if(fileFormat.language==L_TEXT)
                {
                    //探测字符串属于哪种编程语言
                    fileFormat.language=detectLanguageFromTextBegining(reinterpret_cast<unsigned char *>(data),static_cast<size_t>(lenFile));
                }
                isFirstTime=false;
            }
            if(!fileFormat.encoding.isEmpty())
            {
                if(fileFormat.encoding.compare("utf-8",Qt::CaseInsensitive)==0)
                {
                    //是UTF-8编码直接追加到文本编辑器
                    pEdit->SendScintilla(QsciScintilla::SCI_APPENDTEXT,static_cast<unsigned long>(lenFile),reinterpret_cast<long>(data));
                }else{
                    //多字节转utf8
                    std::string newData=encode(fileFormat.encoding.toLatin1(),"utf-8",data,static_cast<int>(lenFile),&incompleteMultibyteChar);
                    pEdit->SendScintilla(QsciScintilla::SCI_APPENDTEXT,static_cast<unsigned long>(newData.size()),reinterpret_cast<long>(newData.c_str()));
                }
                if(format==EolType::unknown) format=getEOLFormatForm(data,static_cast<size_t>(lenFile),EolType::unknown);
            }else{
                //转成UTF-8
                auto newData=utf8_2_ws(data);
                pEdit->SendScintilla(QsciScintilla::SCI_APPENDTEXT,static_cast<unsigned long>(newData.size()),reinterpret_cast<long>(newData.c_str()));
            }
            if (pEdit->SendScintilla(QsciScintilla::SCI_GETSTATUS) != QsciScintilla::SC_STATUS_OK) throw;
            if (incompleteMultibyteChar != 0)
            {
                // copy bytes to next buffer
                memcpy(data, data + blockSize - incompleteMultibyteChar, static_cast<size_t>(incompleteMultibyteChar));
            }
        }while(lenFile>0);
    }
    QT_CATCH(...)
    {
        msgboxErr("读取文件失败！");
        success=false;
    }
    fclose(fp);
    if(format==EolType::unknown)
    {
        auto set=pParameter->getConfigPtr()->getNewDocDefaultSettings();
        fileFormat.eolFormat=set.format;
        if(fileSize==0)
        {
            if(set.unicodeMode==UniMode::uniCookie && set.openAnsiAsUtf8)
            {
                fileFormat.encoding="utf-8";
            }
        }
    }else{
        fileFormat.eolFormat=format;
    }
    pEdit->SendScintilla(QsciScintilla::SCI_EMPTYUNDOBUFFER);
    pEdit->SendScintilla(QsciScintilla::SCI_SETSAVEPOINT);
    if(ro) pEdit->SendScintilla(QsciScintilla::SCI_SETREADONLY,true);
    pEdit->SendScintilla(QsciScintilla::SCI_SETDOCPOINTER,0,_scratchDocDefault);
    return success;
}

void FileManager::fireBufferChanged(Buffer *pBuffer, const int mask)
{
    emit BufferChanged(pBuffer,mask);
}

UniMode FileManager::determineEncoding(const unsigned char *buf, size_t bufLen)
{
    // detect UTF-16 big-endian with BOM
    if (bufLen > 1 && buf[0] == k_Boms[uni16BE][0] && buf[1] == k_Boms[uni16BE][1])
    {
        return uni16BE;
    }
    // detect UTF-16 little-endian with BOM
    if (bufLen > 1 && buf[0] == k_Boms[uni16LE][0] && buf[1] == k_Boms[uni16LE][1])
    {
        return uni16LE;
    }
    // detect UTF-8 with BOM
    if (bufLen > 2 && buf[0] == k_Boms[uniUTF8][0] &&
            buf[1] == k_Boms[uniUTF8][1] && buf[2] == k_Boms[uniUTF8][2])
    {
        return uniUTF8;
    }
    return uni8Bit;
}

Buffer::Buffer(FileManager *_pManager, Document _doc, DocFileStatus _status, const QString &_fileName):
    pManager(_pManager),doc(_doc),currentStatus(_status)
{
    auto set=pParameter->getConfigPtr()->getNewDocDefaultSettings();
    eolFormat=set.format;
    unicodeMode=set.unicodeMode;
    encoding=set.codepage;

    setFileName(_fileName);
    updateModified();
    isDirty=false;
    canNotify=true;
    needLexer=false;//新缓存不需要词法，由Scintilla提供
}

void Buffer::setFileName(const QString &_fileName, LangType _defLang)
{
    if(fileName.compare(_fileName,Qt::CaseInsensitive)==0) {
        updateModified();
        return;
    }
    fileName=_fileName;
    LangType newLang=_defLang;
    QFileInfo fInfo(_fileName);
    auto ext=fInfo.suffix().toLower();
    if(!ext.isEmpty())
    {
        auto langs=pParameter->getLanguagePtr()->getLanguages();
        if(langs.find(ext)!=langs.end()) newLang=langs[ext]->langID;
    }
}

void Buffer::updateModified()
{
    QFileInfo fInfo(fileName);
    if(!fInfo.exists()) return;
    auto last=fInfo.lastModified();
    if(lastModified!=last)
    {
        lastModified=last;
        doNotify(BufferStatusInfo::BufferChangeTimestamp);
    }
}

void Buffer::doNotify(const int mask)
{
    if(!canNotify) return;
    assert(pManager!=nullptr);//如果pManager=nullptr则终止程序继续
    pManager->fireBufferChanged(this,mask);//通知档案已变更
}

