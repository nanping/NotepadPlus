#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

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
    QLabel *lbldoc_type,*lbldoc_size,*lblcur_pos,*lbleof_format,*lblunicode_type,*lbltyping_mode;
    void createStatusBar();
    void updateMenuText(QMenu *pMenu,QMap<QString, QString> &lanValues);

private slots:
    //接收语言变更通知后，更新UI界面
    void  LanguageChanged(QMap<QString, QString> &lanValues);
};
#endif // MAINWINDOW_H
