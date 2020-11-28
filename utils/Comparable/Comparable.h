#ifndef COMPARABLE_H
#define COMPARABLE_H

template<class T>

class Comparable
{
public:
    virtual bool operator == (const T&) const = 0;
};

#endif // COMPARABLE_H
