#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "uilanguage.h"
#include "configfile.h"
#include "languages.h"

#define MSG_LANGUAGE_CHANGE 1
#define MSG_TOOLBAR_CHANGE 2

//当类中有虚函数(纯虚函数)时，就必须定义析构函数，否则会报警告 'xxx' has virtual functions but non-virtual destructor
class Parameters final:public QObject
{
    //使用信号、槽，类必须继承QObject，并且必须在此使用宏Q_OBJECCT
    Q_OBJECT
private:
    bool _isInit=false;
    UILanguage *pLanObj=nullptr;
    QString lanType="";
    static Parameters *pInstance;

    Parameters();
    ~Parameters();//在此定义析构函数，去除编译警告
public:
    void init();
    void changeLanguage(const QString &_lanType="");
    const QString &getLanType();
    bool isInit() const;
    static Parameters *getInstancePtr();
    static ConfigFile *getConfigPtr();
    static Languages *getLanguagePtr();
signals:
    //语言变更
    void LanguageChanged();
};

#endif // PARAMETERS_H
