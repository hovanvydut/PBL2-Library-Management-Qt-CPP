#ifndef USER_H
#define USER_H
#include <QDate>
#include <QString>
#pragma once
#include "utils/Comparable/Comparable.h"
#include "src/BorrowBook/BorrowBook.h"
#include "src/Role/Role.h"

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
    Role role;
    QString address;
    QDate created_at;
    QDate updated_at;
    Listt<BorrowBook> *borrowList;
public:

    User();
    User(int, QString, QDate, int, QString, QString, QString, QString, Role, QString, QDate, QDate);
    User(int, QString, QDate, int, QString, QString, QString, QString, Role, QString);
    User(int, QString, QDate, int, QString, QString);
    User(int, QString);
    ~User();
    // getter - setter
    int getUserId() const;
    void setUserId(int);
    QString getFullname() const;
    void setFullName(QString);
    QDate getBirthday() const;
    void setBirthday(QDate);
    int getGender() const;
    void setGender(int);
    QString getEmail() const;
    void setEmail(QString);
    QString getPhone() const;
    void setPhone(QString);
    QString getUsername() const;
    void setUsername(QString);
    QString getPassword() const;
    void setPassword(QString);
    Role getRole() const;
    void setRole(Role);
    QString getAddress() const;
    void setAddress(QString);
    QDate getCreatedAt() const;
    void setCreatedAt(QDate);
    QDate getUpdatedAt() const;
    void setUpdatedAt(QDate);
    Listt<BorrowBook> *getBorrowList();
    void setBorrowBook(Listt<BorrowBook> *);
    //
    bool operator == (const User&) const;
    bool operator < (const User&) const;
    User &operator=(const User&);
    friend class MainWindow;
    //
    static bool compareName(User, User);
    static bool compareRole(User, User);
    static bool compareCreateDate(User, User);

};

#endif // USER_H
