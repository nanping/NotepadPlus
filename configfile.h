#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include "xmlfile.h"
#include "languages.h"
#include "def_parameters.h"

enum ConfigType
{
    eFindHistory,
    eHistory,
    eGUIConfigs,
    eProjectPanels
};

enum class EolType: std::uint8_t
{
    windows,
    macos,
    unix,

    // special values
    unknown, // can not be the first value for legacy code
    osdefault = windows,
};

enum UniMode {uni8Bit=0, uniUTF8=1, uni16BE=2, uni16LE=3, uniCookie=4, uni7Bit=5, uni16BE_NoBOM=6, uni16LE_NoBOM=7, uniEnd};

struct NewDocDefaultSettings final
{
    EolType format = EolType::osdefault;
    UniMode unicodeMode = uniCookie;
    bool openAnsiAsUtf8 = true;
    LangType lang = L_TEXT;
    QString codepage = ""; // -1 when not using

    void set(const QString &_format,const QString &_unicodeMode,
             const QString &_openAnsiAsUtf8,const QString &_lang,
             const QString &_codepage)
    {
        format=NewDocDefaultSettings::eolTypeFromStr(_format);
        unicodeMode=NewDocDefaultSettings::uniModeFromStr(_unicodeMode);
        openAnsiAsUtf8=_openAnsiAsUtf8.compare("yes",Qt::CaseInsensitive)==0;
        lang=NewDocDefaultSettings::langFromStr(_lang);
        codepage=NewDocDefaultSettings::codepageFromStr(_codepage);
    }

    QString toString()
    {
        return  QString(" format=\"%1\" encoding=\"%2\" lang=\"%3\" codepage=\"%4\" openAnsiAsUTF8=\"%5\" ")
                .arg(static_cast<int>(format)).arg(static_cast<int>(unicodeMode))
                .arg(openAnsiAsUtf8 ? "yes":"no").arg(static_cast<int>(lang)).arg(codepage);
    }

    static QString codepageFromStr(const QString &value)
    {
        return QString(value);
    }

    static EolType eolTypeFromStr(const QString &format)
    {
        bool ok;
        int v;
        v=format.toInt(&ok,10);
        if(!ok) return EolType::osdefault;
        switch(v)
        {
        case static_cast<int>(EolType::windows):
            return EolType::windows;
        case static_cast<int>(EolType::macos):
            return EolType::macos;
        case static_cast<int>(EolType::unix):
            return EolType::unix;
        default:
            return EolType::osdefault;
        }
    }

    static UniMode uniModeFromStr(const QString &value)
    {
        int v;
        bool ok;
        v=value.toInt(&ok,10);
        if(!ok) return UniMode::uniEnd;
        return static_cast<UniMode>(v);
    }

    static LangType langFromStr(const QString &value)
    {
        int v;
        bool ok;
        v=value.toInt(&ok,10);
        if(!ok) return LangType::L_TEXT;
        return static_cast<LangType>(v);
    }
};

class Parameters;

//当类中有虚函数(纯虚函数)时，就必须定义析构函数，否则会报警告 'xxx' has virtual functions but non-virtual destructor
class ConfigFile final:public XmlFile
{
    friend class Parameters;
private:
    QString lanType="";
    NewDocDefaultSettings newDocDefaultSettings;
    static ConfigFile *pInstance;
public:
    const QString createParameterStr(const int type,const QString &tagName="",const QString &idName="",const QString &idValue="");
    bool getHistoryFiles(QVector<QString> &files);
    const NewDocDefaultSettings &getNewDocDefaultSettings(bool reload=false);
    const QString getLanType();
    //使用宏自动构建方法代码
    CREATE_VALUE(ConfigType::eGUIConfigs,GUIConfig,name,language)
    CREATE_ATTRIBUTES_EACH(ConfigType::eGUIConfigs,GUIConfig,name,ToolBar,visible)
    CREATE_VALUE(ConfigType::eGUIConfigs,GUIConfig,name,StatusBar)
    CREATE_VALUE(ConfigType::eGUIConfigs,GUIConfig,name,MenuBar)
    CREATE_ATTRIBUTES_EACH(ConfigType::eGUIConfigs,GUIConfig,name,NewDocDefaultSettings,format,encoding,lang,codepage,openAnsiAsUTF8)
    CREATE_ATTRIBUTES_EACH(ConfigType::eGUIConfigs,GUIConfig,name,TabBar,dragAndDrop,drawTopBar,drawInactiveTab,reduce,closeButton,doubleClick2Close,vertical,multiLine,hide,quitOnEmpty)

};

#endif // CONFIGFILE_H
