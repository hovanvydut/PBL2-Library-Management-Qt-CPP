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

Listt<IssuingCompany>* IssuingCompanyRepository::findByName(QString byName)
{
    Listt<IssuingCompany>* list = new LinkedListt<IssuingCompany>();
    this->query->prepare("SELECT issuing_company_id, name, created_at, updated_at, deleted_at "
                         "FROM dbo.issuing_company "
                         "WHERE deleted_at IS NULL AND UPPER(name) LIKE UPPER('%" + byName + "%')"
                         );
    this->query->exec();
    while(this->query->next())
    {
        list->add(this->parse(this->query));
    }

    return list;
}

bool IssuingCompanyRepository::saveIssuingCompany(IssuingCompany issuingCompany)
{
    if (issuingCompany.getId() == -1)
    {
        QString name = issuingCompany.getName();
        QString createdAt = issuingCompany.getCreatedAt().toString(Qt::ISODate);
        QString updatedAt = issuingCompany.getUpdatedAt().toString(Qt::ISODate);
        QString deletedAt = "NULL";

        QString queryTxt = "INSERT INTO issuing_company (name, created_at, updated_at, deleted_at) "
                "VALUES ('"
                + name + "', '" + createdAt + "', '" + updatedAt
                + "', " + deletedAt + ")";
        qDebug() << queryTxt;
        this->query->prepare(queryTxt);
        return this->query->exec();
    }
    return false;
}

bool IssuingCompanyRepository::updateIssuingCompany(IssuingCompany issuingCompany)
{
    if (issuingCompany.getId() >= 0)
    {
        QString id = QString::number(issuingCompany.getId());
        QString name = issuingCompany.getName();
        QString createdAt = issuingCompany.getCreatedAt().toString(Qt::ISODate);
        QString updatedAt = issuingCompany.getUpdatedAt().toString(Qt::ISODate);
        QString deletedAt = "NULL";
        QString queryTxt = "UPDATE issuing_company SET name = '" + name + "', created_at = '" + createdAt + "', updated_at = '" + updatedAt + "', deleted_at = " + deletedAt + " WHERE issuing_company_id = " + id;
        qDebug() << queryTxt;
        this->query->prepare(queryTxt);
        return this->query->exec();
    }
    else
    {
        return false;
    }
}

bool IssuingCompanyRepository::deleteIssuingCompanyById(int id)
{
    if (id < 0)
        return false;

    QString queryTxt = "DELETE FROM issuing_company WHERE issuing_company_id = " + QString::number(id);
    qDebug() << queryTxt;
    this->query->prepare(queryTxt);
    return this->query->exec();
}

