#ifndef AUTHORSERVICE_H
#define AUTHORSERVICE_H

#include "utils/ListPackage/Listt/Listt.h"
#include "src/Author/AuthorRepository.h"
#include "src/Author/Author.h"

class AuthorService
{

private:
    static AuthorService* _authorService;
    AuthorRepository* _authorRepository;
    AuthorService();

public:
    static AuthorService* initAuthorService();
    ~AuthorService();
    Listt<Author>* findAll();
    Listt<Author>* findBooksOfAuthorByAuthorName(QString name);
    Listt<Author>* findAuthorByName(QString byName);
};

#endif // AUTHORSERVICE_H
