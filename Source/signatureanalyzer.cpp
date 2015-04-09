#include <QMetaClassInfo>
#include <QCryptographicHash>
#include "signatureanalyzer.h"
#include "generalexception.h"
QString SignatureAnalyzer::getInfo() {
    SignatureAnalyzer tmpobj;
    QString ver = QString(tmpobj.metaObject()->classInfo(0).name()) + ':' +  QString(tmpobj.metaObject()->classInfo(0).value());
    QString year = QString(tmpobj.metaObject()->classInfo(1).name()) + ':' +  QString(tmpobj.metaObject()->classInfo(1).value());
    return tr("%1 %2 \n%3").arg(tmpobj.metaObject()->className())
           .arg(ver)
           .arg(year);
}

void SignatureAnalyzer::loadDataBase(const QString &fileName) {
    QFile in(fileName);
    if (!in.open(QIODevice::ReadOnly)) {
        throw GeneralException(tr("Error %1").arg(in.errorString()));
    }

    while (!in.atEnd()) {
        QString ln = in.readLine();
        MalwareInfo *mInfo = new MalwareInfo(ln);
        malwareDb.insert(mInfo->getMD5(), mInfo);
    }
    in.close();

}

bool SignatureAnalyzer::isMalWare(FileInfo *info) {
    return (malwareDb.find(info->getMD5()) != malwareDb.end());
}
