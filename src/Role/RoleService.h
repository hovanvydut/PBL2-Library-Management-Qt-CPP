#ifndef ROLESERVICE_H
#define ROLESERVICE_H
#include "src/Role/RoleRepository.h"

class RoleService
{

private:
    static RoleService* _roleService;
    RoleRepository* _roleRepository;
    RoleService();

public:
    static RoleService* initRoleService();
    ~RoleService();
    Listt<Role>* findAll();
    void addNew(const Role&);
    void deleteRole(int id);
};

#endif // ROLESERVICE_H
