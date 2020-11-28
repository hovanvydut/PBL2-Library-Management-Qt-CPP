#include "IssuingCompany.h"

IssuingCompany::IssuingCompany()
{

}

IssuingCompany::~IssuingCompany()
{

}

IssuingCompany::IssuingCompany(int issuing_company_id, QString name, QDate created_at, QDate updated_at, QDate deleted_at)
{
    this->issuing_company_id = issuing_company_id;
    this->name = name;
    this->created_at = created_at;
    this->updated_at = updated_at;
    this->deleted_at = deleted_at;
}

int IssuingCompany::getId() const
{
    return this->issuing_company_id;
}

QString IssuingCompany::getName() const
{
    return this->name;
}

void IssuingCompany::setName(const QString& name)
{
    this->name = name;
}

QDate IssuingCompany::getCreatedAt() const
{
    return this->created_at;
}

QDate IssuingCompany::getUpdatedAt() const
{
    return this->updated_at;
}

void IssuingCompany::setUpdatedAt(const QDate& updated_at)
{
    this->updated_at = updated_at;
}

QDate IssuingCompany::getDeletedAt() const
{
    return this->deleted_at;
}

bool IssuingCompany::operator == (const IssuingCompany& anotherIssuingCompany) const
{
    return (this->getId()) == (anotherIssuingCompany.getId());
}
