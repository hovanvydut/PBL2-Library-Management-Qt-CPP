#ifndef SORT_H
#define SORT_H
#include "utils/ListPackage/Listt/Listt.h"

template <class T>
class Sort{
public:
    Sort();
    ~Sort();
    static bool compare(T, T);
    static int partition (Listt<T>*, int, int, bool func(T, T));
    static void quickSort(Listt<T>*, int, int, bool func(T, T) = nullptr);
    static void swap(T&, T&);

};

#endif // SORT_H
