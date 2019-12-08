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
    TabPage(TabScintilla *_pParent,const QString &_fileName);
    ~TabPage();

    void setTextEdit(QsciScintilla *_pEdit);
private:
    TabScintilla *pParent=nullptr;
    bool isSave=true;
    QString fileName="";
    QsciScintilla *pEdit=nullptr;
    QHBoxLayout *pLayout=nullptr;
    void setSaveStatus(bool _isSave);
};

class TabScintilla:public QTabWidget
{
    friend class TabPage;
public:
    TabScintilla();
    ~TabScintilla();

    void clearPages();
    TabPage *addPage(const QString &file="");
    void removePage(const QString &file);
    TabPage *getPage(const QString &file);
private:
    int ufileCnt=0;
    QIcon *pSaveIcon=nullptr;
    QIcon *puSaveIcon=nullptr;
    QIcon *pReadOnlyIcon=nullptr;
    QByteArray tmpBytes,tmpBytes2;
    QCryptographicHash *pMd5=nullptr;
    QsciScintilla *mainEdit=nullptr;
    void tabCloseRequested(int index);
    void currentChanged(int index);
    const QString getMd5(const QString &value);
};

#endif // TABSCINTILLA_H
