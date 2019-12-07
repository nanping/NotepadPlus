#include "parameters.h"
#include "tools.h"

Parameters *Parameters::pInstance=new Parameters();

Parameters::Parameters():pLanObj(nullptr),pCfObj(nullptr),lanType("")
{

}

Parameters::~Parameters()
{
    if(pLanObj)
    {
        delete pLanObj;
        pLanObj=nullptr;
    }
    if(pCfObj)
    {
        delete pCfObj;
        pCfObj=nullptr;
    }
}

void Parameters::init()
{
    pLanObj=Languages::getInstancePtr();
    pLanObj->setLanguagePath();
    pCfObj=new ConfigFile();
    QString v="sdfk";
    pCfObj->setNodeValue("/h1/h2/h3[@name='hu']",v);
    if(pCfObj->loadXml())
    {
        changeLanguage(pCfObj->getValue("/NotepadPlus/GUIConfigs/GUIConfig[@name=\"language\"]","中文简体"));
    }
    else{
        changeLanguage("中文简体");
    }
}

void Parameters::changeLanguage(const QString &_lanType)
{
    if(!pLanObj->loadXml(_lanType,lanValues)) return;
    //菜单加载完毕后，通知UI更新，以实现类之间解耦
    emit LanguageChanged(lanValues);
}

const QMap<QString, QString> &Parameters::getLanValues() noexcept
{
    return lanValues;
}

Parameters *Parameters::getInstancePtr()
{
    return pInstance;
}
