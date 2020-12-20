#ifndef PASSWORD_H
#define PASSWORD_H
#include <QString>
#include <QCryptographicHash>

class Password
{
    QString password;
public:
    Password(QString = "");
    ~Password();
    void setPassword(QString);
    QString hashMd5(QString = "");
    bool compare(QString, QString = "");
};

#endif // PASSWORD_H
