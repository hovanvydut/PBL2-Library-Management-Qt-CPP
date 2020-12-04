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
    int issuing_company_id;
    int publisher_id;
    int category_id;
    QDate created_at;
    QDate updated_at;
    QDate deleted_at;
    Category* category;
    IssuingCompany* issuingCompany;
    Publisher* publisher;
    Listt<Author*>* authors;

public:
    Book();
    Book(int, QString, QString, float, int, int, QDate, QString, int, int, int, int, QDate, QDate, QDate);
    ~Book();

    int getId() const;

    QString getTitle() const;
    void setTitle(const QString);

    QString getCoverType() const;
    QString setCoverType(const QString);

    float getPrice() const;
    float setPrice(const float);

    int getTotal() const;
    int setTotal(const int);

    int getAvailable() const;
    int setAvailable(const int);

    QDate getPublicationDate();
    QDate setPublicationDate(const QDate);

    QString getSize() const;
    QString setSize(const QString);

    int getNumberOfPages();
    int setNumberOfPages(const int);

    QDate getCreatedAt() const;

    QDate getUpdatedAt() const;
    void setUpdatedAt(const QDate);

    QDate getDeletedAt() const;

    Category* getCategory();
    Category* setCategory(Category*);

    IssuingCompany* getIssuingCompany();
    IssuingCompany* setIssuingCompany(IssuingCompany*);

    Publisher* getPublisher();
    Publisher* setPublisher(Publisher*);

    // get author By id, bla bla
//    Listt<Author*>* getAuthors();
    bool addAuthor(Author*);

    bool operator == (const Book&) const;
};

#endif // BOOK_H