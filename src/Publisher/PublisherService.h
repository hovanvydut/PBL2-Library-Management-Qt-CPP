#ifndef PUBLISHERSERVICE_H
#define PUBLISHERSERVICE_H

#include "src/Publisher/PublisherRepository.h"
#include "utils/ListPackage/Listt/Listt.h"
#include "src/Publisher/Publisher.h"

class PublisherService
{

private:
    static PublisherService* _publisherService;
    PublisherRepository* _publisherRepository;
    PublisherService();

public:
    static PublisherService* initPublisherService();
    ~PublisherService();
    Listt<Publisher>* findAll();
    Listt<Publisher>* findByName(QString name);
    bool savePublisher(Publisher publisher);
    bool deletePublisherById(int id);
};

#endif // PUBLISHERSERVICE_H
