#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include <QSqlQuery>
#include <QVariant>
#include "base/Repository/Repository.h"
#include "src/User/User.h"
#include "utils/ListPackage/LinkedListt/LinkedListt.h"
#include "utils/DatabaseConnection/DatabaseConnection.h"
#include "src/BorrowBook/BorrowBook.h"

class UserRepository : public Repository<User>
{

private:
    static UserRepository* _userRepository;
    QSqlQuery* query;
    UserRepository();

public:
    static UserRepository* initUserRepository();
    ~UserRepository();
    User parse(QSqlQuery *);
    BorrowBook parseBorrowBook(QSqlQuery *);
    Listt<User>* findAll();
    Listt<User>* findContain(QString, QString);
    Listt<User>* findExact(QString, QString);
    Listt<BorrowBook>* getBorrowBook(int);


};

#endif // USERREPOSITORY_H
