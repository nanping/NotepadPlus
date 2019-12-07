#include "parameters.h"
#include "tools.h"

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
    if(pCfObj->loadXml())
    {
        lanType=pCfObj->getValue("/NotepadPlus/GUIConfigs/GUIConfig[@name=\"language\"]","中文简体");
    }
}

void Parameters::changeLanguage()
{
    changeLanguage(lanType);
}

void Parameters::changeLanguage(const QString &_lanType)
{
    if(!pLanObj->load(_lanType)) return;
    //菜单加载完毕后，通知UI更新，以实现类之间解耦
    emit LanguageChanged();
}

bool Parameters::getHistoryMenus(QVector<QString> &files)
{
    QString v=pCfObj->getAttribute("/NotepadPlus/History","nbMaxFile","");
    if(v.isEmpty()) return false;
    int maxFiles=v.toInt();
    if(!pCfObj->getNodesSameAttr("/NotepadPlus/History/File","filename",files)) return false;
    if(maxFiles>0)
    {
        while(files.count()>maxFiles)
        {
            files.removeAt(maxFiles);
        }
    }
    return files.count()>0;
}

Parameters *Parameters::getInstancePtr()
{
    return pInstance;
}
