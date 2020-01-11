#ifndef LANGUAGES_H
#define LANGUAGES_H

#include "xmlfile.h"
#include <Qsci/qsciscintilla.h>

//小于NB_LANG的值是程序保留值范围，否则用于用户自定义
const int NB_LANG=100;

const int NB_LIST = 20;

enum LangType {L_TEXT, L_PHP , L_C, L_CPP, L_CS, L_OBJC, L_JAVA, L_RC,\
               L_HTML, L_XML, L_MAKEFILE, L_PASCAL, L_BATCH, L_INI, L_ASCII, L_USER,\
               L_ASP, L_SQL, L_VB, L_JS, L_CSS, L_PERL, L_PYTHON, L_LUA, \
               L_TEX, L_FORTRAN, L_BASH, L_FLASH, L_NSIS, L_TCL, L_LISP, L_SCHEME,\
               L_ASM, L_DIFF, L_PROPS, L_PS, L_RUBY, L_SMALLTALK, L_VHDL, L_KIX, L_AU3,\
               L_CAML, L_ADA, L_VERILOG, L_MATLAB, L_HASKELL, L_INNO, L_SEARCHRESULT,\
               L_CMAKE, L_YAML, L_COBOL, L_GUI4CLI, L_D, L_POWERSHELL, L_R, L_JSP,\
               L_COFFEESCRIPT, L_JSON, L_JAVASCRIPT, L_FORTRAN_77, L_BAANC, L_SREC,\
               L_IHEX, L_TEHEX, L_SWIFT,\
               L_ASN1, L_AVS, L_BLITZBASIC, L_PUREBASIC, L_FREEBASIC, \
               L_CSOUND, L_ERLANG, L_ESCRIPT, L_FORTH, L_LATEX, \
               L_MMIXAL, L_NIMROD, L_NNCRONTAB, L_OSCRIPT, L_REBOL, \
               L_REGISTRY, L_RUST, L_SPICE, L_TXT2TAGS, L_VISUALPROLOG,\
               // Don't use L_JS, use L_JAVASCRIPT instead
               // The end of enumated language type, so it should be always at the end
               L_EXTERNAL};

struct LanguageName {
    const char * lexerName;
    const char * shortName;
    const char * longName;
    LangType LangID;
    int lexerID;
};

struct Lang final
{
    LangType langID=L_TEX;
    QString langName="";
    QString defaultExtList="";
    QMap<QString,QString> langKeyWordList;
    QString commentLineSymbol="";
    QString commentStart="";
    QString commentEnd ="";
};
typedef Lang *PLang;

class UserLang final:XmlFile
{
public:
    QString name;
    QString ext;
    QString udlVersion;

    bool loadXml(const QString &file) override;
    bool getKeywordLists(QMap<QString,QString> &values);
    bool getKeywords(const QString &name,QString &value);
    bool getStyles(QMap<QString,QMap<QString,QString>> &values);
    bool getSettings(QMap<QString,QMap<QString,QString>> &values);
};
typedef UserLang *PUserLang;

class Parameters;

class Languages final:XmlFile
{
    friend class Parameters;
private:
    Languages();
    ~Languages();

    static Languages *pInstance;
    static LanguageName langNames[L_EXTERNAL+1];
    QMap<QString,PLang> langList;
    QMap<QString,PUserLang> userLangs;
    void ClearLangs();
    void ClearUserLangs();
public:
    bool loadLanguages();
    bool loadUserLangs(const QString &userLangPath);
    const QMap<QString,PLang> &getLanguages() const
    {
        return langList;
    }
    const QMap<QString,PUserLang> &getUserLangs() const
    {
        return userLangs;
    }
};

#endif // LANGUAGES_H
