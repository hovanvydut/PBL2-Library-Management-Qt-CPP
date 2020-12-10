#ifndef BOOKSERVICE_H
#define BOOKSERVICE_H

#include "utils/ListPackage/Listt/Listt.h"
#include "src/Book/Book.h"
#include "src/Book/BookRepository.h"

class BookService
{

private:
    static BookService* _bookService;
    BookRepository* _bookRepository;
    BookService();

public:
    static BookService* initBookService();
    ~BookService();
    Listt<Book>* findAll();
    Book findById(int id);
    Listt<Book>* findByBookTitle(QString title);
};

#endif // BOOKSERVICE_H
