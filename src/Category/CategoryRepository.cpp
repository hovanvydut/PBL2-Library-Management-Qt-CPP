#include "CategoryRepository.h"

CategoryRepository* CategoryRepository::_categoryRepository = nullptr;

CategoryRepository::CategoryRepository()
{
    this->query = DatabaseConnection::initDatabaseConnection()->getQuery();
}

CategoryRepository::~CategoryRepository()
{

}

CategoryRepository* CategoryRepository::initCategoryRepository()
{
    if (_categoryRepository == nullptr)
    {
        _categoryRepository = new CategoryRepository();
    }

    return _categoryRepository;
}

Category CategoryRepository::parse(QSqlQuery *)
{
    int id = query->value(0).toInt();
    QString name = query->value(1).toString();
    QDate created_at = query->value(2).toDate();
    QDate updated_at = query->value(3).toDate();
    QDate deleted_at = query->value(4).toDate();
    return Category(id, name, created_at, updated_at, deleted_at);
}

Listt<Category>* CategoryRepository::findAll()
{
    Listt<Category>* list = new LinkedListt<Category>();

    // default query conditions
    int limit = 7;
    int offsetId = 5;

    this->query->prepare("SELECT TOP(:limit) categories_id, name, created_at, updated_at, deleted_at "
                         "FROM categories WHERE publisher_id > :offsetId");
    this->query->bindValue(":limit", limit);
    this->query->bindValue(":offsetId", offsetId);

    this->query->exec();
    while(this->query->next())
    {
        list->add(this->parse(this->query));
    }

    return list;
}

