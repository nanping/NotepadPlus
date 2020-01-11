#include "parameters.h"
#include "tools.h"
#include <QCoreApplication>

Parameters *Parameters::pInstance=new Parameters();

Parameters::Parameters()
{

}

Parameters::~Parameters()
{
    if(pLanObj)
    {
        delete pLanObj;
        pLanObj=nullptr;
    }
}

void Parameters::init()
{
    if(_isInit) return;
    pLanObj=UILanguage::getInstancePtr();
    pLanObj->setLanguagePath();
    auto pConfig=ConfigFile::pInstance;
    if((_isInit=pConfig->loadXml(pathCombine({QCoreApplication::applicationDirPath(),"config.xml"}))))
    {
        lanType=pConfig->getLanType();
        changeLanguage();
    }
    _isInit=Languages::pInstance->loadXml(pathCombine({QCoreApplication::applicationDirPath(),"langs.xml"}));
    if(_isInit)
    {
        _isInit=Languages::pInstance->loadLanguages();
    }
    _isInit=Languages::pInstance->loadUserLangs(pathCombine({QCoreApplication::applicationDirPath(),"userDefineLangs"}));
}

void Parameters::changeLanguage(const QString &_lanType)
{
    if(_lanType.isEmpty())
    {
        if(lanType.isEmpty()) return;
        if(!pLanObj->load(lanType)) return;
    }
    else{
        if(!pLanObj->load(_lanType)) return;
        lanType=_lanType;
    }
    //菜单加载完毕后，通知UI更新，以实现类之间解耦
    emit LanguageChanged();
}

const QString &Parameters::getLanType()
{
    return lanType;
}

Parameters *Parameters::getInstancePtr()
{
    return pInstance;
}

ConfigFile *Parameters::getConfigPtr()
{
    return ConfigFile::pInstance;
}

Languages *Parameters::getLanguagePtr()
{
    return Languages::pInstance;
}

bool Parameters::isInit() const
{
    return _isInit;
}

