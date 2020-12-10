#include "AuthorService.h"

AuthorService* AuthorService::_authorService = nullptr;

AuthorService::AuthorService()
{
    this->_authorRepository = AuthorRepository::initAuthorRepository();
}

AuthorService::~AuthorService()
{

}

AuthorService* AuthorService::initAuthorService()
{
    if (_authorService == nullptr)
    {
        _authorService = new AuthorService();
    }

    return _authorService;
}

Listt<Author>* AuthorService::findAll()
{
    return this->_authorRepository->findAll();
}

Listt<Author>* AuthorService::findBooksOfAuthorByAuthorName(QString name)
{
    qDebug() << "AuthorService";
    return this->_authorRepository->findBooksOfAuthorByAuthorName(name);
}


