#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QSqlDatabase>
#include <QSqlQuery>

class DatabaseConnection
{
private:
    static DatabaseConnection* _instance;
    QSqlDatabase conn;
    QSqlQuery *query;
    DatabaseConnection();

public:
    ~DatabaseConnection();
    static DatabaseConnection* initDatabaseConnection();
    QSqlQuery* getQuery();
};

#endif // DATABASECONNECTION_H
