#ifndef CATEGORYREPOSITORY_H
#define CATEGORYREPOSITORY_H

#include <QSqlQuery>
#include <QVariant>
#include "base/Repository/Repository.h"
#include "src/Category/Category.h"
#include "utils/ListPackage/LinkedListt/LinkedListt.h"
#include "utils/DatabaseConnection/DatabaseConnection.h"

class CategoryRepository : public Repository<Category>
{

private:
    static CategoryRepository* _categoryRepository;
    QSqlQuery* query;
    CategoryRepository();

public:
    static CategoryRepository* initCategoryRepository();
    ~CategoryRepository();
    Category parse(QSqlQuery *);
    Listt<Category>* findAll();
    Listt<Category>* findByName(QString byName);
};

#endif // CATEGORYREPOSITORY_H
