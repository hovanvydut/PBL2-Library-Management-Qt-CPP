#include "PublisherService.h"

PublisherService* PublisherService::_publisherService = nullptr;

PublisherService::PublisherService()
{
    this->_publisherRepository = PublisherRepository::initPublisherRepository();
}

PublisherService::~PublisherService()
{

}

PublisherService* PublisherService::initPublisherService()
{
    if (_publisherService == nullptr)
    {
        _publisherService = new PublisherService();
    }

    return _publisherService;
}

Listt<Publisher>* PublisherService::findAll()
{
    return this->_publisherRepository->findAll();
}

Listt<Publisher>* PublisherService::findByName(QString name)
{
    return this->_publisherRepository->findByName(name);
}

bool PublisherService::savePublisher(Publisher publisher)
{
    return this->_publisherRepository->savePublisher(publisher);
}

bool PublisherService::deletePublisherById(int id)
{
    return this->_publisherRepository->deletePublisherById(id);
}
