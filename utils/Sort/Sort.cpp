#include "Sort.h"

template <class T>
Sort<T>::Sort()
{

}

template <class T>
Sort<T>::~Sort()
{

}

template <class T>
bool Sort<T>::compare(T a, T b){
    return a < b;
}

template <class T>
int Sort<T>::partition (Listt<T> *arr, int low, int high, bool func(T, T))
{
    // check if have function compare
    if (func == nullptr){
        func = Sort<T>::compare;
    }

    T pivot = arr->get(high);    // pivot
    int left = low;
    int right = high - 1;
    while(true){
        while(left <= right && func(arr->get(left), pivot)) left++;
        while(right >= left && !func(arr->get(right), pivot)) right--;
        if (left >= right) break;


        T tmp = arr->get(left);
        arr->set(left, arr->get(right));
        arr->set(right, tmp);

        left++;
        right--;
    }

    T tmp = arr->get(left);
    arr->set(left, arr->get(high));
    arr->set(high, tmp);
    return left;
}

template <class T>
void Sort<T>::quickSort(Listt<T> *arr, int left, int right, bool func(T, T))
{
    if (left < right)
    {

        int p = Sort<T>::partition(arr, left, right, func);

        Sort<T>::quickSort(arr, left, p - 1, func);
        Sort<T>::quickSort(arr, p + 1, right, func);
    }
}

template <class T>
void Sort<T>::swap(T& a, T& b){
    T tmp = a;
    a = b;
    b = tmp;

}
