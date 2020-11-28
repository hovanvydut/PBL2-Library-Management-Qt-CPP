#include "AuthorRepository.h"

AuthorRepository* AuthorRepository::_authorRepository = nullptr;

AuthorRepository::AuthorRepository()
{
    this->query = DatabaseConnection::initDatabaseConnection()->getQuery();
}

AuthorRepository::~AuthorRepository()
{

}

AuthorRepository* AuthorRepository::initAuthorRepository()
{
    if (_authorRepository == nullptr)
    {
        _authorRepository = new AuthorRepository();
    }

    return _authorRepository;
}

Author AuthorRepository::parse(QSqlQuery *)
{
    int id = query->value(0).toInt();
    QString name = query->value(1).toString();
    QDate created_at = query->value(2).toDate();
    QDate updated_at = query->value(3).toDate();
    QDate deleted_at = query->value(4).toDate();
    return Author(id, name, created_at, updated_at, deleted_at);
}

Listt<Author>* AuthorRepository::findAll()
{
    Listt<Author>* list = new LinkedListt<Author>();

    // default query conditions
    int limit = 7;
    int offsetId = 5;

    this->query->prepare("SELECT TOP(:limit) author_id, name, created_at, updated_at, deleted_at "
                         "FROM authors WHERE author_id > :offsetId");
    this->query->bindValue(":limit", limit);
    this->query->bindValue(":offsetId", offsetId);

    this->query->exec();
    while(this->query->next())
    {
        list->add(this->parse(this->query));
    }

    return list;
}

