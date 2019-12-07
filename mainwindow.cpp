#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tools.h"
#include <QMap>
#include <QMessageBox>
#include "parameters.h"
#include "languages.h"
#include <QStandardPaths>

static Parameters *pParameter=Parameters::getInstancePtr();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    pParameter->init();
    //关联语言变更事件
    connect(pParameter,&Parameters::LanguageChanged,this,&MainWindow::LanguageChanged);
    ui->setupUi(this);
    ui->toolBar->setFloatable(false);//设置不可悬浮在主窗口
    ui->toolBar->setMovable(false);//设置不可移动
    ui->toolBar->setIconSize(QSize(16,16));//设置图标大小
    this->loadHistoryMenus();
    this->createStatusBar();
    //

    //QMessageBox::information(this,"AppDataLocation",QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppDataLocation));
    //QMessageBox::information(this,"AppConfigLocation",QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppConfigLocation));
    //QMessageBox::information(this,"AppLocalDataLocation",QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppLocalDataLocation));
    //QMessageBox::information(this,"ApplicationsLocation",QStandardPaths::writableLocation(QStandardPaths::StandardLocation::ApplicationsLocation));
    pParameter->changeLanguage();
    this->setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow()
{
    delete ui;
    if(lbldoc_type) delete lbldoc_type;
    if(lbldoc_size) delete lbldoc_size;
    if(lblcur_pos) delete lblcur_pos;
    if(lbleof_format) delete lbleof_format;
    if(lblunicode_type) delete lblunicode_type;
    if(lbltyping_mode) delete lbltyping_mode;
    freeHistoryMenus();
}

void MainWindow::loadHistoryMenus()
{
    freeHistoryMenus();
    Parameters *p=Parameters::getInstancePtr();
    QVector<QString> files;
    if(!p->getHistoryMenus(files)) return;
    QAction *pAction=nullptr,*pBefore=ui->IDM_FILE_EXIT;
    //
    pAction = new QAction(this);
    pAction->setSeparator(true);
    ui->file->insertAction(pBefore,pAction);
    historyFiles.append(pAction);
    pBefore=pAction;
    //
    pClean_Recent_File_List = new QAction("Empty Recent Files List",this);
    pClean_Recent_File_List->setObjectName("IDM_CLEAN_RECENT_FILE_LIST");
    ui->file->insertAction(pBefore,pClean_Recent_File_List);
    pBefore=pClean_Recent_File_List;
    //
    pOpen_All_Recent_File = new QAction("Open All Recent Files",this);
    pOpen_All_Recent_File->setObjectName("IDM_OPEN_ALL_RECENT_FILE");
    ui->file->insertAction(pBefore,pOpen_All_Recent_File);
    pBefore=pOpen_All_Recent_File;
    //
    pRestore_Last_Closed_File = new QAction("Restore Recent Closed File",this);
    pRestore_Last_Closed_File->setObjectName("IDM_FILE_RESTORELASTCLOSEDFILE");
    pRestore_Last_Closed_File->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+T", nullptr));
    ui->file->insertAction(pBefore,pRestore_Last_Closed_File);
    pBefore=pRestore_Last_Closed_File;
    //
    pAction = new QAction(this);
    pAction->setSeparator(true);
    ui->file->insertAction(pBefore,pAction);
    historyFiles.append(pAction);
    pBefore=pAction;
    //
    for(auto i=files.size()-1;i>=0;i--)
    {
        pAction = new QAction(files[i], this);
        ui->file->insertAction(pBefore,pAction);
        historyFiles.append(pAction);
        pBefore=pAction;
    }
    pAction = new QAction(this);
    pAction->setSeparator(true);
    ui->file->insertAction(pBefore,pAction);
    historyFiles.append(pAction);
    pBefore=pAction;
}

void MainWindow::freeHistoryMenus()
{
    if(pRestore_Last_Closed_File) {
        ui->file->removeAction(pRestore_Last_Closed_File);
        delete pRestore_Last_Closed_File;
        pRestore_Last_Closed_File=nullptr;
    }
    if(pOpen_All_Recent_File) {
        ui->file->removeAction(pOpen_All_Recent_File);
        delete pOpen_All_Recent_File;
        pOpen_All_Recent_File=nullptr;
    }
    if(pClean_Recent_File_List) {
        ui->file->removeAction(pClean_Recent_File_List);
        delete pClean_Recent_File_List;
        pClean_Recent_File_List=nullptr;
    }
    while(historyFiles.count()>0)
    {
        auto p=historyFiles[0];
        ui->file->removeAction(p);
        historyFiles.removeAt(0);
        delete p;
    }
    historyFiles.clear();
}

void MainWindow::createStatusBar()
{
    lbldoc_type=new QLabel("Normal text file");
    ui->statusbar->addWidget(lbldoc_type,1);//添加在左边并全部填充

    lbldoc_size=new QLabel("Length:80 lines:1");
    lbldoc_size->setMinimumWidth(200);
    ui->statusbar->addPermanentWidget(lbldoc_size);

    lblcur_pos=new QLabel("Ln:1 Col:1 Sel:80|1");
    lblcur_pos->setMinimumWidth(260);
    ui->statusbar->addPermanentWidget(lblcur_pos);

    lbleof_format=new QLabel("Windows(CR LF)");
    lbleof_format->setMinimumWidth(110);
    ui->statusbar->addPermanentWidget(lbleof_format);

    lblunicode_type=new QLabel("UTF-8");
    lblunicode_type->setMinimumWidth(120);
    ui->statusbar->addPermanentWidget(lblunicode_type);

    lbltyping_mode=new QLabel("INS");
    lbltyping_mode->setMinimumWidth(30);
    ui->statusbar->addPermanentWidget(lbltyping_mode);
}

void MainWindow::updateMenuText(QMenu *pMenu,QMap<QString, QString> &menus,QMap<QString, QString> &commands)
{
    int i,size;
    QString key;
    //更新一级菜单
    QList<QAction*> list=pMenu->actions();
    for(i=0,size=list.count();i<size;i++)
    {
        auto p=list[i];
        auto menu=p->menu();
        if(menu)
        {
            key=menu->objectName().toUpper();
            if(menus.find(key)!=menus.end()) {
                p->setText(menus[key]);
            }else{
                if(commands.find(key)!=commands.end()) p->setText(commands[key]);
            }
            updateMenuText(menu,menus,commands);
        }else{
            key=p->objectName().toUpper();
            if(commands.find(key)!=commands.end()) {
                p->setText(commands[key]);
            }else{
                if(menus.find(key)!=menus.end())  p->setText(menus[key]);
            }
        }
    }
}

void MainWindow::LanguageChanged()
{
    int i,size;
    QString key;
    QMap<QString, QString> mainMenus,subMenus,commands;
    //更新一级菜单
    QList<QAction*> list=ui->menubar->actions();
    Languages *pLan=Languages::getInstancePtr();
    pLan->getMainMenus(mainMenus);
    pLan->getSubMenus(subMenus);
    pLan->getCommands(commands);
    for(i=0,size=list.count();i<size;i++)
    {
        auto p=list[i];
        key=p->menu()->objectName().toUpper();
        if(mainMenus.find(key)!=mainMenus.end()) p->setText(mainMenus[key]);
        updateMenuText(p->menu(),subMenus,commands);
    }
}

