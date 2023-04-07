#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>

//YOUR CODE GOES HERE

class invalid : public std::exception {
 public:
  virtual const char * what() const throw() { return "not found"; }
};

template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;

    Node() : next(NULL), prev(NULL) {}
    Node(const T & _data) : data(_data), next(NULL), prev(NULL) {}
    Node(const T & _data, Node * _next) : data(_data), next(_next), prev(NULL) {}
    Node(const T & _data, Node * _next, Node * _prev) :
        data(_data), next(_next), prev(_prev) {}
  };

  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}

  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    Node * current = rhs.head;
    for (int i = 0; i < rhs.size; i++) {
      addBack(current->data);
      current = current->next;
    }
  }

  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      Node * tempHead = new Node(rhs.head->data, NULL, NULL);
      Node * currentTemp = tempHead;
      Node * currentRhs = rhs.head;

      while (currentRhs->next != NULL) {
        currentTemp->next = new Node(currentRhs->next->data, NULL, currentTemp);
        currentTemp = currentTemp->next;
        currentRhs = currentRhs->next;
      }

      Node * tempTail = currentTemp;

      while (head != NULL) {
        Node * temp = head->next;
        delete head;
        head = temp;
      }

      this->head = tempHead;
      this->tail = tempTail;
      this->size = rhs.size;
    }

    return *this;
  }

  ~LinkedList() {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
  }
  void addFront(const T & item) {
    this->head = new Node(item, head, NULL);
    if (tail == NULL) {
      tail = head;
    }
    else {
      head->next->prev = head;
    }
    size++;
  }

  void addBack(const T & item) {
    tail = new Node(item, NULL, tail);
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->prev->next = tail;
    }
    size++;
  }

  bool remove(const T & item) {
    Node ** current = &head;
    while (*current != NULL && (*current)->data != item) {
      current = &(*current)->next;
    }
    if (*current != NULL) {
      Node * temp = *current;
      *current = (*current)->next;
      if (*current != NULL) {
        (*current)->prev = temp->prev;
      }

      if (*current == NULL) {
        tail = temp->prev;
      }
      delete temp;
      size--;
      return true;
    }
    else {
      return false;
    }
  }

  T & operator[](int index) {
    if (index < 0 || index >= this->size) {
      throw invalid();
    }

    Node * current = head;
    for (int i = 0; i < index; i++) {
      current = current->next;
    }

    return current->data;
  }

  const T & operator[](int index) const {
    if (index < 0 || index >= this->size) {
      throw invalid();
    }

    Node * current = head;
    for (int i = 0; i < index; i++) {
      current = current->next;
    }

    return current->data;
  }

  int find(const T & item) const {
    int index = 0;
    Node * current = head;
    for (int i = 0; i < size; i++) {
      if (current->data == item) {
        return index;
      }
      index++;
      current = current->next;
    }

    return -1;
  }

  int getSize() const { return this->size; }
};

#endif
