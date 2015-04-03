#ifndef GENERALEXCEPTION_H
#define GENERALEXCEPTION_H
#include <QString>
#include <QObject>

class GeneralException
{

private:
    QString m_message;
public:
    GeneralException(const QString &message): m_message(message) {}
    QString getMessage();
};

#endif // GENERALEXCEPTION_H
