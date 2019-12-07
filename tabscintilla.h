#ifndef TABSCINTILLA_H
#define TABSCINTILLA_H

#include "Qsci/qsciscintilla.h"
#include <QTabWidget>
#include <QHBoxLayout>
#include <QCryptographicHash>

class TabScintilla;

class TabPage:public QWidget
{
    friend class TabScintilla;
public:
    TabPage(const QString &_fileName);
    ~TabPage();

    void setTextEdit(QsciScintilla *_pEdit);
private:
    bool isSave=true;
    QString fileName="";
    QsciScintilla *pEdit=nullptr;
    QHBoxLayout *pLayout=nullptr;
};

class TabScintilla:public QTabWidget
{
public:
    TabScintilla();
    ~TabScintilla();

    void clearPages();
    TabPage *addPage(const QString &file="");
    void removePage(const QString &file);
    TabPage *getPage(const QString &file);
private:
    int ufileCnt=0;
    QByteArray tmpBytes,tmpBytes2;
    QCryptographicHash *pMd5=nullptr;
    QsciScintilla *mainEdit=nullptr;
    QsciScintilla *subEdit=nullptr;
    void tabCloseRequested(int index);
    void currentChanged(int index);
    const QString getMd5(const QString &value);
};

#endif // TABSCINTILLA_H
