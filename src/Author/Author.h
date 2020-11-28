#ifndef AUTHOR_H
#define AUTHOR_H

#include <QString>
#include <QDate>
#include <utils/Comparable/Comparable.h>

class Author : public Comparable<Author>
{

private:
    int author_id;
    QString name;
    QDate created_at;
    QDate updated_at;
    QDate deleted_at;

public:
    Author();
    Author(int, QString, QDate, QDate, QDate);
    ~Author();

    int getId() const;

    QString getName() const;
    void setName(const QString&);

    QDate getCreatedAt() const;

    QDate getUpdatedAt() const;
    void setUpdatedAt(const QDate&);

    QDate getDeletedAt() const;

    bool operator == (const Author&) const;

};

#endif // AUTHOR_H
