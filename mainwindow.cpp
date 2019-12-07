#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tools.h"
#include <QMap>
#include <QMessageBox>
#include "parameters.h"
#include <QStandardPaths>

static Parameters *pParameter=Parameters::getInstancePtr();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //关联语言变更事件
    connect(pParameter,&Parameters::LanguageChanged,this,&MainWindow::LanguageChanged);
    ui->setupUi(this);
    ui->toolBar->setFloatable(false);//设置不可悬浮在主窗口
    ui->toolBar->setMovable(false);//设置不可移动
    ui->toolBar->setIconSize(QSize(16,16));//设置图标大小
    this->createStatusBar();
    //
    pParameter->init();
    //QMessageBox::information(this,"AppDataLocation",QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppDataLocation));
    //QMessageBox::information(this,"AppConfigLocation",QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppConfigLocation));
    //QMessageBox::information(this,"AppLocalDataLocation",QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppLocalDataLocation));
    //QMessageBox::information(this,"ApplicationsLocation",QStandardPaths::writableLocation(QStandardPaths::StandardLocation::ApplicationsLocation));

}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::updateMenuText(QMenu *pMenu,QMap<QString, QString> &lanValues)
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
            key=("/Menu/Main/SubEntries/"+menu->objectName()).toUpper();
            if(lanValues.find(key)!=lanValues.end())
            {
                p->setText(lanValues[key]);
                lanValues.remove(key);
            }
            updateMenuText(menu,lanValues);
        }else{
            key=("/Menu/Main/Commands/"+p->objectName()).toUpper();
            if(lanValues.find(key)!=lanValues.end())
            {
                p->setText(lanValues[key]);
                lanValues.remove(key);
            }
        }
    }
}

void MainWindow::LanguageChanged(QMap<QString, QString> &lanValues)
{
    int i,size;
    QString key;
    //更新一级菜单
    QList<QAction*> list=ui->menubar->actions();
    for(i=0,size=list.count();i<size;i++)
    {
        auto p=list[i];
        key=("/Menu/Main/Entries/"+p->menu()->objectName()).toUpper();
        if(lanValues.find(key)!=lanValues.end())
        {
            p->setText(lanValues[key]);
            lanValues.remove(key);
        }
        updateMenuText(p->menu(),lanValues);
    }
}

