#ifndef PUBLISHERREPOSITORY_H
#define PUBLISHERREPOSITORY_H

#include <QSqlQuery>
#include <QVariant>
#include "base/Repository/Repository.h"
#include "src/Publisher/Publisher.h"
#include "utils/ListPackage/Listt/Listt.h"
#include "utils/ListPackage/LinkedListt/LinkedListt.h"
#include "utils/DatabaseConnection/DatabaseConnection.h"

class PublisherRepository : Repository<Publisher>
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
};

#endif // PUBLISHERREPOSITORY_H