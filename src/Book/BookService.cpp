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

