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

Listt<User>* UserService::findByFullname(QString fullname)
{
    return this->_userRepository->findContain("fullname", fullname);
}

Listt<User>* UserService::findByPhone(QString phone)
{
    return this->_userRepository->findContain("phone", phone);
}

Listt<User>* UserService::findById(int id)
{
    return this->_userRepository->findExact("user_id", QString::number(id));
}

Listt<BorrowBook>* UserService::getBorrowBook(int id){
    return this->_userRepository->getBorrowBook(id);
}

int UserService::returnBook(Listt<int>* listId){
    return this->_userRepository->returnBook(listId);
}

int UserService::deleteUsers(Listt<User>* listUser){
    return this->_userRepository->deleteUsers(listUser);
}

void UserService::addUser(const User& user){
    this->_userRepository->addUser(user);
}

void UserService::updateUser(const User& user){
    this->_userRepository->updateUser(user);
}
