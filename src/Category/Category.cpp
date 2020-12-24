#include "Category.h"

Category::Category()
{

}

Category::Category(int categories_id, QString name, QDate created_at, QDate updated_at, QDate deleted_at)
{
    this->categories_id = categories_id;
    this->name = name;
    this->created_at = created_at;
    this->updated_at = updated_at;
    this->deleted_at = deleted_at;
}

Category::Category(int categories_id, QString name, QDate created_at, QDate updated_at)
{
    this->categories_id = categories_id;
    this->name = name;
    this->created_at = created_at;
    this->updated_at = updated_at;
    this->deleted_at = QDate::currentDate();
}

Category::Category(QString name, QDate created_at, QDate updated_at)
{
    this->categories_id = -1;
    this->name = name;
    this->created_at = created_at;
    this->updated_at = updated_at;
    this->deleted_at = QDate::currentDate();
}

Category::Category(const Category& category)
{
    this->categories_id = category.getId();
    this->name = category.getName();
    this->created_at = category.getCreatedAt();
    this->updated_at = category.getUpdatedAt();
    this->deleted_at = category.getDeletedAt();
}

Category::~Category()
{

}

int Category::getId() const
{
    return this->categories_id;
}

QString Category::getName() const
{
    return this->name;
}

void Category::setName(const QString& name)
{
    this->name = name;
}

QDate Category::getCreatedAt() const
{
    return this->created_at;
}

QDate Category::getUpdatedAt() const
{
    return this->updated_at;
}

void Category::setUpdatedAt(const QDate& updated_at)
{
    this->updated_at = updated_at;
}

QDate Category::getDeletedAt() const
{
    return this->deleted_at;
}

bool Category::operator == (const Category& anotherCategory) const
{
    return (this->getId()) == (anotherCategory.getId());
}

