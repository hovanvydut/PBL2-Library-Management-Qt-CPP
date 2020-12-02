#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include <QDate>
#include <utils/Comparable/Comparable.h>
#include "src/Author/Author.h"
#include "src/Book/Book.h"
#include "src/Category/Category.h"
#include "src/IssuingCompany/IssuingCompany.h"
#include "src/Publisher/Publisher.h"
#include "utils/ListPackage/ArrayListt/ArrayListt.h"

class Book : public Comparable<Book>
{

private:
    int book_id;
    QString title;
    QString cover_type;
    float price;
    int total;
    int available;
    QDate publication_date;
    QString size;
    int number_of_pages;
    QDate created_at;
    QDate updated_at;
    QDate deleted_at;
    Category category;
    IssuingCompany issuingCompany;
    Publisher publisher;
    Listt<Author> *authors;

public:
    Book();
    ~Book();

//    int getId();

//    QString getTitle();
//    void setTitle(const QString&);

//    QString getCoverType();
//    QString setCoverType(const QString&);

//    float getPrice();
//    float setPrice(const float&);

//    int getTotal();
//    int setTotal(const int&);

//    int getAvailable();
//    int setAvailable(const int&);

//    QDate getPublicationDate();
//    QDate setPublicationDate(const QDate&);

//    QString getSize();
//    QString setSize(const QString&);

//    int getNumberOfPages();
//    int setNumberOfPages(const int&);

//    QDate getCreatedAt() const;

//    QDate getUpdatedAt() const;
//    void setUpdatedAt(const QDate&);

//    QDate getDeletedAt() const;

//    Category getCategory();
//    Category setCategory(const Category&);

//    IssuingCompany getIssuingCompany();
//    IssuingCompany setIssuingCompany(const IssuingCompany&);

//    Publisher getPublisher();
//    Publisher setPublisher(const Publisher&);

//    Listt<Author> getAuthors();
//    bool addAuthor(const Author&);

//    bool operator == (const Publisher&) const;
};

#endif // BOOK_H
