#include "Author.h"

Author::Author()
{

}

Author::Author(int author_id, QString name, QDate created_at, QDate updated_at, QDate deleted_at)
{
    this->author_id = author_id;
    this->name = name;
    this->created_at = created_at;
    this->updated_at = updated_at;
    this->deleted_at = deleted_at;
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

