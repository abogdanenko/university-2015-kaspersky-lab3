#ifndef FILEINFO_H
#define FILEINFO_H
#include <QFileInfo>

class FileInfo
{
    QFileInfo m_fileinfo;
    QString m_md5;
public:
    FileInfo(const QString &aFileName): m_fileinfo(aFileName) {}
    QFileInfo getFileInfo() {
        return m_fileinfo;
    }

    QString getMD5();
};

#endif // FILEINFO_H
