#include "RoleService.h"

RoleService* RoleService::_roleService = nullptr;

RoleService::RoleService()
{
    this->_roleRepository = RoleRepository::initRoleRepository();
}

RoleService::~RoleService()
{

}

RoleService* RoleService::initRoleService()
{
    if (_roleService == nullptr)
    {
        _roleService = new RoleService();
    }

    return _roleService;
}

Listt<Role>* RoleService::findAll(){
    return this->_roleRepository->findAll();
}

void RoleService::addNew(const Role& role){
    this->_roleRepository->addNew(role);
}

void RoleService::deleteRole(int id){
    this->_roleRepository->deleteRole(id);
}

