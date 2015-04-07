#ifndef FILEBROWSER_H
#define FILEBROWSER_H
#include <QList>
#include "fileinfo.h"
class FileBrowser: public QObject
{
    Q_OBJECT
    Q_CLASSINFO("author", "Kamil Khamitov")
    Q_CLASSINFO("year:", "2015")

public:
    static QList<FileInfo *> getFileList(const QString &TargetName,
                                         bool Recursive,
                                         const QString &Ext = "*.*");
    static QString getInfo();
};

#endif // FILEBROWSER_H
