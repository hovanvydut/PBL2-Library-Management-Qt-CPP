#ifndef ISSUINGCOMPANYREPOSITORY_H
#define ISSUINGCOMPANYREPOSITORY_H

#include <QSqlQuery>
#include "base/Repository/Repository.h"
#include "src/IssuingCompany/IssuingCompany.h"
#include "utils/ListPackage/LinkedListt/LinkedListt.h"
#include "utils/DatabaseConnection/DatabaseConnection.h"

class IssuingCompanyRepository : public Repository<IssuingCompany>
{

private:
    static IssuingCompanyRepository* _issuingCompanyRepository;
    QSqlQuery* query;
    IssuingCompanyRepository();

public:
    static IssuingCompanyRepository* initIssuingCompanyRepository();
    ~IssuingCompanyRepository();
    IssuingCompany parse(QSqlQuery *);
    Listt<IssuingCompany>* findAll();
    Listt<IssuingCompany>* findByName(QString byName);
    bool saveIssuingCompany(IssuingCompany issuingCompany);
    bool updateIssuingCompany(IssuingCompany issuingCompany);
    bool deleteIssuingCompanyById(int id);
};

#endif // ISSUINGCOMPANYREPOSITORY_H
