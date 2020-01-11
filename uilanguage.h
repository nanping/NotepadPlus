#ifndef UILANGUAGE_H
#define UILANGUAGE_H

#include <QString>
#include <QMap>
#include "xmlfile.h"

class UILanguage:public XmlFile
{
private:
    QString lanPath="";
    QMap<QString,QString> lanTypes;
    static UILanguage *pLanObj;

    UILanguage();
public:
    ~UILanguage();
    void setLanguagePath(const QString &path="");
    bool load(const QString &lanType);
    bool getMainMenus(QMap<QString,QString> &menus);
    bool getSubMenus(QMap<QString,QString> &menus);
    bool getCommands(QMap<QString,QString> &commands);
    bool getTabMenus(QMap<QString,QString> &menus);
    QString getDialogAttr(const QString &objName,const QString &attName,const QString &defValue="");
    const QMap<QString,QString> getLanTypes() const;
    static UILanguage *getInstancePtr();
};

#endif // UILANGUAGE_H
