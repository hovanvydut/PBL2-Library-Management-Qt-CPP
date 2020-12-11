#include "UserRepository.h"
#include <QDebug>

UserRepository* UserRepository::_userRepository = nullptr;

UserRepository::UserRepository()
{
    this->query = DatabaseConnection::initDatabaseConnection()->getQuery();
}

UserRepository::~UserRepository()
{

}

UserRepository* UserRepository::initUserRepository()
{
    if (_userRepository == nullptr)
    {
        _userRepository = new UserRepository();
    }

    return _userRepository;
}

User UserRepository::parse(QSqlQuery * query)
{
    int user_id = query->value(0).toInt();
    QString fullname = query->value(1).toString();
    QDate birthday = query->value(2).toDate();
    int gender = query->value(3).toInt();
    QString phone = query->value(4).toString();
    QString email = query->value(5).toString();
    return User(user_id, fullname, birthday, gender, phone, email);
}

Listt<User>* UserRepository::findAll()
{

    Listt<User>* list = new LinkedListt<User>();


    this->query->prepare("SELECT user_id, fullname, birthday, gender, phone, email "
                         "FROM users");


    this->query->exec();

    while(this->query->next())
    {
        list->add(this->parse(this->query));
    }

    return list;
}

