#ifndef BOOKREPOSITORY_H
#define BOOKREPOSITORY_H

#include <QSqlQuery>
#include <QVariant>
#include "base/Repository/Repository.h"
#include "src/Book/Book.h"
#include "utils/ListPackage/LinkedListt/LinkedListt.h"
#include "utils/DatabaseConnection/DatabaseConnection.h"
#include "src/Author/AuthorRepository.h"

class BookRepository : public Repository<Book>
{

private:
    static BookRepository* _bookRepository;
    QSqlQuery* query;
    BookRepository();

public:
    static BookRepository* initBookRepository();
    ~BookRepository();
    Listt<Book>* findAll();
    Book findById(int id);
    Listt<Book>* findByBookTitle(QString title);
    Listt<Book>* findByBookTitle2(QString title);

    bool updateBook(Book book);
    bool insertBook(Book book);

    Book parse(QSqlQuery *);
    Book parse2(QSqlQuery *);

};

#endif // BOOKREPOSITORY_H
