#ifndef USER_H
#define USER_H
#include <QDate>
#include <QString>
#include "utils/Comparable/Comparable.h"
#include "src/BorrowBook/BorrowBook.h"

class MainWindow;

class User: public Comparable<User>
{
    int user_id;
    QString fullname;
    QDate birthday;
    int gender;
    QString email;
    QString phone;
    QString username;
    QString password;
    int role_id;
    QString address;
    QDate created_at;
    QDate updated_at;
    Listt<BorrowBook> *borrowList;
public:

    User();
    User(int, QString, QDate, int, QString, QString, QString, QString, int, QString, QDate, QDate);
    User(int, QString, QDate, int, QString, QString);
    User(int, QString);
    ~User();
    // getter - setter
    int getUserId();
    void setUserId(int);
    QString getFullname();
    void setFullName(QString);
    QDate getBirthday();
    void setBirthday(QDate);
    int getGender();
    void setGender(int);
    QString getEmail();
    void setEmail(QString);
    QString getPhone();
    void setPhone(QString);
    QString getUsername();
    void setUsername(QString);
    QString getPassword();
    void setPassword(QString);
    int getRoleId();
    void setRoleId(int);
    QString getAddress();
    void setAddress(QString);
    QDate getCreatedAt();
    void setCreatedAt(QDate);
    QDate getUpdatedAt();
    void setUpdatedAt(QDate);
    Listt<BorrowBook> *getBorrowList();
    void setBorrowBook(Listt<BorrowBook> *);
    //
    bool operator == (const User&) const;
    friend class MainWindow;

};

#endif // USER_H
