#ifndef LINKEDLISTT_H
#define LINKEDLISTT_H


#ifndef Listt_h
#define Listt_h
#include "utils/ListPackage/Listt/Listt.h"
#endif
#include "utils/ListPackage/NodeLinkedListt/NodeLinkedListt.h"
#include <QDebug>

template <class E>
class LinkedListt : public Listt<E>
{
private:
  NodeLinkedListt<E> *data;
  int size;

public:
  LinkedListt();
  ~LinkedListt();
  virtual int indexOf(const E);
  virtual int lastIndexOf(const E);
  virtual bool add(const E);
  virtual bool add(const int &, const E);
  virtual bool addFirst(const E);
  virtual bool removeAt(const int &);
  virtual bool remove(const E);
  virtual int getSize();
  virtual bool isEmpty();
  virtual void clear();
  virtual bool contains(const E);
  virtual E get(const int &);
  virtual const E set(const int &, const E);
  virtual void show();
  virtual void sort(bool (*compare)(const E, const E));
  static bool compareASC(const E, const E);
  static bool compareDESC(const E, const E);
  NodeLinkedListt<E> *listIterator();
};

template <class E>
LinkedListt<E>::LinkedListt()
{
  this->data = nullptr;
  this->size = 0;
}

template <class E>
LinkedListt<E>::~LinkedListt()
{
  delete this->data;
}

template <class E>
int LinkedListt<E>::indexOf(const E elm)
{
  int idx = -1;
  NodeLinkedListt<E> *it = this->listIterator();

  while (it != nullptr)
  {
    idx++;
    if ((*it).getData() == elm)
    {
      return idx;
    }
    it = it->getNext();
  }

  return -1;
}

template <class E>
int LinkedListt<E>::lastIndexOf(const E elm)
{
  int idx = -1;
  int result = idx;
  NodeLinkedListt<E> *it = this->listIterator();

  while (it != nullptr)
  {
    idx++;
    if ((*it).getData() == elm)
    {
      result = idx;
    }
    it = it->getNext();
  }

  return result;
}

template <class E>
bool LinkedListt<E>::add(const E elm)
{
  NodeLinkedListt<E> *newNode = new NodeLinkedListt<E>(elm);
  if (this->data == nullptr)
  {
    this->data = newNode;
    this->size++;
    return true;
  }

  NodeLinkedListt<E> *it = this->data;
  while (it->hasNext())
  {
    it = it->getNext();
  }
  it->setNextNode(newNode);
  newNode->setPreviousNode(it);
  this->size++;
  return true;
}

template <class E>
bool LinkedListt<E>::add(const int &idx, const E elm)
{
  // Case: list is empty, insert elm as the first List's node
  if (idx == 0 && this->size == 0)
  {
    return this->add(elm);
  }

  // Case: add elm as List's tail node
  if (idx == this->size)
  {
    return this->add(elm);
  }

  if (idx < 0 || idx > this->size)
  {
    return false;
  }

  NodeLinkedListt<E> *it = this->listIterator();
  int count = -1;
  NodeLinkedListt<E> *newNode = new NodeLinkedListt<E>(elm);

  while (it != nullptr)
  {
    count++;
    if (count == idx)
    {
      NodeLinkedListt<E> *preNode = it->getPrevious();
      NodeLinkedListt<E> *currentNode = it;

      newNode->setNextNode(currentNode);
      newNode->setPreviousNode(preNode);

      if (preNode != nullptr)
      {
        preNode->setNextNode(newNode);
      }
      else
      {
        this->data = newNode;
      }
      currentNode->setPreviousNode(newNode);
      this->size++;
      return true;
    }
    it = it->getNext();
  }

  return false;
}

template <class E>
bool LinkedListt<E>::removeAt(const int &idx)
{
  if (idx < 0 || idx >= this->getSize())
  {
    return false;
  }

  int count = -1;
  NodeLinkedListt<E> *it = this->listIterator();

  while (it != nullptr)
  {
    count++;
    if (count == idx)
    {
      NodeLinkedListt<E> *deletedNode = it;
      NodeLinkedListt<E> *preNode = it->getPrevious();
      NodeLinkedListt<E> *afterNode = it->getNext();

      if (preNode != nullptr)
      {
        preNode->setNextNode(afterNode);
      }
      else
      {
        this->data = afterNode;
      }

      if (afterNode != nullptr)
      {
        afterNode->setPreviousNode(preNode);
      }

      this->size--;
      delete deletedNode;
      return true;
    }
    it = it->getNext();
  }

  return false;
}

template <class E>
bool LinkedListt<E>::remove(const E elm)
{
  const int idx = this->indexOf(elm);

  if (idx <= -1)
  {
    return false;
  }

  return this->removeAt(idx);
}

template <class E>
bool LinkedListt<E>::addFirst(const E elm)
{
  this->size++;
  NodeLinkedListt<E> *newNode = new NodeLinkedListt<E>(elm);
  NodeLinkedListt<E> *it = this->listIterator();
  it->setPreviousNode(newNode);
  newNode->setNextNode(it);
  this->data = newNode;
  return true;
}

template <class E>
int LinkedListt<E>::getSize()
{
  return this->size;
}

template <class E>
bool LinkedListt<E>::isEmpty()
{
  return this->size == 0;
}

template <class E>
void LinkedListt<E>::clear()
{
  NodeLinkedListt<E> *it = this->listIterator();

  while (it != nullptr)
  {
    NodeLinkedListt<E> *p = it;
    it = it->getNext();
    delete p;
  }

  this->data = nullptr;
  this->size = 0;
}

template <class E>
bool LinkedListt<E>::contains(const E elm)
{
  NodeLinkedListt<E> *it = this->listIterator();
  while (it != nullptr)
  {
    if ((*it).getData() == elm)
    {
      return true;
    }
    it = it->getNext();
  }
  return false;
}

template <class E>
const E LinkedListt<E>::set(const int &idx, const E elm)
{
  if (idx < 0 || idx >= this->size)
  {
    throw "index is out of range";
  }

  //    NodeLinkedListt<E> *newNode = new NodeLinkedListt<E>(elm);
  NodeLinkedListt<E> *it = this->listIterator();
  int count = -1;
  while (it != nullptr)
  {
    count++;
    if (count == idx)
    {
      const E &x = (*it).getData();
      (*it).setData(elm);
      return x;
    }
    it = it->getNext();
  }

  // not affected, c++ require return
}

template <class E>
E LinkedListt<E>::get(const int &idx)
{
  if (idx < 0 || idx >= this->getSize())
  {
    throw "index is out of range";
  }

  int count = -1;
  NodeLinkedListt<E> *it = this->listIterator();
  while (it != nullptr)
  {
    count++;
    if (count == idx)
    {
      return it->getData();
    }
    it = it->getNext();
  }

  // cannt reach here, c++ requires return
}

template <class E>
NodeLinkedListt<E> *LinkedListt<E>::listIterator()
{
  return this->data;
}

template <class E>
void LinkedListt<E>::show()
{
  NodeLinkedListt<E> *it = this->listIterator();

  if (!it)
    return;

  std::cout << it << " ";

  while (it->hasNext())
  {
    it = it->getNext();
    std::cout << it << " ";
  }
  std::cout << std::endl;
}

template <class E>
void LinkedListt<E>::sort(bool (*compare)(const E, const E))
{
  for (int i = 0; i < this->size - 1; i++)
  {
    for (int j = i + 1; j < this->size; j++)
    {
      if (compare(this->get(i), this->get(j)))
      {
        E tmp = this->get(i);
        this->set(i, this->get(j));
        this->set(j, tmp);
      }
    }
  }
}

template <class E>
bool LinkedListt<E>::compareASC(const E a, const E b)
{
  return a > b;
}

template <class E>
bool LinkedListt<E>::compareDESC(const E a, const E b)
{
  return b > a;
}

#endif // LINKEDLISTT_H

