#include "IssuingCompanyRepository.h"

IssuingCompanyRepository* IssuingCompanyRepository::_issuingCompanyRepository = nullptr;

IssuingCompanyRepository::IssuingCompanyRepository()
{
    this->query = DatabaseConnection::initDatabaseConnection()->getQuery();
}

IssuingCompanyRepository::~IssuingCompanyRepository()
{

}

IssuingCompanyRepository* IssuingCompanyRepository::initIssuingCompanyRepository()
{
    if (_issuingCompanyRepository == nullptr)
    {
        _issuingCompanyRepository = new IssuingCompanyRepository();
    }

    return _issuingCompanyRepository;
}

IssuingCompany IssuingCompanyRepository::parse(QSqlQuery *)
{
    int id = query->value(0).toInt();
    QString name = query->value(1).toString();
    QDate created_at = query->value(2).toDate();
    QDate updated_at = query->value(3).toDate();
    QDate deleted_at = query->value(4).toDate();
    return IssuingCompany(id, name, created_at, updated_at, deleted_at);
}

Listt<IssuingCompany>* IssuingCompanyRepository::findAll()
{
    Listt<IssuingCompany>* list = new LinkedListt<IssuingCompany>();

    // default query conditions
    int limit = 7;
    int offsetId = 5;

    this->query->prepare("SELECT TOP(:limit) issuing_company_id, name, created_at, updated_at, deleted_at "
                         "FROM issuing_company WHERE issuing_company_id > :offsetId");
    this->query->bindValue(":limit", limit);
    this->query->bindValue(":offsetId", offsetId);

    this->query->exec();
    while(this->query->next())
    {
        list->add(this->parse(this->query));
    }

    return list;
}

