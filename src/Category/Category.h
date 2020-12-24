#ifndef CATEGORY_H
#define CATEGORY_H

#include <QString>
#include <QDate>
#include <utils/Comparable/Comparable.h>

class Category : public Comparable<Category>
{

private:
    int categories_id = -1;
    QString name;
    QDate created_at;
    QDate updated_at;
    QDate deleted_at;

public:
    Category();
    Category(int, QString, QDate, QDate, QDate);
    Category(int, QString, QDate, QDate);
    Category(QString, QDate, QDate);
    Category(const Category& category);
    ~Category();

    int getId() const;

    QString getName() const;
    void setName(const QString&);

    QDate getCreatedAt() const;

    QDate getUpdatedAt() const;
    void setUpdatedAt(const QDate&);

    QDate getDeletedAt() const;

    bool operator == (const Category&) const;
};

#endif // CATEGORY_H
