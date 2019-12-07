#include "languages.h"
#include "tools.h"
#include <QCoreApplication>
#include <QFile>
#include <QStandardPaths>

Languages *Languages::pLanObj=new Languages();

Languages::Languages():
    lanTypes({
{"English", "english.xml"},
{"English (customizable)", "english_customizable.xml"},
{"Français", "french.xml"},
{"中文繁體", "chinese.xml"},
{"中文简体", "chineseSimplified.xml"},
{"한국어", "korean.xml"},
{"日本語", "japanese.xml"},
{"Deutsch", "german.xml"},
{"Español", "spanish.xml"},
{"Italiano", "italian.xml"},
{"Português", "portuguese.xml"},
{"Português brasileiro", "brazilian_portuguese.xml"},
{"Nederlands", "dutch.xml"},
{"Русский", "russian.xml"},
{"Polski", "polish.xml"},
{"Català", "catalan.xml"},
{"Česky", "czech.xml"},
{"Magyar", "hungarian.xml"},
{"Română", "romanian.xml"},
{"Türkçe", "turkish.xml"},
{"فارسی", "farsi.xml"},
{"Українська", "ukrainian.xml"},
{"עברית", "hebrew.xml"},
{"Nynorsk", "nynorsk.xml"},
{"Norsk", "norwegian.xml"},
{"Occitan", "occitan.xml"},
{"ไทย", "thai.xml"},
{"Furlan", "friulian.xml"},
{"العربية", "arabic.xml"},
{"Suomi", "finnish.xml"},
{"Lietuvių", "lithuanian.xml"},
{"Ελληνικά", "greek.xml"},
{"Svenska", "swedish.xml"},
{"Galego", "galician.xml"},
{"Slovenščina", "slovenian.xml"},
{"Slovenčina", "slovak.xml"},
{"Dansk", "danish.xml"},
{"Estremeñu", "extremaduran.xml"},
{"Žemaitiu ruoda", "samogitian.xml"},
{"Български", "bulgarian.xml"},
{"Bahasa Indonesia", "indonesian.xml"},
{"Gjuha shqipe", "albanian.xml"},
{"Hrvatski jezik", "croatian.xml"},
{"ქართული ენა", "georgian.xml"},
{"Euskara", "basque.xml"},
{"Español argentina", "spanish_ar.xml"},
{"Беларуская мова", "belarusian.xml"},
{"Srpski", "serbian.xml"},
{"Cрпски", "serbianCyrillic.xml"},
{"Bahasa Melayu", "malay.xml"},
{"Lëtzebuergesch", "luxembourgish.xml"},
{"Tagalog", "tagalog.xml"},
{"Afrikaans", "afrikaans.xml"},
{"Қазақша", "kazakh.xml"},
{"O‘zbekcha", "uzbek.xml"},
{"Ўзбекча", "uzbekCyrillic.xml"},
{"Кыргыз тили", "kyrgyz.xml"},
{"Македонски јазик", "macedonian.xml"},
{"latviešu valoda", "latvian.xml"},
{"தமிழ்", "tamil.xml"},
{"Azərbaycan dili", "azerbaijani.xml"},
{"Bosanski", "bosnian.xml"},
{"Esperanto", "esperanto.xml"},
{"Zeneize", "ligurian.xml"},
{"हिन्दी", "hindi.xml"},
{"Sardu", "sardinian.xml"},
{"ئۇيغۇرچە", "uyghur.xml"},
{"తెలుగు", "telugu.xml"},
{"aragonés", "aragonese.xml"},
{"বাংলা", "bengali.xml"},
{"සිංහල", "sinhala.xml"},
{"Taqbaylit", "kabyle.xml"},
{"मराठी", "marathi.xml"},
{"tiếng Việt", "vietnamese.xml"},
{"Aranés", "aranese.xml"},
{"ગુજરાતી", "gujarati.xml"},
{"Монгол хэл", "mongolian.xml"},
{"اُردُو‎", "urdu.xml"},
{"ಕನ್ನಡ‎", "kannada.xml"},
{"Cymraeg", "welsh.xml"},
{"eesti keel", "estonian.xml"},
{"Тоҷик", "tajikCyrillic.xml"},
{"татарча", "tatar.xml"},
{"ਪੰਜਾਬੀ", "punjabi.xml"},
{"Corsu", "corsican.xml"},
{"Brezhoneg", "breton.xml"},
{"کوردی‬", "kurdish.xml"},
{"Pig latin", "piglatin.xml"},
{"Zulu", "zulu.xml"}
             })
{

}

void Languages::setLanguagePath(const QString &path)
{
    lanPath.clear();
    if(path.isEmpty())
    {
        lanPath.append(pathCombine({QCoreApplication::applicationDirPath(),"localization"}));
    }else{
        lanPath.append(path);
    }
}

bool Languages::load(const QString &lanType)
{
    if(lanType.isEmpty()) return false;
    auto it=lanTypes.find(lanType);
    if(it==lanTypes.end()) return false;
    return loadXml(pathCombine({lanPath,it.value()}));
}

bool Languages::getMainMenus(QMap<QString, QString> &menus)
{
    return getNodesSameAttr("/NotepadPlus/Native-Langue/Menu/Main/Entries/Item","menuId","name",menus,true,true);
}

bool Languages::getSubMenus(QMap<QString, QString> &menus)
{
    return getNodesSameAttr("/NotepadPlus/Native-Langue/Menu/Main/SubEntries/Item","subMenuId","name",menus,true,true);
}

bool Languages::getCommands(QMap<QString, QString> &commands)
{
    return getNodesSameAttr("/NotepadPlus/Native-Langue/Menu/Main/Commands/Item","id","name",commands,true,true);
}

bool Languages::getTabMenus(QMap<QString, QString> &menus)
{
    return getNodesSameAttr("/NotepadPlus/Native-Langue/Menu/Main/TabBar/Item","CMID","name",menus,true,true);
}

const QMap<QString, QString> Languages::getLanTypes() const
{
    return lanTypes;
}

Languages *Languages::getInstancePtr()
{
    return pLanObj;
}
