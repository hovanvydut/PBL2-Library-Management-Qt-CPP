#ifndef USERSERVICE_H
#define USERSERVICE_H

#include "src/User/UserRepository.h"
#include "utils/ListPackage/Listt/Listt.h"
#include "src/User/User.h"
#include "src/BorrowBook/BorrowBook.h"

class UserService
{

private:
    static UserService* _userService;
    UserRepository* _userRepository;
    UserService();

public:
    static UserService* initUserService();
    ~UserService();
    Listt<User>* findAll();
    Listt<User>* findByFullname(QString);
    Listt<User>* findByPhone(QString);
    Listt<User>* findById(int);
    Listt<BorrowBook>* getBorrowBook(int);
    int returnBook(Listt<int>*);
    int deleteUsers(Listt<User>*);
    void addUser(const User&);

};

#endif // USERSERVICE_H
