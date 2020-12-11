#include "UserService.h"

UserService* UserService::_userService = nullptr;

UserService::UserService()
{
    this->_userRepository = UserRepository::initUserRepository();
}

UserService::~UserService()
{

}

UserService* UserService::initUserService()
{
    if (_userService == nullptr)
    {
        _userService = new UserService();
    }

    return _userService;
}

Listt<User>* UserService::findAll()
{
    return this->_userRepository->findAll();
}

