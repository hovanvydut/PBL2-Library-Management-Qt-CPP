#include "DatabaseConnection.h"
#include <iostream>
DatabaseConnection* DatabaseConnection::_instance = nullptr;

DatabaseConnection::DatabaseConnection()
{
    DotEnv* dotEnv = DotEnv::initDotEnv();
    const QString DB_NAME = QString::fromStdString((*dotEnv)["DB_NAME"]);
    const QString DB_SERVER = QString::fromStdString((*dotEnv)["DB_SERVER"]);
    //QString connectString = "DRIVER={SQL Server};SERVER=" + DB_SERVER + ", 1433;DATABASE=" + DB_NAME + ";Trusted=true;";
    QString connectString = "DRIVER={SQL Server};SERVER=" + DB_SERVER + ";DATABASE=" + DB_NAME + ";Trusted=true;";
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



