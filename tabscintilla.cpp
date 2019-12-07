#include "tabscintilla.h"
#include <QFileInfo>
#include <QMessageBox>

#include "tools.h"
/*
ui->tabWidget->setTabIcon(0,QIcon("F:\\磊神图片\\icons\\2.ico"));//设置选项卡图标
ui->tabWidget->setTabEnabled(0,false);//禁用选项卡
ui->tabWidget->setTabEnabled(1,false);
ui->tabWidget->setTabToolTip(2,tr("Beautiful"));//鼠标悬停弹出提示
ui->tabWidget->usesScrollButtons();//选项卡太多滚动

//ui->tabWidget->removeTab(0);//移除选项卡
//ui->tabWidget->setTabWhatsThis(3,tr("Beautiful Girl"));//不知道干嘛的
//ui->tabWidget->setTabBarAutoHide(true);//包含少于2个选项卡时会自动隐藏
//ui->tabWidget->setTabText(0,tr("软件"));//按索引修改选项卡的名称
//ui->tabWidget->setTabText(1,tr("舞蹈"));
//ui->tabWidget->setDocumentMode(true);//设置选项卡是否以适合文档页面的模式呈现
//ui->tabWidget->setElideMode(Qt::ElideLeft);//标签栏中删除文字

//ui->tabWidget->clear();//清空选项卡
*/
TabScintilla::TabScintilla()
{
    this->setTabsClosable(true);
    this->setMovable(true);
    this->usesScrollButtons();
    connect(this,&QTabWidget::tabCloseRequested,this,&TabScintilla::tabCloseRequested);
    connect(this,&QTabWidget::currentChanged,this,&TabScintilla::currentChanged);

    pMd5=new QCryptographicHash(QCryptographicHash::Md5);
    mainEdit = new QsciScintilla;
    subEdit = new QsciScintilla;
    auto page=this->addPage("");
    page=this->addPage("");
}

TabScintilla::~TabScintilla()
{
    if(mainEdit)
    {
        delete mainEdit;
        mainEdit=nullptr;
    }
    if(subEdit)
    {
        delete subEdit;
        subEdit=nullptr;
    }
    if(pMd5)
    {
        delete pMd5;
        pMd5=nullptr;
    }
}

void TabScintilla::clearPages()
{
    ufileCnt=0;
    tmpBytes.clear();
    tmpBytes.clear();
    auto list=this->children();
    while(list.count()>0)
    {
        TabPage *p=static_cast<TabPage *>(list[0]);
        if(!p->isSave)
        {
            this->setCurrentWidget(p);
        }
        list.removeAt(0);
        delete p;
    }
    this->clear();
}

TabPage *TabScintilla::addPage(const QString &file)
{
    TabPage *page=getPage(file);
    if(page)
    {
        this->setCurrentWidget(static_cast<QWidget*>(page));
        return page;
    }
    if(fileExists(file))
    {
        QFileInfo fInfo(file);
        page=new TabPage(file);
        page->setObjectName(getMd5(file));
        this->addTab(page, fInfo.fileName());
    }
    else{
        QString id=QString("new %1").arg(++ufileCnt);
        page=new TabPage(id);
        page->isSave=false;
        page->setObjectName(getMd5(id));
        this->addTab(page, id);
    }
    this->setCurrentWidget(static_cast<QWidget*>(page));
    return page;
}

void TabScintilla::removePage(const QString &file)
{
    TabPage *page=getPage(file);
    if(!page) return;
    int index=this->indexOf(static_cast<QWidget*>(page));
    if(index<0) return;
    this->removeTab(index);
    if(!page->isSave)
    {
        --ufileCnt;
        if(ufileCnt<0) ufileCnt=0;
    }
    delete page;
}

TabPage *TabScintilla::getPage(const QString &file)
{
    if(file.isEmpty()) return nullptr;
    QString id=getMd5(file);
    return this->findChild<TabPage *>(id);
}

void TabScintilla::tabCloseRequested(int index)
{
    this->setCurrentIndex(index);
    TabPage *page=static_cast<TabPage*>(this->currentWidget());
    if(!page) return;
    if(!page->isSave)
    {
        if(QMessageBox::question(this,QString("询问"),QString("保存文件吗？\r\n%1").arg(page->fileName),
                                 QMessageBox::Yes|QMessageBox::No,QMessageBox::No)!=QMessageBox::Yes)
        {
            return;
        }
    }
    this->removeTab(index);
    delete page;
}

void TabScintilla::currentChanged(int /*index*/)
{
    TabPage *page=static_cast<TabPage*>(this->currentWidget());
    if(!page) return;
    page->setTextEdit(mainEdit);
}

const QString TabScintilla::getMd5(const QString &value)
{
    if(value.isEmpty()) return "";
    tmpBytes.clear();
    tmpBytes.clear();
    tmpBytes.append(value);
    pMd5->addData(tmpBytes);
    tmpBytes2=pMd5->result();
    QString rt= tmpBytes2.toHex();
    tmpBytes.clear();
    tmpBytes.clear();
    return rt;
}

TabPage::TabPage(const QString &_fileName)
{
    fileName=_fileName;
    pLayout=new QHBoxLayout(this);
}

TabPage::~TabPage()
{
    if(pLayout)
    {
        delete pLayout;
        pLayout=nullptr;
    }
    pEdit=nullptr;
}

void TabPage::setTextEdit(QsciScintilla *_pEdit)
{
    if(!_pEdit) return;
    if(pEdit) pLayout->removeWidget(pEdit);
    pEdit=_pEdit;
    pLayout->addWidget(pEdit);
    pLayout->setContentsMargins(0,0,0,0);
}
