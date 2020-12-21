#include "Publisher.h"

Publisher::Publisher()
{
    this->publisher_id = -1;
}

Publisher::Publisher(int publisher_id, QString name, QDate created_at, QDate updated_at, QDate deleted_at)
{
    this->publisher_id = publisher_id;
    this->name = name;
    this->created_at = created_at;
    this->updated_at = updated_at;
    this->deleted_at = deleted_at;
}

Publisher::Publisher(const Publisher& publisher)
{
    this->publisher_id = publisher.getId();
    this->name = publisher.getName();
    this->created_at = publisher.getCreatedAt();
    this->updated_at = publisher.getUpdatedAt();
    this->deleted_at = publisher.getDeletedAt();
}

Publisher::~Publisher()
{

}

int Publisher::getId() const
{
    return this->publisher_id;
}

QString Publisher::getName() const
{
    return this->name;
}

void Publisher::setName(const QString& name)
{
    this->name = name;
}

QDate Publisher::getCreatedAt() const
{
    return this->created_at;
}

QDate Publisher::getUpdatedAt() const
{
    return this->updated_at;
}

void Publisher::setUpdatedAt(const QDate& updated_at)
{
    this->updated_at = updated_at;
}

QDate Publisher::getDeletedAt() const
{
    return this->deleted_at;
}

bool Publisher::operator == (const Publisher& anotherPublisher) const
{
    return (this->getId()) == (anotherPublisher.getId());
}

