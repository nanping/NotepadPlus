#ifndef LANGUAGES_H
#define LANGUAGES_H

#include <QString>
#include <QMap>
#include "configfile.h"

class Languages:public ConfigFile
{
private:
    QString lanPath="";
    QMap<QString,QString> lanTypes;
    static Languages *pLanObj;

    Languages();
public:
    void setLanguagePath(const QString &path="");
    bool load(const QString &lanType);
    bool getMainMenus(QMap<QString,QString> &menus);
    bool getSubMenus(QMap<QString,QString> &menus);
    bool getCommands(QMap<QString,QString> &commands);
    bool getTabMenus(QMap<QString,QString> &menus);
    const QMap<QString,QString> getLanTypes() const;
    static Languages *getInstancePtr();
};

#endif // LANGUAGES_H
