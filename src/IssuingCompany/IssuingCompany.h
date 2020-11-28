#ifndef ISSUINGCOMPANY_H
#define ISSUINGCOMPANY_H

#include <QString>
#include <QDate>
#include "utils/Comparable/Comparable.h"

class IssuingCompany : public Comparable<IssuingCompany>
{

private:
    int issuing_company_id;
    QString name;
    QDate created_at;
    QDate updated_at;
    QDate deleted_at;

public:
    IssuingCompany();
    IssuingCompany(int, QString, QDate, QDate, QDate);
    ~IssuingCompany();

    int getId() const;

    QString getName() const;
    void setName(const QString&);

    QDate getCreatedAt() const;

    QDate getUpdatedAt() const;
    void setUpdatedAt(const QDate&);

    QDate getDeletedAt() const;

    bool operator == (const IssuingCompany&) const;

};

#endif // ISSUINGCOMPANY_H
