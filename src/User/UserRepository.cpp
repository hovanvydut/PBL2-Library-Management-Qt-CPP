#include "UserRepository.h"
#include <QDebug>
#include <QSqlError>
#include <QRegExp>
#include "utils/Auth/Password.h"

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
    int role_id = query->value(6).toInt();
    QString username = query->value(7).toString();
    QString password = query->value(8).toString();
    QString address = query->value(9).toString();
    return User(user_id, fullname, birthday, gender, email, phone, username, password, role_id, address);
}

Listt<User>* UserRepository::findAll()
{

    Listt<User>* list = new LinkedListt<User>();


    this->query->prepare("SELECT user_id, fullname, birthday, gender, phone, email, role_id, username, password, address "
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

    QString queryText = "SELECT user_id, fullname, birthday, gender, phone, email, role_id, username, password, address "
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

    QString queryText = "SELECT user_id, fullname, birthday, gender, phone, email, role_id, username, password, address "
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

Listt<BorrowBook>* UserRepository::getBorrowBook(int id)
{
    Listt<BorrowBook>* list = new LinkedListt<BorrowBook>();

    QString queryText = "select books.book_id, title, cover_type, price, total, available, publication_date, size, number_of_pages, issuing_company_id, publisher_id, category_id, books.created_at, books.updated_at, books.deleted_at, borrowed_at, quantity, numberOfDay, deposit_money, borrow_books.updated_at as borrow_updated_at, borrow_book_id from borrow_books left join books on borrow_books.book_id = books.book_id"
            " WHERE user_id = " + QString::number(id) + " and borrow_books.deleted_at is null";
    this->query->prepare(queryText);
    this->query->exec();

    while(this->query->next())
    {
        list->add(this->parseBorrowBook(this->query));
    }

    return list;
}

int UserRepository::returnBook(Listt<int>* listId)
{
    QString queryText;
    for (int i = 0;i < listId->getSize();i++){
        int id = listId->get(i);
        queryText = "UPDATE borrow_books SET deleted_at = GETDATE() WHERE borrow_book_id = :id";
        try{
            this->query->prepare(queryText);
            this->query->bindValue(":id", QString::number(id));
            this->query->exec();
        } catch (...){
            qDebug() << this->query->lastError().text();
            return i;
        }
    }
    return -1;
}

int UserRepository::deleteUsers(Listt<User>* listUser){
    QString queryText;
    for (int i = 0;i < listUser->getSize();i++){
        int id = listUser->get(i).getUserId();
        queryText = "DELETE FROM users WHERE user_id = :id";
        try{
            this->query->prepare("SELECT COUNT(borrow_book_id) AS count_borrow FROM borrow_books WHERE deleted_at IS NULL AND user_id = :id");
            this->query->bindValue(":id", QString::number(id));
            this->query->exec();
            this->query->next();
            if (this->query->value(0).toInt() != 0){
                qDebug() << "Tai khoan nay con no sach";
                return i;
            }
            this->query->prepare(queryText);
            this->query->bindValue(":id", QString::number(id));
            this->query->exec();
        } catch (...){
            qDebug() << "Loi CSDL:" <<  this->query->lastError().text();
            return i;
        }
    }
    return -1;
}

void UserRepository::addUser(const User& user){

    this->validateBeforeInsert(user);

    QString queryText = "INSERT INTO users(role_id, fullname, birthday, gender, email, phone, username, password, address) "
                        "VALUES (:role_id, :fullname, :birthday, :gender, :email, :phone, :username, :password, :address)";
    try{

        //Hash password
        Password pwd(user.getPassword());
        //Query
        this->query->prepare(queryText);
        this->query->bindValue(":role_id", QString::number(user.getRoleId()));
        this->query->bindValue(":fullname", user.getFullname());
        this->query->bindValue(":birthday", user.getBirthday().toString("dd/MM/yyyy"));
        this->query->bindValue(":gender", QString::number(user.getGender()));
        this->query->bindValue(":email", user.getEmail());
        this->query->bindValue(":phone", user.getPhone());
        this->query->bindValue(":username", user.getUsername());
        this->query->bindValue(":password", pwd.hashMd5());
        this->query->bindValue(":address", user.getAddress());
        this->query->exec();
        if (this->query->lastError().isValid()) throw QString::fromUtf8("Lỗi cơ sở dữ liệu");
    } catch(...){
        qDebug() << this->query->lastError().text();
        throw this->query->lastError().text();
    }

}

void UserRepository::validateBeforeInsert(const User& user){
    QRegExp specialChar("[!@#$%^&()_+]");
    QRegExp number("[0-9]");
    QRegExp email("[a-z0-9._%+-]+@[a-z0-9.-]+\\.[a-z]{2,4}");
    QRegExp alpha("[a-zA-z]+");

    // fullname
    if (user.getFullname() == "") throw QString::fromUtf8("Vui lòng nhập họ và tên");
    if (user.getFullname().count(number) != 0 || user.getFullname().count(specialChar)) throw QString::fromUtf8("Họ và tên chỉ được phép chứa chữ cái");
    // phone
    if (user.getPhone() == "") throw QString::fromUtf8("Vui lòng nhập số điện thoại");
    if (!(user.getPhone().length() >= 6 && user.getPhone().length() <= 11)) throw QString::fromUtf8("Số điện thoại không hợp lệ");
    if (user.getPhone().count(number) != user.getPhone().length()) throw QString::fromUtf8("Số điện thoại chỉ chứa chữ số");
    // gender - role
    if (!(user.getGender() >= 0 && user.getGender() <= 2)) throw QString::fromUtf8("Giới tính không hợp lệ");
    if (!(user.getRoleId() >= 1 && user.getGender() <= 4)) throw QString::fromUtf8("Quyền không hợp lệ");
    // email
    if (user.getEmail() != ""){
        if (!email.exactMatch(user.getEmail())) throw QString::fromUtf8("Email không hợp lệ");
    }
    // usr + pwd
    if (user.getRoleId() != 4){
        if (user.getUsername().length() < 5) throw QString::fromUtf8("Tên đăng nhập phải từ 5 kí tự");
        if (user.getPassword().length() < 10) throw QString::fromUtf8("Mật khẩu phải từ 10 kí tự");
    }
    // validate in database
    QString queryText;
    // check if phone exist
    queryText = "SELECT * FROM users WHERE phone = :phone";
    this->query->prepare(queryText);
    this->query->bindValue(":phone", user.getPhone());
    this->query->exec();
    int count = 0;
    while (this->query->next()) count++;
    if (count != 0) throw QString::fromUtf8("Số điện thoại đã được sử dụng");
    // check if email exist
    if (user.getEmail() != ""){
        count = 0;
        queryText = "SELECT * FROM users WHERE email = :email";
        this->query->prepare(queryText);
        this->query->bindValue(":email", user.getEmail());
        this->query->exec();
        while (this->query->next()) count++;
        if (count != 0) throw QString::fromUtf8("Email đã được sử dụng");
    }
    // check if username exist
    if (user.getRoleId() != 4){
        count = 0;
        queryText = "SELECT * FROM users WHERE username = :username";
        this->query->prepare(queryText);
        this->query->bindValue(":username", user.getUsername());
        this->query->exec();
        while (this->query->next()) count++;
        if (count != 0) throw QString::fromUtf8("Tên tài khoản đã được sử dụng");
    }
}

void UserRepository::validateBeforeUpdate(const User& user){
    QRegExp specialChar("[!@#$%^&()_+]");
    QRegExp number("[0-9]");
    QRegExp email("[a-z0-9._%+-]+@[a-z0-9.-]+\\.[a-z]{2,4}");
    QRegExp alpha("[a-zA-z]+");

    // fullname
    if (user.getFullname() == "") throw QString::fromUtf8("Vui lòng nhập họ và tên");
    if (user.getFullname().count(number) != 0 || user.getFullname().count(specialChar)) throw QString::fromUtf8("Họ và tên chỉ được phép chứa chữ cái");
    // phone
    if (user.getPhone() == "") throw QString::fromUtf8("Vui lòng nhập số điện thoại");
    if (!(user.getPhone().length() >= 6 && user.getPhone().length() <= 11)) throw QString::fromUtf8("Số điện thoại không hợp lệ");
    if (user.getPhone().count(number) != user.getPhone().length()) throw QString::fromUtf8("Số điện thoại chỉ chứa chữ số");
    // gender - role
    if (!(user.getGender() >= 0 && user.getGender() <= 2)) throw QString::fromUtf8("Giới tính không hợp lệ");
    if (!(user.getRoleId() >= 1 && user.getGender() <= 4)) throw QString::fromUtf8("Quyền không hợp lệ");
    // email
    if (user.getEmail() != ""){
        if (!email.exactMatch(user.getEmail())) throw QString::fromUtf8("Email không hợp lệ");
    }
    // usr + pwd
    if (user.getRoleId() != 4){
        if (user.getUsername().length() < 5) throw QString::fromUtf8("Tên đăng nhập phải từ 5 kí tự");
        if (user.getPassword().length() < 10) throw QString::fromUtf8("Mật khẩu phải từ 10 kí tự");
    }
    // validate in database
    QString queryText;
    // check if phone exist
    queryText = "SELECT * FROM users WHERE phone = :phone AND user_id != :user_id";
    this->query->prepare(queryText);
    this->query->bindValue(":phone", user.getPhone());
    this->query->bindValue(":user_id", QString::number(user.getUserId()));
    this->query->exec();
    int count = 0;
    while (this->query->next()) count++;
    if (count != 0) throw QString::fromUtf8("Số điện thoại đã được sử dụng");
    // check if email exist
    if (user.getEmail() != ""){
        count = 0;
        queryText = "SELECT * FROM users WHERE email = :email AND user_id != :user_id";
        this->query->prepare(queryText);
        this->query->bindValue(":email", user.getEmail());
        this->query->bindValue(":user_id", QString::number(user.getUserId()));
        this->query->exec();
        while (this->query->next()) count++;
        if (count != 0) throw QString::fromUtf8("Email đã được sử dụng");
    }
    // check if username exist
    if (user.getRoleId() != 4){
        count = 0;
        queryText = "SELECT * FROM users WHERE username = :username AND user_id != :user_id";
        this->query->prepare(queryText);
        this->query->bindValue(":username", user.getUsername());
        this->query->bindValue(":user_id", QString::number(user.getUserId()));
        this->query->exec();
        while (this->query->next()) count++;
        if (count != 0) throw QString::fromUtf8("Tên tài khoản đã được sử dụng");
    }
}

void UserRepository::updateUser(const User& user){
    this->validateBeforeUpdate(user);

    QString queryText = "UPDATE users "
                        "SET role_id = :role_id, fullname = :fullname, birthday = :birthday, gender = :gender, email = :email, phone = :phone, username = :username, address = :address";

    // check if have new password
    if (user.getPassword() != "defaultPassword"){
        queryText += ", password = :password";
    }
    queryText += " WHERE user_id = :user_id";
    try{
        this->query->prepare(queryText);
        this->query->bindValue(":role_id", QString::number(user.getRoleId()));
        this->query->bindValue(":fullname", user.getFullname());
        this->query->bindValue(":birthday", user.getBirthday().toString("dd/MM/yyyy"));
        this->query->bindValue(":gender", QString::number(user.getGender()));
        this->query->bindValue(":email", user.getEmail());
        this->query->bindValue(":phone", user.getPhone());
        this->query->bindValue(":username", user.getUsername());
        if (user.getPassword() != "defaultPassword"){
            Password pwd(user.getPassword());
            this->query->bindValue(":password", pwd.hashMd5());
        }
        this->query->bindValue(":address", user.getAddress());
        this->query->bindValue(":user_id", user.getUserId());
        this->query->exec();
        if (this->query->lastError().isValid()) throw QString::fromUtf8("Lỗi cơ sở dữ liệu");
    } catch(...){
        qDebug() << this->query->lastError().text();
        throw this->query->lastError().text();
    }
}
