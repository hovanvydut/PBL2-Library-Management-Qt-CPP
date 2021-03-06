#include "BookService.h"

BookService* BookService::_bookService = nullptr;

BookService::BookService()
{
    this->_bookRepository = BookRepository::initBookRepository();
}

BookService::~BookService()
{

}

BookService* BookService::initBookService()
{
    if (_bookService == nullptr)
    {
        _bookService = new BookService();
    }

    return _bookService;
}

Listt<Book>* BookService::findAll()
{
    return this->_bookRepository->findAll();
}

Book BookService::findById(int id)
{
    return this->_bookRepository->findById(id);
}

Listt<Book>* BookService::findByBookTitle(QString title)
{
    return this->_bookRepository->findByBookTitle(title);
}

Listt<Book>* BookService::findByBookTitle2(QString title)
{
    return this->_bookRepository->findByBookTitle2(title);
}

bool BookService::updateBook(Book book)
{
    return this->_bookRepository->updateBook(book);
}

bool BookService::insertBook(Book book)
{
    return this->_bookRepository->insertBook(book);
}

bool BookService::deleteBookById(int id)
{
    return this->_bookRepository->deleteBookById(id);
}
