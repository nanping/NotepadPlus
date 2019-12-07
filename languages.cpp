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

void Languages::Clear()
{
    lanVer.clear();
    lanName.clear();
}

void Languages::readLanValues(QXmlStreamReader &reader, QMap<QString, QString> &lanValues)
{
    int isStart=-1;
    QString key("");
    QString name("");
    QString value("");
    QString nodeName("");
    int pos,cnt=0;
    while((reader.readNext()!=QXmlStreamReader::TokenType::Invalid) && !reader.atEnd())
    {
        nodeName= reader.name().toString();
        if(!reader.isStartElement()) {
            if(isStart==1 && key.endsWith("/"+nodeName,Qt::CaseInsensitive))
            {
                pos=key.lastIndexOf('/');
                if(pos>=0)
                {
                    key.remove(pos,key.length()-pos);
                }else{
                    key.clear();
                }
            }
            continue;
        }
        if(isStart==1)
        {
            auto attributes=reader.attributes();
            if(QString::compare("Item",nodeName,Qt::CaseInsensitive)==0)
            {
                name.clear();
                if(attributes.hasAttribute("menuId")) name=attributes.value("menuId").toString();
                if(attributes.hasAttribute("idName")) name=attributes.value("idName").toString();
                if(attributes.hasAttribute("subMenuId")) name=attributes.value("subMenuId").toString();
                if(attributes.hasAttribute("CMID")) name=attributes.value("CMID").toString();
                if(attributes.hasAttribute("id")) name=attributes.value("id").toString();
                if(name.isEmpty()) {
                    continue;
                }
                name=name.replace("-","_");
                value=attributes.hasAttribute("name") ? attributes.value("name").toString():"";
                name=(key+"/"+name).toUpper();
                if(lanValues.find(name)!=lanValues.end())
                {
                    lanValues[name]=value;
                }else{
                    lanValues.insert(name,value);
                }
            }
            else if(QString::compare("Element",nodeName,Qt::CaseInsensitive)==0 && key.endsWith("/ComboBox",Qt::CaseInsensitive))
            {
                if(attributes.hasAttribute("name"))
                {
                    value=attributes.value("name").toString();
                    name=QString("%1/%2/%3").arg(key).arg(nodeName).arg(cnt).toUpper();
                    if(lanValues.find(name)!=lanValues.end())
                    {
                        lanValues[name]=value;
                    }else{
                        lanValues.insert(name,value);
                    }
                    cnt++;
                }
                else{
                    continue;
                }
            }
            else{
                for(auto it=attributes.begin();it!=attributes.end();it++)
                {
                    name=(key+"/"+nodeName+"/"+it->name()).toUpper();
                    value=it->value().toString();
                    if(lanValues.find(name)!=lanValues.end())
                    {
                        lanValues[name]=value;
                    }else{
                        lanValues.insert(name,value);
                    }
                }
                if(!reader.isEndElement()) key.append("/"+nodeName);
            }
            continue;
        }
        if(QString::compare("NotepadPlus",nodeName,Qt::CaseInsensitive)==0) {
            isStart=0;
            continue;
        }
        if(isStart==0 && QString::compare("Native-Langue",nodeName,Qt::CaseInsensitive)==0)
        {
            auto attributes=reader.attributes();
            if(attributes.hasAttribute("name")) lanName=attributes.value("name").toString();
            if(attributes.hasAttribute("version")) lanVer=attributes.value("version").toString();
            isStart=1;
            continue;
        }
    }
}

void Languages::readLanValues(QXmlStreamReader &reader, QMap<QString, QString> &lanValues,const QString &findKey)
{
    int isStart=-1;
    QString key("");
    QString name("");
    QString value("");
    QString nodeName("");
    int pos,cnt=0;
    while((reader.readNext()!=QXmlStreamReader::TokenType::Invalid) && !reader.atEnd())
    {
        nodeName= reader.name().toString();
        if(!reader.isStartElement()) {
            if(isStart==1 && key.endsWith("/"+nodeName,Qt::CaseInsensitive))
            {
                pos=key.lastIndexOf('/');
                if(pos>=0)
                {
                    key.remove(pos,key.length()-pos);
                }else{
                    key.clear();
                }
            }
            continue;
        }
        if(isStart==1)
        {
            if(!findKey.isEmpty()) {
                if(!(key+"/"+nodeName+"/").startsWith(findKey,Qt::CaseInsensitive))
                {
                    if(lanValues.count()>0)
                        break;
                    else
                    {
                        if(QString::compare("Item",nodeName,Qt::CaseInsensitive)==0 ||
                                (QString::compare("Element",nodeName,Qt::CaseInsensitive)==0 && key.endsWith("/ComboBox",Qt::CaseInsensitive)))
                        {

                        }else{
                            if(!reader.isEndElement()) key.append("/"+nodeName);
                        }
                        continue;
                    }
                }
            }
            auto attributes=reader.attributes();
            if(QString::compare("Item",nodeName,Qt::CaseInsensitive)==0)
            {
                name.clear();
                if(attributes.hasAttribute("menuId")) name=attributes.value("menuId").toString();
                if(attributes.hasAttribute("idName")) name=attributes.value("idName").toString();
                if(attributes.hasAttribute("subMenuId")) name=attributes.value("subMenuId").toString();
                if(attributes.hasAttribute("CMID")) name=attributes.value("CMID").toString();
                if(attributes.hasAttribute("id")) name=attributes.value("id").toString();
                if(name.isEmpty()) {
                    continue;
                }
                value=attributes.hasAttribute("name") ? attributes.value("name").toString():"";
                name=(key+"/"+name).toUpper();
                if(lanValues.find(name)!=lanValues.end())
                {
                    lanValues[name]=value;
                }else{
                    lanValues.insert(name,value);
                }
            }
            else if(QString::compare("Element",nodeName,Qt::CaseInsensitive)==0 && key.endsWith("/ComboBox",Qt::CaseInsensitive))
            {
                if(attributes.hasAttribute("name"))
                {
                    value=attributes.value("name").toString();
                    name=QString("%1/%2/%3").arg(key).arg(nodeName).arg(cnt).toUpper();
                    if(lanValues.find(name)!=lanValues.end())
                    {
                        lanValues[name]=value;
                    }else{
                        lanValues.insert(name,value);
                    }
                    cnt++;
                }
                else{
                    continue;
                }
            }
            else{
                for(auto it=attributes.begin();it!=attributes.end();it++)
                {
                    name=(key+"/"+nodeName+"/"+it->name()).toUpper();
                    value=it->value().toString();
                    if(lanValues.find(name)!=lanValues.end())
                    {
                        lanValues[name]=value;
                    }else{
                        lanValues.insert(name,value);
                    }
                }
                if(!reader.isEndElement()) key.append("/"+nodeName);
            }
            continue;
        }
        if(QString::compare("NotepadPlus",nodeName,Qt::CaseInsensitive)==0) {
            isStart=0;
            continue;
        }
        if(isStart==0 && QString::compare("Native-Langue",nodeName,Qt::CaseInsensitive)==0)
        {
            auto attributes=reader.attributes();
            if(attributes.hasAttribute("name")) lanName=attributes.value("name").toString();
            if(attributes.hasAttribute("version")) lanVer=attributes.value("version").toString();
            isStart=1;
            continue;
        }
    }
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

bool Languages::loadXml(const QString &lanType,QMap<QString,QString> &lanValues,const QString &findKeys)
{
    if(lanType.isEmpty()) return  false;
    auto it=lanTypes.find(lanType);
    if(it==lanTypes.end()) return false;
    QString file=pathCombine({lanPath,it.value()});
    if(!fileExists(file)) return false;
    lanValues.clear();
    this->Clear();
    QFile *pXmlFile=nullptr;
    QXmlStreamReader reader;
    try {
        pXmlFile=new QFile(file);
        reader.setDevice(pXmlFile);
        if(!pXmlFile->open(QIODevice::ReadOnly|QIODevice::Text)) return false;
        if(findKeys.isEmpty())
            readLanValues(reader,lanValues);
        else
            readLanValues(reader,lanValues,findKeys);
        pXmlFile->close();
        return true;
    } catch (...)
    {
        if(pXmlFile) pXmlFile->close();
        return false;
    }
}

const QMap<QString, QString> Languages::getLanTypes() const
{
    return lanTypes;
}

Languages *Languages::getInstancePtr()
{
    return pLanObj;
}
