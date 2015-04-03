#include <QCryptographicHash>
#include <QTranslator>
#include "fileinfo.h"
#include "generalexception.h"
QString FileInfo::getMD5() {
    if (m_md5.isEmpty()) {
        QFile in(m_fileinfo.absoluteFilePath());
        if (!in.open(QIODevice::ReadOnly)) {
            throw GeneralException(tr("Cant open file %1").arg(m_fileinfo.absoluteFilePath()));
        }
        QByteArray buff = in.readAll();
        in.close();
        m_md5 = QString(QCryptographicHash::hash(buff,QCryptographicHash::Md5));
    }
    return m_md5;
}
