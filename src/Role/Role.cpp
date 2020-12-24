#include "Role.h"

Role::Role(int role_id, int priorty, QString code, QString description){
    this->role_id = role_id;
    this->priorty = priorty;
    this->code = code;
    this->description = description;
}
Role::~Role(){}

int Role::getRoleId() const{
    return this->role_id;
}
int Role::getPriorty() const{
    return this->priorty;
}
QString Role::getCode() const{
    return this->code;
}
QString Role::getDescription() const{
    return this->description;
}

void Role::setPriorty(int priorty){
    this->priorty = priorty;
}
void Role::setCode(QString code){
    this->code = code;
}
void Role::setDescription(QString description){
    this->description = description;
}

bool Role::operator == (const Role& role) const{
    return this->role_id == role.getRoleId();
}

