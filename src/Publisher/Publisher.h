#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <QString>
#include <QDate>
#include <utils/Comparable/Comparable.h>

class Publisher : public Comparable<Publisher>
{

private:
    int publisher_id = -1;
    QString name;
    QDate created_at;
    QDate updated_at;
    QDate deleted_at;

public:
    Publisher();
    Publisher(int, QString, QDate, QDate, QDate);
    Publisher(int, QString, QDate, QDate);
    Publisher(QString, QDate, QDate);
    Publisher(const Publisher& publisher);

    ~Publisher();

    int getId() const;

    QString getName() const;
    void setName(const QString&);

    QDate getCreatedAt() const;

    QDate getUpdatedAt() const;
    void setUpdatedAt(const QDate&);

    QDate getDeletedAt() const;

    bool operator == (const Publisher&) const;

};

#endif // PUBLISHER_H
