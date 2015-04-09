#include <QCryptographicHash>
#include "fileinfo.h"
#include "generalexception.h"


enum {
    BLOCK_SIZE = 8912
};

static QByteArray calcMd5(const QString &fileName) {
    QCryptographicHash crypto(QCryptographicHash::Md5);
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        throw GeneralException(QObject::tr("Cant open file %1").arg(fileName));
    }
    while (!file.atEnd()) {
        crypto.addData(file.read(BLOCK_SIZE));
    }
    file.close();
    return crypto.result().toHex();
}

QString FileInfo::getMD5() {
    if (m_md5.isEmpty()) {
        m_md5 = calcMd5(m_fileinfo.absoluteFilePath());
    }
    return m_md5;
}
