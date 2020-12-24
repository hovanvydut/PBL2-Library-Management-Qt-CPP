#ifndef ISSUINGCOMPANY_H
#define ISSUINGCOMPANY_H

#include <QString>
#include <QDate>
#include "utils/Comparable/Comparable.h"

class IssuingCompany : public Comparable<IssuingCompany>
{

private:
    int issuing_company_id = -1;
    QString name;
    QDate created_at;
    QDate updated_at;
    QDate deleted_at;

public:
    IssuingCompany();
    IssuingCompany(int, QString, QDate, QDate, QDate);
    IssuingCompany(int, QString, QDate, QDate);
    IssuingCompany(QString, QDate, QDate);
    IssuingCompany(const IssuingCompany& issuingCompany);
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
