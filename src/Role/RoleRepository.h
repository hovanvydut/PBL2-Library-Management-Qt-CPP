#ifndef ROLEREPOSITORY_H
#define ROLEREPOSITORY_H
#include "src/Role/Role.h"
#include <QSqlQuery>
#include "utils/ListPackage/Listt/Listt.h"
#include "utils/ListPackage/LinkedListt/LinkedListt.h"

class RoleRepository
{
private:
    static RoleRepository* _roleRepository;
    QSqlQuery* query;
    RoleRepository();

public:
    static RoleRepository* initRoleRepository();
    ~RoleRepository();
    Role parse(QSqlQuery *);
    Listt<Role>* findAll();
    void addNew(const Role&);
    void deleteRole(int id);
};

#endif // ROLEREPOSITORY_H
