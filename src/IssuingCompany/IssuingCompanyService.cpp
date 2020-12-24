#include "IssuingCompanyService.h"

IssuingCompanyService* IssuingCompanyService::_issuingCompanyService = nullptr;

IssuingCompanyService::IssuingCompanyService()
{
    this->_issuingCompanyRepository = IssuingCompanyRepository::initIssuingCompanyRepository();
}

IssuingCompanyService::~IssuingCompanyService()
{

}

IssuingCompanyService* IssuingCompanyService::initIssuingCompanyService()
{
    if (_issuingCompanyService == nullptr)
    {
        _issuingCompanyService = new IssuingCompanyService();
    }

    return _issuingCompanyService;
}

Listt<IssuingCompany>* IssuingCompanyService::findAll()
{
    return this->_issuingCompanyRepository->findAll();
}

Listt<IssuingCompany>* IssuingCompanyService::findByName(QString byName)
{
    return this->_issuingCompanyRepository->findByName(byName);
}

bool IssuingCompanyService::saveIssuingCompany(IssuingCompany issuingCompany)
{
    return this->_issuingCompanyRepository->saveIssuingCompany(issuingCompany);
}

bool IssuingCompanyService::updateIssuingCompany(IssuingCompany issuingCompany)
{
    return this->_issuingCompanyRepository->updateIssuingCompany(issuingCompany);
}

bool IssuingCompanyService::deleteIssuingCompanyById(int id)
{
    return this->_issuingCompanyRepository->deleteIssuingCompanyById(id);
}
