#ifndef LANGUAGES_H
#define LANGUAGES_H

#include <QString>
#include <QMap>
#include <QXmlStreamReader>

class Languages
{
private:
    QString lanPath="";
    QString lanName="";
    QString lanVer="";
    QMap<QString,QString> lanTypes;
    static Languages *pLanObj;

    Languages();
    void Clear();
    void readLanValues(QXmlStreamReader &reader,QMap<QString,QString> &lanValues);
    void readLanValues(QXmlStreamReader &reader,QMap<QString,QString> &lanValues,const QString &findKey);
public:
    void setLanguagePath(const QString &path="");
    bool loadXml(const QString &lanType,QMap<QString,QString> &lanValues,const QString &findKey="");
    const QMap<QString,QString> getLanTypes() const;
    static Languages *getInstancePtr();
};

#endif // LANGUAGES_H
