#ifndef ROLE_H
#define ROLE_H
#include <QString>


class Role
{
    int role_id;
    int priorty;
    QString code;
    QString description;
public:
    Role(int = -1, int = -1, QString = "", QString = "");
    ~Role();

    int getRoleId() const;
    int getPriorty() const;
    QString getCode() const;
    QString getDescription() const;

    void setPriorty(int);
    void setCode(QString);
    void setDescription(QString);
    bool operator == (const Role&) const;
};

#endif // ROLE_H
