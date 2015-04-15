#include <QFile>
#include "scanner.h"
#include "filebrowser.h"
QString Scanner::dbPath = "main.mdb";

void Scanner::generateTestVirus(const QString &fname) {
    QFile out(fname + "eicar.com");
    if (out.open(QIODevice::WriteOnly)) {
        throw GeneralException(tr("Error %1%2").arg(QString::number(out.error())).arg(out.errorString()));
    }
    out.write("X5O!P%@AP[4\\X5O!P%@AP[4\PZX54(P^)7CC)7}$EICAR-STANDARD-ANTIVIRUS-TEST-FILE!$H+H*PZX54(P^)7CC)7}$EICAR-STANDARD-ANTIVIRUS-TEST-FILE!$H+H*");
    out.close();
}

void Scanner::check(const QString &targetName,
                    bool isRecursive,
                    const QString &ext) {


    QList<FileInfo *> fileLst = FileBrowser::getFileList(targetName, isRecursive, ext);
    int infectedCount = 0;
    try {
        int cnt = 0;
        for (auto &it: fileLst) {
            cnt++;
            emit(log(tr("Scanning %1").arg(it->getFileInfo().absoluteFilePath())));
            if (mSignatureAnalyzer.isMalWare(it)) {
                infectedCount++;
                bool res = mMalwareHandler.HandleMalware((it)->getFileInfo().absoluteFilePath());
                QString logStr = (it)->getFileInfo().absoluteFilePath();

                switch (mPolicy) {
                case MPOL_REMOVE:
                    logStr = (res) ? logStr + tr(" Removed Successfully") : tr("Failed to remove ") + logStr;
                    break;
                case MPOL_SKIP:
                    logStr = tr("Skipped ") + logStr;
                    break;
                case MPOL_ASK:
                    logStr = (res) ? logStr + tr(" Removed Successfully") : tr("Skipped ") + logStr;
                    break;
                default:
                    break;
                }
                emit(log(logStr));
            } else {
                emit(log(tr("File is OK!")));
            }
        }
    }
    catch (GeneralException &e) {
        emit(log(tr("Scanning Aborted")));
        emit(log(e.getMessage()));
    }
    emit(log(tr("Scanner Log Infected %1/%2").arg(infectedCount).arg(fileLst.size())));


    for (auto &it: fileLst) {
        delete it;
    }
}

void Scanner::setPolicy(MalwarePolicy policy)
{
    mPolicy = policy;
    mMalwareHandler.setPolicy(policy);
}

