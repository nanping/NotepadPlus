#ifndef BUFFER_H
#define BUFFER_H

#include <QDateTime>
#include <stdio.h>
#include "parameters.h"
#include "languages.h"

typedef void* Document;

enum DocFileStatus
{
    DOC_REGULAR    = 0x01, // should not be combined with anything
    DOC_UNNAMED    = 0x02, // not saved (new ##)
    DOC_DELETED    = 0x04, // doesn't exist in environment anymore, but not DOC_UNNAMED
    DOC_MODIFIED   = 0x08, // File in environment has changed
    DOC_NEEDRELOAD = 0x10  // File is modified & needed to be reload (by log monitoring)
};

enum BufferStatusInfo
{
    BufferChangeLanguage	= 0x001,  // Language was altered
    BufferChangeDirty		= 0x002,  // Buffer has changed dirty state
    BufferChangeFormat		= 0x004,  // EOL type was changed
    BufferChangeUnicode		= 0x008,  // Unicode type was changed
    BufferChangeReadonly	= 0x010,  // Readonly state was changed, can be both file and user
    BufferChangeStatus		= 0x020,  // Filesystem Status has changed
    BufferChangeTimestamp	= 0x040,  // Timestamp was changed
    BufferChangeFilename	= 0x080,  // Filename was changed
    BufferChangeRecentTag	= 0x100,  // Recent tag has changed
    BufferChangeLexing		= 0x200,  // Document needs lexing
    BufferChangeMask		= 0x3FF   // Mask: covers all changes
};

struct Position
{
    int _firstVisibleLine = 0;
    int _startPos = 0;
    int _endPos = 0;
    int _xOffset = 0;
    int _selMode = 0;
    int _scrollWidth = 1;
};

class FileManager;

class Buffer
{
public:
    Buffer(FileManager *_pManager,Document _doc,DocFileStatus _status,const QString &_fileName);
    //保存文档位置，以便下次显示时恢复
    Position pos;
    void setFileName(const QString &_fileName,LangType _defLang=L_TEXT);
    void updateModified();
private:
    FileManager *pManager=nullptr;
    Document doc=nullptr;
    DocFileStatus currentStatus=DOC_UNNAMED;
    QString fileName="";
    EolType eolFormat=EolType::osdefault;
    UniMode unicodeMode;
    QString encoding="";
    QDateTime lastModified;
    bool canNotify=false;
    bool isDirty=true;
    bool needLexer=false;

    Buffer(const Buffer&)=delete;//删除默认的拷贝构造函数
    Buffer& operator=(const Buffer&)=delete;
    void doNotify(const int mask);
};

//C++11关键字final表示禁止该类继承
class FileManager final:QObject
{
    friend class Buffer;
    Q_OBJECT
public:
    //探查文件编码
    bool detectEncoding=true;
    void init(QsciScintilla *_pEdit);
    //检查语言类别
    static LangType detectLanguageFromTextBegining(const unsigned char *data,const size_t dataLen);
    //检查是否包含BOM
    static UniMode determineEncoding(const unsigned char *buf, size_t bufLen);
    Buffer *loadFile(const QString &fileName,Document doc=nullptr,const QString &encoding="");
private:
    struct FileFormat {
        LangType language=LangType::L_TEXT;
        QString encoding="";
        EolType eolFormat=EolType::unknown;
    };
    int uSaveNewFileCount=0;
    QVector<Buffer*> _buffers;
    QsciScintilla *pEdit=nullptr;
    Document _scratchDocDefault=nullptr;
    Buffer *newEmptyDocument();
    bool loadFileData(Document doc, const QString &filename, FileFormat& fileFormat);
    void fireBufferChanged(Buffer *pBuffer,const int mask);
signals:
    void BufferChanged(Buffer *pBuffer,const int mask);//档案发生改变事件
};



#endif // BUFFER_H
