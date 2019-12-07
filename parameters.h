#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "languages.h"
#include "configfile.h"

//当类中有虚函数(纯虚函数)时，就必须定义析构函数，否则会报警告 'xxx' has virtual functions but non-virtual destructor
class Parameters:public QObject
{
    //使用信号、槽，类必须继承QObject，并且必须在此使用宏Q_OBJECCT
    Q_OBJECT
private:
    Languages *pLanObj=nullptr;
    ConfigFile *pCfObj=nullptr;
    QString lanType="中文简体";
    static Parameters *pInstance;

    Parameters();
    ~Parameters();//在此定义析构函数，去除编译警告

public:
    void init();
    void changeLanguage();
    void changeLanguage(const QString &_lanType);
    bool getHistoryMenus(QVector<QString> &files);
    static Parameters *getInstancePtr();

//信号声明区
signals:
    //定义UI语言更新事件
    void LanguageChanged();
};

#endif // PARAMETERS_H
