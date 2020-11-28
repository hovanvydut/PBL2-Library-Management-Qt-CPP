#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QSqlQuery>
#include "utils/ListPackage/Listt/Listt.h"

template<class T>
class Repository
{
public:
    Repository();
    virtual ~Repository();
    virtual T parse(QSqlQuery*) = 0;
    virtual Listt<T>* findAll() = 0;
};

template<class T>
Repository<T>::Repository()
{

}

template<class T>
Repository<T>::~Repository()
{

}

#endif // REPOSITORY_H
