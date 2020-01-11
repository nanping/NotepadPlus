#include "languages.h"
#include "parameters.h"
#include "tools.h"

Languages *Languages::pInstance=new Languages();

LanguageName Languages::langNames[L_EXTERNAL+1] = {
    {"normal",		"Normal text",		"Normal text file",								L_TEXT,			QsciScintilla::SCLEX_NULL},
    {"php",			"PHP",				"PHP Hypertext Preprocessor file",				L_PHP,			QsciScintilla::SCLEX_HTML},
    {"c",				"C",					"C source file",									L_C,			QsciScintilla::SCLEX_CPP},
    {"cpp",			"C++",				"C++ source file",								L_CPP,			QsciScintilla::SCLEX_CPP},
    {"cs",			"C#",					"C# source file",									L_CS,			QsciScintilla::SCLEX_CPP},
    {"objc",			"Objective-C",		"Objective-C source file",						L_OBJC,			QsciScintilla::SCLEX_CPP},
    {"java",			"Java",				"Java source file",								L_JAVA,			QsciScintilla::SCLEX_CPP},
    {"rc",			"RC",					"Windows Resource file",							L_RC,			QsciScintilla::SCLEX_CPP},
    {"html",			"HTML",				"Hyper Text Markup Language file",				L_HTML,			QsciScintilla::SCLEX_HTML},
    {"xml",			"XML",				"eXtensible Markup Language file",				L_XML,			QsciScintilla::SCLEX_XML},
    {"makefile",		"Makefile",			"Makefile",										L_MAKEFILE,		QsciScintilla::SCLEX_MAKEFILE},
    {"pascal",		"Pascal",				"Pascal source file",								L_PASCAL,		QsciScintilla::SCLEX_PASCAL},
    {"batch",			"Batch",				"Batch file",										L_BATCH,		QsciScintilla::SCLEX_BATCH},
    {"ini",			"ini",				"MS ini file",									L_INI,			QsciScintilla::SCLEX_PROPERTIES},
    {"nfo",			"NFO",				"MSDOS Style/ASCII Art",							L_ASCII,		QsciScintilla::SCLEX_NULL},
    {"udf",			"udf",				"User Defined language file",						L_USER,			QsciScintilla::SCLEX_USER},
    {"asp",			"ASP",				"Active Server Pages script file",				L_ASP,			QsciScintilla::SCLEX_HTML},
    {"sql",			"SQL",				"Structured Query Language file",					L_SQL,			QsciScintilla::SCLEX_SQL},
    {"vb",			"Visual Basic",		"Visual Basic file",								L_VB,			QsciScintilla::SCLEX_VB},
    {"javascript",	"JavaScript",			"JavaScript file",								L_JS,			QsciScintilla::SCLEX_CPP},
    {"css",			"CSS",				"Cascade Style Sheets File",						L_CSS,			QsciScintilla::SCLEX_CSS},
    {"perl",			"Perl",				"Perl source file",								L_PERL,			QsciScintilla::SCLEX_PERL},
    {"python",		"Python",				"Python file",									L_PYTHON,		QsciScintilla::SCLEX_PYTHON},
    {"lua",			"Lua",				"Lua source File",								L_LUA,			QsciScintilla::SCLEX_LUA},
    {"tex",			"TeX",				"TeX file",										L_TEX,			QsciScintilla::SCLEX_TEX},
    {"fortran",		"Fortran free form",	"Fortran free form source file",					L_FORTRAN,		QsciScintilla::SCLEX_FORTRAN},
    {"bash",			"Shell",				"Unix script file",								L_BASH,			QsciScintilla::SCLEX_BASH},
    {"actionscript",	"ActionScript",		"Flash ActionScript file",						L_FLASH,		QsciScintilla::SCLEX_CPP},
    {"nsis",			"NSIS",				"Nullsoft Scriptable Install System script file",	L_NSIS,			QsciScintilla::SCLEX_NSIS},
    {"tcl",			"TCL",				"Tool Command Language file",						L_TCL,			QsciScintilla::SCLEX_TCL},
    {"lisp",			"Lisp",				"List Processing language file",					L_LISP,			QsciScintilla::SCLEX_LISP},
    {"scheme",		"Scheme",				"Scheme file",									L_SCHEME,		QsciScintilla::SCLEX_LISP},
    {"asm",			"Assembly",			"Assembly language source file",					L_ASM,			QsciScintilla::SCLEX_ASM},
    {"diff",			"Diff",				"Diff file",										L_DIFF,			QsciScintilla::SCLEX_DIFF},
    {"props",			"Properties file",	"Properties file",								L_PROPS,		QsciScintilla::SCLEX_PROPERTIES},
    {"postscript",	"PostScript",			"PostScript file",								L_PS,			QsciScintilla::SCLEX_PS},
    {"ruby",			"Ruby",				"Ruby file",										L_RUBY,			QsciScintilla::SCLEX_RUBY},
    {"smalltalk",		"Smalltalk",			"Smalltalk file",									L_SMALLTALK,	QsciScintilla::SCLEX_SMALLTALK},
    {"vhdl",			"VHDL",				"VHSIC Hardware Description Language file",		L_VHDL,			QsciScintilla::SCLEX_VHDL},
    {"kix",			"KiXtart",			"KiXtart file",									L_KIX,			QsciScintilla::SCLEX_KIX},
    {"autoit",		"AutoIt",				"AutoIt",											L_AU3,			QsciScintilla::SCLEX_AU3},
    {"caml",			"CAML",				"Categorical Abstract Machine Language",			L_CAML,			QsciScintilla::SCLEX_CAML},
    {"ada",			"Ada",				"Ada file",										L_ADA,			QsciScintilla::SCLEX_ADA},
    {"verilog",		"Verilog",			"Verilog file",									L_VERILOG,		QsciScintilla::SCLEX_VERILOG},
    {"matlab",		"MATLAB",				"MATrix LABoratory",								L_MATLAB,		QsciScintilla::SCLEX_MATLAB},
    {"haskell",		"Haskell",			"Haskell",										L_HASKELL,		QsciScintilla::SCLEX_HASKELL},
    {"inno",			"Inno Setup",			"Inno Setup script",								L_INNO,			QsciScintilla::SCLEX_INNOSETUP},
    {"searchResult",	"Internal Search",	"Internal Search",								L_SEARCHRESULT,	QsciScintilla::SCLEX_SEARCHRESULT},
    {"cmake",			"CMake",				"CMake file",										L_CMAKE,		QsciScintilla::SCLEX_CMAKE},
    {"yaml",			"YAML",				"YAML Ain't Markup Language",						L_YAML,			QsciScintilla::SCLEX_YAML},
    {"cobol",			"COBOL",				"COmmon Business Oriented Language",				L_COBOL,		QsciScintilla::SCLEX_COBOL},
    {"gui4cli",		"Gui4Cli",			"Gui4Cli file",									L_GUI4CLI,		QsciScintilla::SCLEX_GUI4CLI},
    {"d",				"D",					"D programming language",							L_D,			QsciScintilla::SCLEX_D},
    {"powershell",	"PowerShell",			"Windows PowerShell",								L_POWERSHELL,	QsciScintilla::SCLEX_POWERSHELL},
    {"r",				"R",					"R programming language",							L_R,			QsciScintilla::SCLEX_R},
    {"jsp",			"JSP",				"JavaServer Pages script file",					L_JSP,			QsciScintilla::SCLEX_HTML},
    {"coffeescript",	"CoffeeScript",		"CoffeeScript file",								L_COFFEESCRIPT,	QsciScintilla::SCLEX_COFFEESCRIPT},
    {"json",			"json",				"JSON file",										L_JSON,			QsciScintilla::SCLEX_CPP },
    {"javascript.js", "JavaScript",			"JavaScript file",								L_JAVASCRIPT,	QsciScintilla::SCLEX_CPP },
    {"fortran77",		"Fortran fixed form",	"Fortran fixed form source file",					L_FORTRAN_77,	QsciScintilla::SCLEX_F77},
    {"baanc",			"BaanC",				"BaanC File",										L_BAANC,		QsciScintilla::SCLEX_BAAN },
    {"srec",			"S-Record",			"Motorola S-Record binary data",					L_SREC,			QsciScintilla::SCLEX_SREC},
    {"ihex",			"Intel HEX",			"Intel HEX binary data",							L_IHEX,			QsciScintilla::SCLEX_IHEX},
    {"tehex",			"Tektronix extended HEX",	"Tektronix extended HEX binary data",			L_TEHEX,		QsciScintilla::SCLEX_TEHEX},
    {"swift",			"Swift",              "Swift file",										L_SWIFT,		QsciScintilla::SCLEX_CPP},
    {"asn1",			"ASN.1",				"Abstract Syntax Notation One file",				L_ASN1,			QsciScintilla::SCLEX_ASN1},
    {"avs",			"AviSynth",			"AviSynth scripts files",							L_AVS,			QsciScintilla::SCLEX_AVS},
    {"blitzbasic",	"BlitzBasic",			"BlitzBasic file",								L_BLITZBASIC,	QsciScintilla::SCLEX_BLITZBASIC},
    {"purebasic",		"PureBasic",			"PureBasic file",									L_PUREBASIC,	QsciScintilla::SCLEX_PUREBASIC},
    {"freebasic",		"FreeBasic",			"FreeBasic file",									L_FREEBASIC,	QsciScintilla::SCLEX_FREEBASIC},
    {"csound",		"Csound",				"Csound file",									L_CSOUND,		QsciScintilla::SCLEX_CSOUND},
    {"erlang",		"Erlang",				"Erlang file",									L_ERLANG,		QsciScintilla::SCLEX_ERLANG},
    {"escript",		"ESCRIPT",			"ESCRIPT file",									L_ESCRIPT,		QsciScintilla::SCLEX_ESCRIPT},
    {"forth",			"Forth",				"Forth file",										L_FORTH,		QsciScintilla::SCLEX_FORTH},
    {"latex",			"LaTeX",				"LaTeX file",										L_LATEX,		QsciScintilla::SCLEX_LATEX},
    {"mmixal",		"MMIXAL",				"MMIXAL file",									L_MMIXAL,		QsciScintilla::SCLEX_MMIXAL},
    {"nimrod",		"Nimrod",				"Nimrod file",									L_NIMROD,		QsciScintilla::SCLEX_NIMROD},
    {"nncrontab",		"Nncrontab",			"extended crontab file",							L_NNCRONTAB,	QsciScintilla::SCLEX_NNCRONTAB},
    {"oscript",		"OScript",			"OScript source file",							L_OSCRIPT,		QsciScintilla::SCLEX_OSCRIPT},
    {"rebol",			"REBOL",				"REBOL file",										L_REBOL,		QsciScintilla::SCLEX_REBOL},
    {"registry",		"registry",			"registry file",									L_REGISTRY,		QsciScintilla::SCLEX_REGISTRY},
    {"rust",			"Rust",				"Rust file",										L_RUST,			QsciScintilla::SCLEX_RUST},
    {"spice",			"Spice",				"spice file",										L_SPICE,		QsciScintilla::SCLEX_SPICE},
    {"txt2tags",		"txt2tags",			"txt2tags file",									L_TXT2TAGS,		QsciScintilla::SCLEX_TXT2TAGS},
    {"visualprolog",	"Visual Prolog",		"Visual Prolog file",								L_VISUALPROLOG,	QsciScintilla::SCLEX_VISUALPROLOG},
    {"ext",			"External",			"External",										L_EXTERNAL,		QsciScintilla::SCLEX_NULL}
};

Languages::Languages()
{

}

Languages::~Languages()
{

}

void Languages::ClearLangs()
{
    if(langList.count()>0)
    {
        for(auto it=langList.begin();it!=langList.end();it++)
        {
            auto v=it.value();
            v->langKeyWordList.clear();
            delete v;
        }
        langList.clear();
    }
}

void Languages::ClearUserLangs()
{
    if(userLangs.count()>0)
    {
        for(auto it=userLangs.begin();it!=userLangs.end();it++)
        {
            auto v=it.value();
            delete v;
        }
        userLangs.clear();
    }
}

bool Languages::loadLanguages()
{
    this->ClearLangs();
    auto list=this->queryNodes("/NotepadPlus/Languages/Language");
    PLang pLan;
    for(auto it=list.begin();it!=list.end();it++)
    {
        auto n=it->node();
        auto attr=n.attribute("name");
        if(!attr) continue;
        pLan=new Lang();
        pLan->langName=attr.value();
        attr=n.attribute("ext");
        if(attr) pLan->defaultExtList=attr.value();
        attr=n.attribute("commentLine");
        if(attr) pLan->commentLineSymbol=attr.value();
        attr=n.attribute("commentStart");
        if(attr) pLan->commentStart=attr.value();
        attr=n.attribute("commentEnd");
        if(attr) pLan->commentEnd=attr.value();
        auto childs=n.select_nodes("Keywords");
        for(auto child=childs.begin();child!=childs.end();child++)
        {
            attr=child->node().attribute("name");
            if(!attr) continue;
            pLan->langKeyWordList.insert(attr.value(),child->node().text().get());
        }
        langList.insert(pLan->langName.toLower(),pLan);
    }
    return langList.count()>0;
}

bool Languages::loadUserLangs(const QString &userLangPath)
{
    if(!pathExists(userLangPath)) return false;
    QDir dir(userLangPath);
    auto xmls=dir.entryInfoList({"*.xml"},QDir::Files);
    if(xmls.size()<1) return false;
    ClearUserLangs();
    for(int i=0,size=xmls.size();i<size;i++)
    {
        QString key=xmls.at(i).baseName();
        PUserLang plan=new UserLang();
        if(!plan->loadXml(pathCombine({xmls.at(i).path(),xmls.at(i).fileName()})))
        {
            delete plan;
            continue;
        }
        userLangs.insert(key,plan);
    }
    return userLangs.count()>0;
}

bool UserLang::loadXml(const QString &file)
{
    if(!XmlFile::loadXml(file)) return false;
    auto node=this->querySingleNode("/NotepadPlus/UserLang");
    if(!node) return false;
    auto n=node.node();
    auto attr=n.attribute("name");
    if(!attr) return false;
    name=attr.value();
    attr=n.attribute("ext");
    if(!attr) return false;
    ext=attr ? attr.value():"";
    attr=n.attribute("udlVersion");
    udlVersion=attr ? attr.value():"";
    return true;
}

bool UserLang::getKeywordLists(QMap<QString, QString> &values)
{
    values.clear();
    auto list=this->queryNodes("/NotepadPlus/UserLang/KeywordLists/Keywords");
    for(auto it=list.begin();it!=list.end();it++)
    {
        auto n=it->node();
        auto attr=n.attribute("name");
        if(!attr) continue;
        values.insert(attr.value(),n.text().get());
    }
    return values.count()>0;
}

bool UserLang::getKeywords(const QString &name, QString &value)
{
    auto n=this->querySingleNode(QString("/NotepadPlus/UserLang/KeywordLists/Keywords[@name='%1']").arg(name));
    if(!n) return false;
    value=n.node().text().get();
    return true;
}

bool UserLang::getStyles(QMap<QString, QMap<QString, QString>> &values)
{
    values.clear();
    auto list=this->queryNodes("/NotepadPlus/UserLang/Styles/WordsStyle");
    for(auto it=list.begin();it!=list.end();it++)
    {
        auto n=it->node();
        auto attr=n.attribute("name");
        if(!attr) continue;
        QString key=attr.value();
        QMap<QString, QString> lst;
        for(auto a=n.attributes_end();a!=n.attributes_end();a++)
        {
            QString k=a->name();
            if(k.compare("name",Qt::CaseInsensitive)==0) continue;
            lst.insert(k,a->value());
        }
        values.insert(key,lst);
    }
    return values.count()>0;
}

bool UserLang::getSettings(QMap<QString, QMap<QString, QString> > &values)
{
    values.clear();
    auto list=this->queryNodes("/NotepadPlus/UserLang/Settings");
    for(auto it=list.begin();it!=list.end();it++)
    {
        auto n=it->node();
        QString key=n.name();
        QMap<QString, QString> lst;
        for(auto a=n.attributes_end();a!=n.attributes_end();a++)
        {
            lst.insert(a->name(),a->value());
        }
        values.insert(key,lst);
    }
    return values.count()>0;
}
