#ifndef BOOKREPOSITORY_H
#define BOOKREPOSITORY_H

#include <QSqlQuery>
#include <QVariant>
#include "base/Repository/Repository.h"
#include "src/Book/Book.h"
#include "utils/ListPackage/LinkedListt/LinkedListt.h"
#include "utils/DatabaseConnection/DatabaseConnection.h"

class BookRepository : public Repository<Book>
{

private:
    static BookRepository* _bookRepository;
    QSqlQuery* query;
    BookRepository();

public:
    static BookRepository* initBookRepository();
    ~BookRepository();
    Book parse(QSqlQuery *);
    Listt<Book>* findAll();
};

#endif // BOOKREPOSITORY_H
