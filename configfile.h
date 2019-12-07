#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QMap>
#include <QVector>
#include <QObject>
#include "pugixml/pugixml.hpp"

using namespace pugi;

class ConfigFile:public QObject
{
    Q_OBJECT
public:
    ConfigFile();
    ~ConfigFile();

private:
    QString fileName;
    QString errMsg;
    xml_document *pDoc;
    bool appendNodes(const QString &xpath,xml_node *pChild);
    void getNodeName(QString &name,QMap<QString,QString> &attrs);
public:
    void close();
    bool loadXml(const QString &file="");
    QString getAttribute(const QString &xpath,const QString &attrName,const QString &defValue="");
    QString getValue(const QString &xpath,const QString &defValue="");
    bool getValues(const QString &xpath,QVector<QString> &values);
    bool getAttributes(const QString &xpath,QMap<QString,QString> &attributes);
    bool setAttribute(const QString &xpath,const QString &attrName,QString &value);
    bool setNodeValue(const QString &xpath,QString &value);
    xpath_node querySingleNode(const QString &xpath);
    xpath_node_set queryNodes(const QString &xpath);
};

#endif // CONFIG_H
