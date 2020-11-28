#include "DatabaseConnection.h"

DatabaseConnection* DatabaseConnection::_instance = nullptr;

DatabaseConnection::DatabaseConnection()
{
    QString connectString = "DRIVER={SQL Server};SERVER=ADMINISTRATOR, 1433;DATABASE=LibraryManagement;Trusted=true;";
    this->conn = QSqlDatabase::addDatabase("QODBC");
    this->conn.setDatabaseName(connectString);
    this->conn.open();
    this->query = new QSqlQuery(this->conn);
}

DatabaseConnection::~DatabaseConnection()
{
    this->conn.close();
    delete this->query;
}

DatabaseConnection* DatabaseConnection::initDatabaseConnection() {
    if(_instance == nullptr) {
        _instance = new DatabaseConnection();
    }
    return _instance;
}

QSqlQuery* DatabaseConnection::getQuery() {
    return this->query;
}



