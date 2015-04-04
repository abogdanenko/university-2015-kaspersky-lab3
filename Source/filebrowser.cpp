#include "filebrowser.h"
#include <QStack>
#include <QRegExp>
#include <QDir>
int FileBrowser::m_Version = 0x01;
int FileBrowser::m_Year = 2015;

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
    return tr("File Browser V%1 \n%2 Khamitov Kamil").arg(QString::number(m_Version)
                                                          .arg(QString::number(m_Year)));
}
