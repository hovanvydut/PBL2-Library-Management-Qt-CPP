#include "RoleRepository.h"
#include "utils/DatabaseConnection/DatabaseConnection.h"
#include <QSqlError>
#include <QDebug>

RoleRepository* RoleRepository::_roleRepository = nullptr;

RoleRepository::RoleRepository()
{
    this->query = DatabaseConnection::initDatabaseConnection()->getQuery();
}

RoleRepository::~RoleRepository()
{

}

RoleRepository* RoleRepository::initRoleRepository()
{
    if (_roleRepository == nullptr)
    {
        _roleRepository = new RoleRepository();
    }

    return _roleRepository;
}

Role RoleRepository::parse(QSqlQuery *query){
    int id = query->value(0).toInt();
    QString code = query->value(1).toString();
    int priorty = query->value(2).toInt();
    QString des = query->value(3).toString();
    return Role(id, priorty, code, des);
}

Listt<Role>* RoleRepository::findAll(){
    QString queryText = "SELECT role_id, code, priorty, description FROM roles";
    this->query->prepare(queryText);
    this->query->exec();
    Listt<Role> *list = new LinkedListt<Role>();
    while (this->query->next()){
        list->add(this->parse(this->query));
    }
    return list;
}

void RoleRepository::addNew(const Role& role){
    QString queryText = "INSERT INTO roles(code, priorty, description) VALUES (:code, :priorty, :description)";
    try{
        this->query->prepare(queryText);
        this->query->bindValue(":code", role.getCode());
        this->query->bindValue(":priorty", QString::number(role.getPriorty()));
        this->query->bindValue(":description", role.getDescription());
        this->query->exec();
        if (this->query->lastError().isValid()){
            throw this->query->lastError().text();
        }
    } catch (...){
        throw QString::fromUtf8("Lỗi không xác định");
    }
}

void RoleRepository::deleteRole(int id){
    QString queryText;
    queryText = "DELETE FROM roles WHERE role_id = :id";
    try{
        this->query->prepare(queryText);
        this->query->bindValue(":id", QString::number(id));
        this->query->exec();
        if (this->query->lastError().isValid()) throw this->query->lastError().text();
    } catch (...){
        throw QString::fromUtf8("Lỗi cơ sở dữ liệu");
    }

}
