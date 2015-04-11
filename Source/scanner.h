#ifndef SCANNER_H
#define SCANNER_H

#include <QObject>
#include "malwarehandler.h"
#include "generalexception.h"
#include "signatureanalyzer.h"
class Scanner : public QObject
{
    Q_OBJECT
    static QString dbPath;
    SignatureAnalyzer mSignatureAnalyzer;
    MalwareHandler mMalwareHandler;
    MalwarePolicy mPolicy;
public:
    Scanner() : mPolicy(MPOL_REMOVE) {
        mMalwareHandler.setPolicy(mPolicy);
        try {
            mSignatureAnalyzer.loadDataBase(dbPath);
        }
        catch(GeneralException &e) {
            emit log(e.getMessage());
        }
    }
    void generateTestVirus(const QString &fname);
    void check(const QString &targetName,
               bool  isRecursive = false,
               const QString &ext = QString("*.*"));

    void setPolicy(MalwarePolicy policy);
signals:
    void log(QString Message);
};

#endif // SCANNER_H
