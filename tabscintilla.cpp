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
    this->setIconSize(QSize(16,16));
    pSaveIcon=new QIcon();
    pSaveIcon->addFile(QString::fromUtf8(":/images/saveFile.bmp"), QSize(), QIcon::Normal, QIcon::Off);

    puSaveIcon=new QIcon();
    puSaveIcon->addFile(QString::fromUtf8(":/images/unsaved.ico"), QSize(), QIcon::Normal, QIcon::Off);

    pReadOnlyIcon=new QIcon();
    pReadOnlyIcon->addFile(QString::fromUtf8(":/images/readonly.ico"), QSize(), QIcon::Normal, QIcon::Off);

    connect(this,&QTabWidget::tabCloseRequested,this,&TabScintilla::tabCloseRequested);
    connect(this,&QTabWidget::currentChanged,this,&TabScintilla::currentChanged);

    pMd5=new QCryptographicHash(QCryptographicHash::Md5);
    mainEdit = new QsciScintilla;

    //行号显示区域
    mainEdit->setMarginType(0, QsciScintilla::NumberMargin);
    mainEdit->setMarginLineNumbers(0, true);
    mainEdit->setMarginWidth(0,30);
    //自动折叠区域
    mainEdit->setMarginType(3, QsciScintilla::SymbolMargin);
    mainEdit->setMarginLineNumbers(3, false);
    mainEdit->setMarginWidth(3, 15);
    mainEdit->setMarginSensitivity(3, true);

    this->addPage("");
    this->addPage("");
}

TabScintilla::~TabScintilla()
{
    if(mainEdit)
    {
        delete mainEdit;
        mainEdit=nullptr;
    }
    if(pMd5)
    {
        delete pMd5;
        pMd5=nullptr;
    }
    if(pSaveIcon!=nullptr)
    {
        delete pSaveIcon;
        pSaveIcon=nullptr;
    }
    if(puSaveIcon!=nullptr)
    {
        delete puSaveIcon;
        puSaveIcon=nullptr;
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
        page=new TabPage(this,file);
        page->setObjectName(getMd5(file));
        auto index=this->addTab(page, fInfo.fileName());
        this->setTabIcon(index,*pSaveIcon);
        this->setTabToolTip(index,file);
    }
    else{
        QString id=QString("new %1").arg(++ufileCnt);
        page=new TabPage(this,id);
        page->isSave=false;
        page->setObjectName(getMd5(id));
        auto index=this->addTab(page, id);
        this->setTabIcon(index,*puSaveIcon);
        this->setTabToolTip(index,id);
    }
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

TabPage::TabPage(TabScintilla *_pParent,const QString &_fileName)
{
    pParent=_pParent;
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

void TabPage::setSaveStatus(bool _isSave)
{
    if(_isSave==isSave) return;
    int index=pParent->indexOf(static_cast<QWidget*>(this));
    if(index<0) return;
    isSave=_isSave;
    if(isSave)
    {
        pParent->setTabIcon(index,*pParent->pSaveIcon);
    }else{
        pParent->setTabIcon(index,*pParent->puSaveIcon);
    }
}
