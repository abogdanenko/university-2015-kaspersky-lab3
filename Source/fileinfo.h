#ifndef FILEINFO_H
#define FILEINFO_H
#include <QFileInfo>

class FileInfo: public QObject
{
    Q_OBJECT
    QFileInfo m_fileinfo;
    QString m_md5;
public:
    FileInfo(const QString &FileName): m_fileinfo(FileName) {}
    QFileInfo getFileInfo() {
        return m_fileinfo;
    }

    QString getMD5();
};

#endif // FILEINFO_H
