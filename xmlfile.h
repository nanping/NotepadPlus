#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QMap>
#include <QVector>
#include <QObject>
#include "pugixml/pugixml.hpp"

using namespace pugi;

class XmlFile:public QObject
{
    Q_OBJECT
public:
    XmlFile();
    ~XmlFile();

protected:
    QString fileName="";
    QString errMsg="";
    xml_document *pDoc=nullptr;
    xml_node appendNodes(const QString &xpath);
    void readName(QString &name,QMap<QString,QString> &attrs);
    xpath_node querySingleNode(const QString &xpath);
    xpath_node_set queryNodes(const QString &xpath);
public:
    void close();
    bool isOpen();
    const QString &getFileName();
    virtual bool loadXml(const QString &file);
    QString getAttribute(const QString &xpath,const QString &attrName,const QString &defValue="");
    QString getValue(const QString &xpath,const QString &defValue="");
    bool getValues(const QString &xpath,QVector<QString> &values);
    bool getValues(const QString &xpath,const QString &tagName,QMap<QString,QString> &values);
    bool getAttributes(const QString &xpath,QMap<QString,QString> &attributes,const bool &ignoreCase=true);
    bool setAttribute(const QString &xpath,const QString &attrName,const QString &value);
    bool setNodeValue(const QString &xpath,const QString &value);
    bool getNodesSameAttr(const QString &xpath,const QString &keyAttrName,const QString &valueAttrName,QMap<QString,QString> &attrs,const bool keyUpper=false,const bool repSchar=false);
    bool getNodesSameAttr(const QString &xpath,const QString &attrName,QVector<QString> &values);

signals:
    //参数改变通知
    void  ValueChanged(const int msg,const void *data);
};

#endif // CONFIG_H
