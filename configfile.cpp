#include "configfile.h"
#include "tools.h"
#include <QFile>
#include <QStandardPaths>
#include <fstream>

#include <QCoreApplication>

ConfigFile::ConfigFile():errMsg(""),pDoc(nullptr)
{
    //fileName=pathCombine({QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppDataLocation),"config.xml"});
    fileName=pathCombine({QCoreApplication::applicationDirPath(),"config.xml"});
}

ConfigFile::~ConfigFile()
{
    close();
}

void ConfigFile::close()
{
    if(pDoc)
    {
        delete pDoc;
        pDoc=nullptr;
    }
    errMsg.clear();
}

bool ConfigFile::isOpen()
{
    return (pDoc!=nullptr);
}

QString ConfigFile::getAttribute(const QString &xpath,const QString &attrName, const QString &defValue)
{
    auto node= querySingleNode(xpath.toStdString().c_str());
    if(!node) return defValue;
    auto attr= node.node().attributes();
    for(auto it=attr.begin();it!=attr.end();it++)
    {
        if(QString::compare(it->name(),attrName)==0)
        {
            return QString(it->value());
        }
    }
    return defValue;
}

QString ConfigFile::getValue(const QString &xpath,const QString &defValue)
{
    auto node= querySingleNode(xpath.toStdString().c_str());
    if(!node) return defValue;
    return node.node().text().get();
}

bool ConfigFile::getAttributes(const QString &xpath, QMap<QString, QString> &attributes)
{
    auto node= querySingleNode(xpath.toStdString().c_str());
    if(!node) return false;
    attributes.clear();
    auto attr= node.node().attributes();
    for(auto it=attr.begin();it!=attr.end();it++)
    {
        attributes.insert(it->name(),it->value());
    }
    return attributes.count()>0;
}

bool ConfigFile::getValues(const QString &xpath,QVector<QString> &values)
{
    auto list= queryNodes(xpath.toStdString().c_str());
    values.clear();
    for(auto it=list.begin();it!=list.end();it++)
    {
        values.append(it->node().text().get());
    }
    return values.count()>0;
}

bool ConfigFile::setAttribute(const QString &xpath,const  QString &attrName, QString &value)
{
    auto node= querySingleNode(xpath.toStdString().c_str());
    try {
        if(!node)
        {
            node=appendNodes(xpath);
            if(!node) return false;
        }
        node.node().append_attribute(attrName.toStdString().c_str()).set_value(value.toStdWString().c_str());
        pDoc->save_file(fileName.toStdWString().c_str(),"\t",1U,encoding_utf8);
        return true;
    }
    catch(xpath_exception &ex)
    {
        errMsg="xpath="+xpath+"\r\nvalue="+value+"\r\nerr="+ex.what();
    }
    catch (...) {
        errMsg="xpath="+xpath+"\r\nvalue="+value;
    }
    return false;
}

bool ConfigFile::setNodeValue(const QString &xpath, QString &value)
{
    auto node= querySingleNode(xpath.toStdString().c_str());
    try {
        if(!node)
        {
            node=appendNodes(xpath);
            if(!node) return false;
        }
        node.node().text().set(value.toStdString().c_str());
        pDoc->save_file(fileName.toStdWString().c_str(),"\t",1U,encoding_utf8);
        return true;
    }
    catch(xpath_exception &ex)
    {
        errMsg="xpath="+xpath+"\r\nvalue="+value+"\r\nerr="+ex.what();
    }
    catch (...) {
        errMsg="xpath="+xpath+"\r\nvalue="+value;
    }
    return false;
}

bool ConfigFile::loadXml(const QString &file)
{
    if(!file.isEmpty())
    {
        if(!fileExists(file)) return false;
        fileName=file;
    }else{
        if(!fileExists(fileName)) return false;
    }
    close();
    pDoc=new xml_document();
    xml_parse_result result= pDoc->load_file(fileName.toStdWString().c_str());
    if(result) return true;
    errMsg.sprintf("offset:%d\r\nmsg:%s",result.offset,result.description());
    close();
    return false;
}

bool ConfigFile::getNodesSameAttr(const QString &xpath, const QString &keyAttrName, const QString &valueAttrName, QMap<QString, QString> &attrs,const bool keyUpper,const bool repSchar)
{
    if(!isOpen()) return false;
    attrs.clear();
    QString key,value;
    auto tools=queryNodes(xpath);
    for(auto it=tools.begin();it!=tools.end();++it)
    {
        auto attr=it->node().attribute(keyAttrName.toStdString().c_str());
        if(!attr) continue;
        key=attr.value();
        if(keyUpper) key=key.toUpper();
        if(repSchar) key=key.replace('-','_');
        attr=it->node().attribute(valueAttrName.toStdString().c_str());
        if(attr)
        {
            value=attr.value();
        }else{
            value.clear();
        }
        if(attrs.find(key)!=attrs.end())
        {
            attrs.insert(key,value);
        }else{
            attrs[key]=value;
        }
    }
    return attrs.count()>0;
}

bool ConfigFile::getNodesSameAttr(const QString &xpath, const QString &attrName, QVector<QString> &values)
{
    if(!isOpen()) return false;
    values.clear();
    auto tools=queryNodes(xpath);
    for(auto it=tools.begin();it!=tools.end();++it)
    {
        auto attr=it->node().attribute(attrName.toStdString().c_str());
        if(!attr) continue;
        values.append(attr.value());
    }
    return values.count()>0;
}

xml_node ConfigFile::appendNodes(const QString &xpath)
{
    auto list=xpath.split("/");
    if(list.count()<2) return xml_node();
    QMap<QString,QString> attrs;
    int cnt=0;
    xml_node p,n;
    for(auto i=0,size=list.count();i<size;i++)
    {
        if(list[i].isEmpty()) continue;
        readName(list[i],attrs);
        if(!p)
        {
            p=pDoc->child(list[i].toStdString().c_str());
            if(!p) p=pDoc->append_child(list[i].toStdString().c_str());
            n=p;
        }else{
            n=p.child(list[i].toStdString().c_str());
            if(!n)
            {
                n=p.append_child(list[i].toStdString().c_str());
            }
            p=n;
        }
        for(auto it=attrs.begin();it!=attrs.end();it++)
        {
            auto attr=n.attribute(it.key().toStdString().c_str());
            if(attr)
            {
                attr.set_value(it.value().toStdString().c_str());
            }
            else{
                n.append_attribute(it.key().toStdString().c_str()).set_value(it.value().toStdString().c_str());
            }
        }
        cnt++;
    }
    return cnt>0 ? p:xml_node();
}

void ConfigFile::readName(QString &name,QMap<QString,QString> &attrs)
{
    attrs.clear();
    auto start=name.indexOf('[');
    if(start<0) return;
    auto end=name.lastIndexOf(']');
    if(end<=start)
    {
        name=name.mid(0,start).trimmed();
        return;
    }
    auto tmp=name.mid(start+1,end-start-1);
    name=name.mid(0,start).trimmed();
    if(tmp.indexOf("@")>=0)
    {
        QString key,value;
        int index;
        auto list=tmp.split(" and ",QString::SplitBehavior::SkipEmptyParts,Qt::CaseInsensitive);
        for(auto i=0,size=list.count();i<size;i++)
        {
            list[i]=list[i].trimmed();
            if(list[i].isEmpty() || !list[i].startsWith("@")) continue;
            if((index=list[i].indexOf('='))<1) continue;
            key=list[i].mid(1,index-1).trimmed();
            if(key.isEmpty()) continue;
            value=list[i].mid(index+1).trimmed();
            if(value.length()>1)
            {
                if(value.startsWith('"') && (index=value.indexOf('"',1))>1)
                {
                    value=value.mid(1,index-1);
                }
                else if(value.startsWith('\'') && (index=value.indexOf('\'',1))>1)
                {
                    value=value.mid(1,index-1);
                }
                else continue;
            }
            if(attrs.find(key)!=attrs.end())
            {
                attrs[key]=value;
            }else{
                attrs.insert(key,value);
            }
        }
    }
}

xpath_node ConfigFile::querySingleNode(const QString &xpath)
{
    try {
        return  pDoc->select_node(xpath.toStdString().c_str());
    }
    catch(xpath_exception &ex)
    {
        errMsg="xpath="+xpath+"\r\nerr="+ex.what();
    }
    catch (...) {
        errMsg="xpath="+xpath;
    }
    return xpath_node();
}

xpath_node_set ConfigFile::queryNodes(const QString &xpath)
{
    try {
        return  pDoc->select_nodes(xpath.toStdString().c_str());
    }
    catch(xpath_exception &ex)
    {
        errMsg="xpath="+xpath+"\r\nerr="+ex.what();
    }
    catch (...) {
        errMsg="xpath="+xpath;
    }
    return xpath_node_set();
}

