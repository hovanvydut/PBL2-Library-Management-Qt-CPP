#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include <QSqlQuery>
#include <QVariant>
#include "base/Repository/Repository.h"
#include "src/User/User.h"
#include "utils/ListPackage/LinkedListt/LinkedListt.h"
#include "utils/DatabaseConnection/DatabaseConnection.h"

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
    int returnBook(Listt<int>*);
    int deleteUsers(Listt<User>*);
    void addUser(const User&);
    void validateBeforeInsert(const User&);
    void updateUser(const User&);
    void validateBeforeUpdate(const User&);
    void validateBorrowList(Listt<BorrowBook>*);
    void borrowBooks(Listt<BorrowBook>*);


};

#endif // USERREPOSITORY_H
