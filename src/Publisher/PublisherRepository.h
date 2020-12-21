#ifndef PUBLISHERREPOSITORY_H
#define PUBLISHERREPOSITORY_H

#include <QSqlQuery>
#include <QVariant>
#include "base/Repository/Repository.h"
#include "src/Publisher/Publisher.h"
#include "utils/ListPackage/LinkedListt/LinkedListt.h"
#include "utils/DatabaseConnection/DatabaseConnection.h"

class PublisherRepository : public Repository<Publisher>
{

private:
    static PublisherRepository* _publisherRepository;
    QSqlQuery* query;
    PublisherRepository();

public:
    static PublisherRepository* initPublisherRepository();
    ~PublisherRepository();
    Publisher parse(QSqlQuery *);
    Listt<Publisher>* findAll();
    Listt<Publisher>* findByName(QString byName);
};

#endif // PUBLISHERREPOSITORY_H
