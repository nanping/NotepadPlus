#include "configfile.h"
#include "tools.h"
#include "parameters.h"

ConfigFile *ConfigFile::pInstance=new ConfigFile();

const QString ConfigFile::createParameterStr(const int type, const QString &tagName, const QString &idName, const QString &idValue)
{
    switch(type)
    {
    case ConfigType::eGUIConfigs:
        return tagName.isEmpty() ? "/NotepadPlus/GUIConfigs": QString("/NotepadPlus/GUIConfigs/%1[@%2='%3']").arg(tagName).arg(idName).arg(idValue);
    case ConfigType::eHistory:
        return tagName.isEmpty() ? "/NotepadPlus/History": QString("/NotepadPlus/History/%1[@%2='%3']").arg(tagName).arg(idName).arg(idValue);
    case ConfigType::eFindHistory:
        return tagName.isEmpty() ? "/NotepadPlus/FindHistory": QString("/NotepadPlus/FindHistory/%1[@%2='%3']").arg(tagName).arg(idName).arg(idValue);
    case ConfigType::eProjectPanels:
        return tagName.isEmpty() ? "/NotepadPlus/ProjectPanels": QString("/NotepadPlus/ProjectPanels/%1[@%2='%3']").arg(tagName).arg(idName).arg(idValue);
    }
    return "";
}

bool ConfigFile::getHistoryFiles(QVector<QString> &files)
{
    if(!this->isOpen()) return false;
    QString v=this->getAttribute(createParameterStr(eHistory),"nbMaxFile","");
    int maxFiles;
    if(v.isEmpty())
    {
        maxFiles=10;
    }else{
        bool ok;
        maxFiles=v.toInt(&ok);
        if(!ok || maxFiles<1) {
            maxFiles=10;
        }else{
            if(maxFiles>30) maxFiles=10;
        }
    }
    if(!this->getNodesSameAttr(createParameterStr(eHistory,"File"),"filename",files)) return false;
    while(files.count()>maxFiles)
    {
        files.removeAt(maxFiles);
    }
    return files.count()>0;
}

const NewDocDefaultSettings &ConfigFile::getNewDocDefaultSettings(bool reload)
{
    if(reload)
    {
        newDocDefaultSettings.set(getNewDocDefaultSettings_format("0"),
                                  getNewDocDefaultSettings_encoding("4"),
                                  getNewDocDefaultSettings_openAnsiAsUTF8("yes"),
                                  getNewDocDefaultSettings_lang("0"),
                                  getNewDocDefaultSettings_codepage("-1"));
    }
    return newDocDefaultSettings;
}

const QString ConfigFile::getLanType()
{
    return this->getlanguageValue("中文简体");
}
