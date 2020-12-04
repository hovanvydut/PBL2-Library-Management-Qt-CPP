#ifndef NODELINKEDLISTT_H
#define NODELINKEDLISTT_H

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

template <class E>
class NodeLinkedListt
{
private:
    E data;
    NodeLinkedListt *previous;
    NodeLinkedListt *next;

public:
    NodeLinkedListt(const E);
    ~NodeLinkedListt();
    bool hasNext();
    bool hasPrevious();
    NodeLinkedListt *getNext();
    NodeLinkedListt *getPrevious();
    bool setNextNode(NodeLinkedListt *);
    bool setPreviousNode(NodeLinkedListt *);
    const E getData();
    const E setData(const E);
    //    template <class T> friend std::ostream &operator<<(std::ostream &, const NodeLinkedListt<T> &);
    //    template <class T> friend std::ostream &operator<<(std::ostream &, const NodeLinkedListt<T> *);
};

template <class E>
NodeLinkedListt<E>::NodeLinkedListt(const E data)
{
    this->previous = nullptr;
    this->next = nullptr;
    this->data = data;
}

template <class E>
NodeLinkedListt<E>::~NodeLinkedListt()
{
}

template <class E>
bool NodeLinkedListt<E>::hasNext()
{
    return this->next != nullptr;
}

template <class E>
bool NodeLinkedListt<E>::hasPrevious()
{
    return this->previous != nullptr;
}

template <class E>
NodeLinkedListt<E> *NodeLinkedListt<E>::getNext()
{
    return this->next;
}

template <class E>
NodeLinkedListt<E> *NodeLinkedListt<E>::getPrevious()
{
    return this->previous;
}

template <class E>
bool NodeLinkedListt<E>::setNextNode(NodeLinkedListt *newNode)
{
    this->next = newNode;
    return true;
}

template <class E>
bool NodeLinkedListt<E>::setPreviousNode(NodeLinkedListt *newNode)
{
    NodeLinkedListt *tmp = this->previous;
    this->previous = newNode;
    if (tmp != nullptr)
        delete tmp;
    return true;
}

template <class E>
const E NodeLinkedListt<E>::getData()
{
    return this->data;
}

template <class E>
const E NodeLinkedListt<E>::setData(const E data)
{
    E &before = this->data;
    this->data = data;
    return before;
}

//template <class T>
//std::ostream &operator<<(std::ostream &o, const NodeLinkedListt<T> &nodeLinkedList)
//{
//    o << nodeLinkedList.data;
//    return o;
//}

//template <class T>
//std::ostream &operator<<(std::ostream &o, const NodeLinkedListt<T> *nodeLinkedList)
//{
//    o << nodeLinkedList->data;
//    return o;
//}

#endif // NODELINKEDLISTT_H
