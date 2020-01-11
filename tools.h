#ifndef TOOLS_H
#define TOOLS_H

#include <QObject>
#include <stdio.h>
#include <locale>
#include <codecvt>
#include <cerrno>
#include <QString>
#include <initializer_list>
#include <QFileInfo>
#include <QDir>
#include <QMessageBox>
#include <QWidget>
#include "uchardet/uchardet.h"
#include "EncodingMapper.h"

#ifdef Q_OS_WIN
    #include "winclass.h"
#else
    #include <iconv.h>
#endif

//提示窗口封装
void msgboxWarn(const QString &text,const QString &title="警告",QWidget *parent=nullptr);
void msgboxInfo(const QString &text,const QString &title="提示",QWidget *parent=nullptr);
void msgboxErr(const QString &text,const QString &title="错误",QWidget *parent=nullptr);
int  msgboxQst(const QString &text,const QString &title="询问",QWidget *parent=nullptr,QMessageBox::StandardButtons buttons = QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No),QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);

//合并路径
const QString pathCombine(std::initializer_list<QString> lst) noexcept;
//判断文件是否存在
bool fileExists(const QString &fileName);
//判断路劲是否存在
bool pathExists(const QString &fileName);
//多字节与宽字符之间相互转换
bool encodeConvert(const char *codeFrom,const char *codeTo,const char *inbuf,const size_t inlen, std::string &out,int *pBytesNotProcessed=nullptr);
//指定编码的宽字符转换
const std::string ws2s(const std::wstring& src,bool &success,const std::locale &sys_locale=std::locale(""));
//指定编码的字符转换
const std::wstring s2ws( const std::string& src,bool &success,const std::locale &sys_locale=std::locale(""));
//unicode转换成UTF-8
const std::string ws2utf8( const std::wstring& src );
//UTF-8转换成unicode
const std::wstring utf8_2_ws( const std::string& src );
//探测字符编码类别
const QString detectEncode(const char *buf, const size_t len);
//比较字符串是否相等
bool compare(const std::string &str1,const std::string &str2,const bool ignoreCase=true);
//转换编码
const std::string encode(const char* fromCode, const char* toCode, const char *txt2Encode, int lenIn=-1, int *pBytesNotProcessed=nullptr);

#endif // TOOLS_H
