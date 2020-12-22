#ifndef AUTHORREPOSITORY_H
#define AUTHORREPOSITORY_H

#include <QSqlQuery>
#include <QVariant>
#include "base/Repository/Repository.h"
#include "utils/ListPackage/Listt/Listt.h"
#include "utils/ListPackage/LinkedListt/LinkedListt.h"
#include "utils/DatabaseConnection/DatabaseConnection.h"
#include "src/Author/Author.h"
#include "src/Book/Book.h"
#include <QDebug>

class AuthorRepository : public Repository<Author>
{

private:
    static AuthorRepository* _authorRepository;
    QSqlQuery* query;
    AuthorRepository();

public:
    static AuthorRepository* initAuthorRepository();
    ~AuthorRepository();
    Author parse(QSqlQuery *);
    Listt<Author>* findAll();
    Listt<Author>* findBooksOfAuthorByAuthorName(QString name);
    Listt<Author>* findAuthorByName(QString byName);
    Book parseBook(QSqlQuery *, int offset);
};

#endif // AUTHORREPOSITORY_H
