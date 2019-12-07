#include "tools.h"
#include <QDir>

const QString pathCombine(initializer_list<QString> lst) noexcept
{
    QString result="";
    for(auto &a:lst)
    {
        if(a.isEmpty()) continue;
        if(!a.startsWith(QDir::separator()))
        {
            if(!result.isEmpty() && !result.endsWith(QDir::separator()))
            {
                result.append(QDir::separator());
            }
            result.append(a);
        }else{
            result.append(a.mid(1));
        }
    }
    return result;
}

bool fileExists(const QString &fileName)
{
    QFileInfo file(fileName);
    if(!file.exists()) return false;
    return file.isFile();
}

bool pathExists(const QString &fileName)
{
    QFileInfo file(fileName);
    if(!file.exists()) return false;
    return file.isDir();
}
