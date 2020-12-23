#include "PublisherRepository.h"

PublisherRepository* PublisherRepository::_publisherRepository = nullptr;

PublisherRepository::PublisherRepository()
{
    this->query = DatabaseConnection::initDatabaseConnection()->getQuery();
}

PublisherRepository::~PublisherRepository()
{

}

PublisherRepository* PublisherRepository::initPublisherRepository()
{
    if (_publisherRepository == nullptr)
    {
        _publisherRepository = new PublisherRepository();
    }

    return _publisherRepository;
}

Publisher PublisherRepository::parse(QSqlQuery *)
{
    int id = query->value(0).toInt();
    QString name = query->value(1).toString();
    QDate created_at = query->value(2).toDate();
    QDate updated_at = query->value(3).toDate();
    QDate deleted_at = query->value(4).toDate();
    return Publisher(id, name, created_at, updated_at, deleted_at);
}

Listt<Publisher>* PublisherRepository::findAll()
{
    Listt<Publisher>* list = new LinkedListt<Publisher>();

    // default query conditions
    int limit = 100;
    int offsetId = 0;

    this->query->prepare("SELECT TOP(:limit) publisher_id, name, created_at, updated_at, deleted_at "
                         "FROM publishers WHERE publisher_id > :offsetId");
    this->query->bindValue(":limit", limit);
    this->query->bindValue(":offsetId", offsetId);

    this->query->exec();
    while(this->query->next())
    {
        list->add(this->parse(this->query));
    }

    return list;
}

Listt<Publisher>* PublisherRepository::findByName(QString byName)
{
    Listt<Publisher>* list = new LinkedListt<Publisher>();
    this->query->prepare("SELECT publisher_id, name, created_at, updated_at, deleted_at "
                         "FROM dbo.publishers "
                         "WHERE deleted_at IS NULL AND UPPER(name) LIKE UPPER('%" + byName + "%')"
                         );
    this->query->exec();
    while(this->query->next())
    {
        list->add(this->parse(this->query));
    }

    return list;
}

bool PublisherRepository::savePublisher(Publisher publisher)
{
    if (publisher.getId() == -1)
    {
        QString name = publisher.getName();
        QString createdAt = publisher.getCreatedAt().toString(Qt::ISODate);
        QString updatedAt = publisher.getUpdatedAt().toString(Qt::ISODate);
        QString deletedAt = "NULL";

        QString queryTxt = "INSERT INTO publishers (name, created_at, updated_at, deleted_at) "
                "VALUES ('"
                + name + "', '" + createdAt + "', '" + updatedAt
                + "', " + deletedAt + ")";
        qDebug() << queryTxt;
        this->query->prepare(queryTxt);
        return this->query->exec();
    }
    return false;
}

bool PublisherRepository::deletePublisherById(int id)
{
    if (id < 0)
        return false;

    QString queryTxt = "DELETE FROM publishers WHERE publisher_id = " + QString::number(id);
    qDebug() << queryTxt;
    this->query->prepare(queryTxt);
    return this->query->exec();
}

