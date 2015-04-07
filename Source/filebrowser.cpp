#include "filebrowser.h"
#include <QStack>
#include <QRegExp>
#include <QDir>
#include <QMetaClassInfo>
static inline bool wildCardMatch(const QString &name, const QString &pattern) {
    QRegExp regExp(pattern, Qt::CaseSensitive, QRegExp::Wildcard);
    return regExp.exactMatch(name);
}


QList<FileInfo *> FileBrowser::getFileList(const QString &TargetName,
                                           bool Recursive,
                                           const QString &Ext) {
    QList<FileInfo *> res;
    FileInfo *rootInfo = new FileInfo(TargetName);
    if (rootInfo->getFileInfo().isFile() && !wildCardMatch(TargetName, Ext)) {
        return res;
    }

    res.append(rootInfo);
    if (rootInfo->getFileInfo().isDir()) {
        QStack<QString> stack;
        do {
            QDir currentDir(TargetName);
            QStringList files = currentDir.entryList(QStringList(Ext), QDir::Files);
            for (auto &it: files) {
                FileInfo *currentFile = new FileInfo(it);
                res.append(currentFile);
            }
            QStringList dirs = currentDir.entryList(QDir::Filter::Dirs);
            for (auto &it: files) {
                stack.push_back(it);
            }
        } while (Recursive && !stack.empty());
    }
    return res;
}
QString FileBrowser::getInfo() {
    FileBrowser tmpobj;
    QString ver = QString(tmpobj.metaObject()->classInfo(0).name()) + ':' +  QString(tmpobj.metaObject()->classInfo(0).value());
    QString year = QString(tmpobj.metaObject()->classInfo(1).name()) + ':' +  QString(tmpobj.metaObject()->classInfo(1).value());
    return tr("%1 %2 \n%3").arg(tmpobj.metaObject()->className())
           .arg(ver)
           .arg(year);
}