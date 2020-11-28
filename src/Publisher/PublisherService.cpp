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

