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
