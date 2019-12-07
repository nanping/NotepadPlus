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
            xml_node *pChild=nullptr;
            if(!appendNodes(xpath,pChild)) return false;
            pChild->append_attribute(attrName.toStdString().c_str()).set_value(value.toStdWString().c_str());
        }else{
            node.node().append_attribute(attrName.toStdString().c_str()).set_value(value.toStdWString().c_str());
        }
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
            xml_node *pChild=nullptr;
            if(!appendNodes(xpath,pChild)) return false;
            pChild->set_value(value.toStdString().c_str());
        }else{
            node.node().set_value(value.toStdString().c_str());
        }
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

bool ConfigFile::appendNodes(const QString &xpath, xml_node *pChild)
{
    auto list=xpath.split("/");
    if(list.count()<2) return false;
    QMap<QString,QString> attrs;
    getNodeName(list[1],attrs);
    xml_node p= pDoc->child(list[1].toStdString().c_str());
    if(!p)
    {
        p=pDoc->append_child(list[1].toStdString().c_str());
    }
    for(auto it=attrs.begin();it!=attrs.end();it++)
    {
        p.append_attribute(it.key().toStdString().c_str()).set_value(it.value().toStdString().c_str());
    }
    for(auto i=1,size=list.count()-1;i<size;i++)
    {
        if(list[i].isEmpty())
        {
            throw "xpath has null path.\n"+xpath;
        }
        getNodeName(list[i],attrs);
        auto n=p.child(list[i].toStdString().c_str());
        if(!n)
        {
            n=p.append_child(list[i].toStdString().c_str());
            p=n;
        }
        for(auto it=attrs.begin();it!=attrs.end();it++)
        {
            n.append_attribute(it.key().toStdString().c_str()).set_value(it.value().toStdString().c_str());
        }
    }
    pChild=&p;
    return true;
}

void ConfigFile::getNodeName(QString &name,QMap<QString,QString> &attrs)
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
    QString key,value;
    bool flag1,flag2;
    int i,size=tmp.length();
    start=0;
    while((end=tmp.indexOf('=',start))>0)
    {
        key=tmp.mid(start+1,end-start-1).trimmed();
        start=end+1;
        if(key.isEmpty())  continue;
        flag1=false;
        flag2=false;
        value.clear();
        for(i=start;i<size;i++)
        {
            if(tmp[i]=='"')
            {
                if(flag1)
                {
                    if(i+1<size && tmp[i+1]!='"')
                    {
                        attrs.insert(key,value);
                        start=i+1;
                        key.clear();
                        break;
                    }else {
                        value.append(tmp[i]);
                    }
                }
                else{
                    flag1=true;
                }
            }
            else if(tmp[i]=='\'')
            {
                if(flag2)
                {
                    if(i+1<size && tmp[i+1]!='\'')
                    {
                        attrs.insert(key,value);
                        start=i+1;
                        key.clear();
                        break;
                    }else {
                        value.append(tmp[i]);
                    }
                }
                else{
                    flag2=true;
                }
            }
            else if(tmp[i]==' ' || tmp[i]=='\t' || tmp[i]=='\r' || tmp[i]=='\n')
            {
                if(flag1 || flag2)
                {
                    value.append(tmp[i]);
                }
            }
            else{
                value.append(tmp[i]);
            }
        }
        if(!key.isEmpty())
        {
            value=value.trimmed();
            attrs.insert(key,value);
        }
        start=i;
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

