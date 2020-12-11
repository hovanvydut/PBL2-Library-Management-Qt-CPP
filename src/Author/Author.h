#ifndef AUTHOR_H
#define AUTHOR_H

#include <QString>
#include <QDate>
#include <utils/Comparable/Comparable.h>
#include <src/Book/Book.h>
#include "utils/ListPackage/LinkedListt/LinkedListt.h"

class Author : public Comparable<Author>
{

private:
    int author_id;
    QString name;
    QDate created_at;
    QDate updated_at;
    QDate deleted_at;
    Listt<Book>* books;
public:
    Author();
    Author(int, QString, QDate, QDate, QDate);
    ~Author();

    int getId() const;

    QString getName() const;
    void setName(const QString&);

    QDate getCreatedAt() const;

    QDate getUpdatedAt() const;
    void setUpdatedAt(const QDate&);

    QDate getDeletedAt() const;

    Listt<Book>* getBooks();
    bool addBook(const Book& book) const;

    bool operator == (const Author&) const;

};

#endif // AUTHOR_H
