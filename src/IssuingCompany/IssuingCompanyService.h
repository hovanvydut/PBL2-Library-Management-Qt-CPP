#ifndef ISSUINGCOMPANYSERVICE_H
#define ISSUINGCOMPANYSERVICE_H

#include "src/IssuingCompany/IssuingCompanyRepository.h"
#include "utils/ListPackage/LinkedListt/LinkedListt.h"

class IssuingCompanyService
{

private:
    static IssuingCompanyService* _issuingCompanyService;
    IssuingCompanyRepository* _issuingCompanyRepository;
    IssuingCompanyService();

public:
    static IssuingCompanyService* initIssuingCompanyService();
    ~IssuingCompanyService();
    Listt<IssuingCompany>* findAll();

};

#endif // ISSUINGCOMPANYSERVICE_H
