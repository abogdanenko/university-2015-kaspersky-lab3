#include "fileinfo.h"
#include <QCryptographicHash>
QString FileInfo::getMD5() {
    if (m_md5.isEmpty()) {
        QFile in(m_fileinfo.absoluteFilePath());
        in.open(QIODevice::ReadOnly);
        QByteArray buff = in->readAll();
        in.close();
        m_md5 = QString(QCryptographicHash::hash(buff,QCryptographicHash::Md5));
    }
    return m_md5;
}
