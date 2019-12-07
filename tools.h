#ifndef TOOLS_H
#define TOOLS_H

#include <QString>
#include <initializer_list>
#include <QFileInfo>

using namespace std;

//合并路径
const QString pathCombine(initializer_list<QString> lst) noexcept;
//判断文件是否存在
bool fileExists(const QString &fileName);
//判断路劲是否存在
bool pathExists(const QString &fileName);

#endif // TOOLS_H
