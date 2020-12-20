#include "Password.h"


Password::Password(QString password){
    this->password = password;
}

Password::~Password(){}

void Password::setPassword(QString password){
    this->password = password;
}

QString Password::hashMd5(QString salt){
    if (this->password.length() == 0) throw QString("Password is not set");
    return QString(QCryptographicHash::hash((this->password + salt).toLocal8Bit(), QCryptographicHash::Md5).toHex());
}

bool Password::compare(QString hash, QString salt){
    return this->hashMd5(salt) == hash;
}

