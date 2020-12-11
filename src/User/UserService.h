#ifndef USERSERVICE_H
#define USERSERVICE_H

#include "src/User/UserRepository.h"
#include "utils/ListPackage/Listt/Listt.h"
#include "src/User/User.h"

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

};

#endif // USERSERVICE_H
