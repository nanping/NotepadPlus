#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "tabscintilla.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    TabScintilla *tabMain=nullptr;
    QLabel *lbldoc_type=nullptr,*lbldoc_size=nullptr,*lblcur_pos=nullptr,*lbleof_format=nullptr,*lblunicode_type=nullptr,*lbltyping_mode=nullptr;
    QAction *pRestore_Last_Closed_File=nullptr,*pOpen_All_Recent_File=nullptr,*pClean_Recent_File_List=nullptr;
    QVector<QAction*> historyFiles;
    void loadHistoryMenus();
    void freeHistoryMenus();
    void createStatusBar();
    void freeStatusBar();
    void updateMenuText(QMenu *pMenu,QMap<QString, QString> &menus,QMap<QString, QString> &commands);

private slots:
    //接收语言变更通知后，更新UI界面
    void  LanguageChanged();
};
#endif // MAINWINDOW_H
