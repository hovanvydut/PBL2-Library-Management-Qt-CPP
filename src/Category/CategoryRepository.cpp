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
    int offsetId = 0;

    this->query->prepare("SELECT TOP(:limit) categories_id, name, created_at, updated_at, deleted_at "
                         "FROM categories WHERE categories_id > :offsetId");
    this->query->bindValue(":limit", limit);
    this->query->bindValue(":offsetId", offsetId);

    this->query->exec();
    while(this->query->next())
    {
        list->add(this->parse(this->query));
    }

    return list;
}

Listt<Category>* CategoryRepository::findByName(QString byName)
{
    Listt<Category>* list = new LinkedListt<Category>();
    this->query->prepare("SELECT categories_id, name, created_at, updated_at, deleted_at "
                         "FROM dbo.categories "
                         "WHERE deleted_at IS NULL AND UPPER(name) LIKE UPPER('%" + byName + "%')"
                         );
    this->query->exec();
    while(this->query->next())
    {
        list->add(this->parse(this->query));
    }

    return list;
}

bool CategoryRepository::saveCategory(Category category)
{
    if (category.getId() == -1)
    {
        QString name = category.getName();
        QString createdAt = category.getCreatedAt().toString(Qt::ISODate);
        QString updatedAt = category.getUpdatedAt().toString(Qt::ISODate);
        QString deletedAt = "NULL";

        QString queryTxt = "INSERT INTO categories (name, created_at, updated_at, deleted_at) "
                "VALUES ('"
                + name + "', '" + createdAt + "', '" + updatedAt
                + "', " + deletedAt + ")";
        qDebug() << queryTxt;
        this->query->prepare(queryTxt);
        return this->query->exec();
    }
    return false;
}

bool CategoryRepository::updateCategory(Category category)
{
    if (category.getId() >= 0)
    {
        QString id = QString::number(category.getId());
        QString name = category.getName();
        QString createdAt = category.getCreatedAt().toString(Qt::ISODate);
        QString updatedAt = category.getUpdatedAt().toString(Qt::ISODate);
        QString deletedAt = "NULL";
        QString queryTxt = "UPDATE categories SET name = '" + name + "', created_at = '" + createdAt + "', updated_at = '" + updatedAt + "', deleted_at = " + deletedAt + " WHERE categories_id = " + id;
        qDebug() << queryTxt;
        this->query->prepare(queryTxt);
        return this->query->exec();
    }
    else
    {
        return false;
    }
}

bool CategoryRepository::deleteCategoryById(int id)
{
    if (id < 0)
        return false;

    QString queryTxt = "DELETE FROM categories WHERE categories_id = " + QString::number(id);
    qDebug() << queryTxt;
    this->query->prepare(queryTxt);
    return this->query->exec();
}

