#ifndef SIGNATUREANALYZER_H
#define SIGNATUREANALYZER_H

#include <QObject>
#include <QHash>
#include "malwareinfo.h"
#include "fileinfo.h"

class SignatureAnalyzer : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("author", "Kamil Khamitov")
    Q_CLASSINFO("year:", "2015")

    QHash<QString, MalwareInfo*> malwareDb;
public:
    static QString getInfo();
    void loadDataBase(const QString  &fileName);
    bool isMalWare(FileInfo *info);
};

#endif // SIGNATUREANALYZER_H
