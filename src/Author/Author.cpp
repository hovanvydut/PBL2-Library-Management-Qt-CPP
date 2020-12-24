#include "Author.h"

Author::Author()
{
    this->books = new LinkedListt<Book>();
}

Author::Author(int author_id, QString name, QDate created_at, QDate updated_at, QDate deleted_at)
{
    this->author_id = author_id;
    this->name = name;
    this->created_at = created_at;
    this->updated_at = updated_at;
    this->deleted_at = deleted_at;
    this->books = new LinkedListt<Book>();
}

Author::Author(int author_id, QString name, QDate created_at, QDate updated_at)
{
    this->author_id = author_id;
    this->name = name;
    this->created_at = created_at;
    this->updated_at = updated_at;
    this->deleted_at = QDate::currentDate();
    this->books = new LinkedListt<Book>();
}

Author::Author(QString name, QDate created_at, QDate updated_at)
{
    this->author_id = -1;
    this->name = name;
    this->created_at = created_at;
    this->updated_at = updated_at;
    this->deleted_at = QDate::currentDate();
    this->books = new LinkedListt<Book>();
}


Author::~Author()
{

}

int Author::getId() const
{
    return this->author_id;
}

QString Author::getName() const
{
    return this->name;
}

void Author::setName(const QString& name)
{
    this->name = name;
}

QDate Author::getCreatedAt() const
{
    return this->created_at;
}

QDate Author::getUpdatedAt() const
{
    return this->updated_at;
}

void Author::setUpdatedAt(const QDate& updated_at)
{
    this->updated_at = updated_at;
}

QDate Author::getDeletedAt() const
{
    return this->deleted_at;
}

bool Author::operator == (const Author& anotherAuthor) const
{
    return (this->getId()) == (anotherAuthor.getId());
}

Listt<Book>* Author::getBooks()
{
    return this->books;
}

bool Author::addBook(const Book& book) const
{
    return this->books->add(book);
}
