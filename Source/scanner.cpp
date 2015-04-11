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
    try {
        for (auto &it: fileLst) {
            if (mSignatureAnalyzer.isMalWare(it)) {
                bool res = mMalwareHandler.HandleMalware((it)->getFileInfo().absolutePath());
                QString logStr = (it)->getFileInfo().absolutePath();

                switch (mPolicy) {
                case MPOL_REMOVE:
                    logStr = (res) ? logStr + tr(" Removed Successfully") : tr("Failed to remove ") + logStr;
                    break;
                case MPOL_SKIP:
                    logStr = tr("Skipped ") + logStr;
                    break;
                default:
                    break;
                }

                emit(logStr);
            }
        }
    }
    catch (GeneralException &e) {
        emit(e.getMessage());
    }

    for (auto &it: fileLst) {
        delete it;
    }
}

void Scanner::setPolicy(MalwarePolicy policy)
{
    mPolicy = policy;
    mMalwareHandler.setPolicy(policy);
}

