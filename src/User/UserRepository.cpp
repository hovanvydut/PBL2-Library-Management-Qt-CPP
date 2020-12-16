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

Listt<User>* UserRepository::findContain(QString key, QString value)
{

    Listt<User>* list = new LinkedListt<User>();

    QString queryText = "SELECT user_id, fullname, birthday, gender, phone, email "
                        "FROM users WHERE lower(" + key + ") LIKE lower(:value)";
    this->query->prepare(queryText);
    this->query->bindValue(":value", QString("%%1%").arg(value));

    this->query->exec();

    while(this->query->next())
    {
        list->add(this->parse(this->query));
    }

    return list;
}

Listt<User>* UserRepository::findExact(QString key, QString value)
{

    Listt<User>* list = new LinkedListt<User>();

    QString queryText = "SELECT user_id, fullname, birthday, gender, phone, email "
                        "FROM users WHERE " + key + " = :value";
    this->query->prepare(queryText);
    this->query->bindValue(":value", value);

    this->query->exec();

    while(this->query->next())
    {
        list->add(this->parse(this->query));
    }

    return list;
}

BorrowBook UserRepository::parseBorrowBook(QSqlQuery * query){
    int book_id = query->value(0).toInt();
    QString title = query->value(1).toString();
    QString cover_type = query->value(2).toString();
    float price = query->value(3).toFloat();
    int total = query->value(4).toInt();
    int available = query->value(5).toInt();
    QDate publication_date = query->value(6).toDate();
    QString size = query->value(7).toString();
    int number_of_pages = query->value(8).toInt();
    int issuing_company_id = query->value(9).toInt();
    int publisher_id = query->value(10).toInt();
    int category_id = query->value(11).toInt();
    QDate created_at = query->value(12).toDate();
    QDate updated_at = query->value(13).toDate();
    QDate deleted_at = query->value(14).toDate();

    Book book(book_id, title, cover_type, price, total, available, publication_date, size
                , number_of_pages, issuing_company_id, publisher_id, category_id,
                created_at, updated_at, deleted_at);

    QDate borrowed_at = query->value(15).toDate();
    int quantity = query->value(16).toInt();
    int num_of_day = query->value(17).toInt();
    int deposit_money = query->value(18).toInt();
    QDate updated_at_ = query->value(19).toDate();
    int borrow_id = query->value(20).toInt();

    return BorrowBook(borrow_id, borrowed_at, quantity, book, num_of_day, deposit_money, updated_at_);
}

Listt<BorrowBook>* UserRepository::getBorrowBook(int id){
    Listt<BorrowBook>* list = new LinkedListt<BorrowBook>();

    QString queryText = "select books.book_id, title, cover_type, price, total, available, publication_date, size, number_of_pages, issuing_company_id, publisher_id, category_id, books.created_at, books.updated_at, books.deleted_at, borrowed_at, quantity, numberOfDay, deposit_money, borrow_books.updated_at as borrow_updated_at, borrow_book_id from borrow_books left join books on borrow_books.book_id = books.book_id"
            " WHERE user_id = " + QString::number(id) + " and borrow_books.deleted_at is null";
    this->query->prepare(queryText);
    //this->query->bindValue(":id", id);
    this->query->exec();

    while(this->query->next())
    {
        list->add(this->parseBorrowBook(this->query));
    }

    return list;
}

