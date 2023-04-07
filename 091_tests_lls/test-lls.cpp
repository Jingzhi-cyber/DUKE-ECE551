#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

using namespace std;

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME
    IntList il;
    il.addFront(1);
    assert(il.head != NULL);
    assert(il.tail != NULL);

    assert(il.head->data == 1);
    assert(il.tail->data == 1);

    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.tail->next == NULL);
    assert(il.tail->prev == NULL);
  }

  void testAddFront2() {
    IntList il;
    il.addFront(2);
    il.addFront(1);

    assert(il.head->data == 1);
    assert(il.tail->data == 2);
    assert(il.head != il.tail);
    assert(il.head->prev == NULL);
    assert(il.head->next == il.tail);
    assert(il.tail->prev == il.head);
    assert(il.tail->next == NULL);
  }

  // add ones
  void testAddBack() {
    IntList il;
    il.addBack(1);

    assert(il.head != NULL);
    assert(il.tail != NULL);

    assert(il.head->data == 1);
    assert(il.tail->data == 1);

    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.tail->next == NULL);
    assert(il.tail->prev == NULL);
  }

  void testAddBack2() {
    IntList il;
    il.addBack(1);
    il.addBack(2);

    assert(il.head->data == 1);
    assert(il.tail->data == 2);
    assert(il.head != il.tail);
    assert(il.head->prev == NULL);
    assert(il.head->next == il.tail);
    assert(il.tail->prev == il.head);
    assert(il.tail->next == NULL);
  }

  void testAddSize() {
    IntList il;
    il.addFront(1);
    assert(il.getSize() == 1);

    IntList il2;
    il2.addFront(1);
    il2.addFront(2);
    assert(il2.getSize() == 2);
  }

  // rule of 3 ones
  void testCopy() {
    IntList l1;
    l1.addBack(1);
    l1.addBack(2);
    l1.addBack(3);

    IntList l2(l1);

    assert(l1.getSize() == l2.getSize());
    assert(l1.tail->data == l2.tail->data);

    IntList::Node * n1 = l1.head;
    IntList::Node * n2 = l2.head;
    assert(l1.head->prev == l2.head->prev);

    while (n1 != NULL && n2 != NULL) {
      assert(n1->data == n2->data);
      if (n1->next != NULL) {
        assert(n1->next->data == n2->next->data);
        //        assert(n1->prev->data == n2->prev->data);
      }
      n1 = n1->next;
      n2 = n2->next;
    }
  }

  void testAssignment() {
    IntList l1;
    l1.addBack(1);
    l1.addBack(2);
    l1.addBack(3);

    IntList l2;
    l2.addFront(5);

    l2 = l1;

    assert(l1.getSize() == l2.getSize());
    assert(l1.tail->data == l2.tail->data);

    IntList::Node * n1 = l1.head;
    IntList::Node * n2 = l2.head;

    while (n1 != NULL && n2 != NULL) {
      assert(n1->data == n2->data);
      if (n1->next != NULL) {
        assert(n1->next->data == n2->next->data);
        //        assert(n1->prev->data == n2->prev->data);
      }
      n1 = n1->next;
      n2 = n2->next;
    }
  }

  void testDeleteSize1() {
    IntList il;
    il.addFront(1);

    il.remove(1);

    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }

  void testDeleteSize3() {
    IntList il;
    il.addBack(1);
    il.addBack(2);
    il.addBack(3);

    il.remove(2);
    assert(il.head->data == 1);
    assert(il.head->next->data == 3);
    assert(il.head->next->next == NULL);
    assert(il.tail->next == NULL);
    assert(il.tail->prev->data == 1);

    assert(il.getSize() == 2);
  }

  // Removal ones
  void testRemoveFront() {
    IntList il;
    il.addBack(1);
    il.addBack(2);
    il.addBack(3);

    il.remove(1);

    assert(il.head->data == 2);
    assert(il.head->next->data == 3);
    assert(il.head->prev == NULL);
    assert(il.tail->prev->data == 2);

    assert(il.getSize() == 2);
  }

  void testRemoveBack() {
    IntList il;
    il.addFront(3);
    il.addFront(2);
    il.addFront(1);

    il.remove(3);

    assert(il.tail->data == 2);
    assert(il.head->next->next == NULL);
    assert(il.tail->prev->data == 1);
    assert(il.tail->next == NULL);

    assert(il.getSize() == 2);
  }

  void testRemoveMiddle() {
    IntList il;
    il.addBack(1);
    il.addBack(2);
    il.addBack(3);

    il.remove(2);

    assert(il.head->next->data == 3);
    assert(il.head->next->next == NULL);
    assert(il.head->next->prev->data == 1);
    assert(il.tail->prev->data == 1);

    // assert find fails for removed element
    //assert(il.find() == false);
    assert(il[1] == 3);
  }

  void testReturnValueofRemove() {
    IntList il;
    il.addFront(1);

    int a = il.remove(1);
    assert(a == true);

    il.addFront(1);
    int b = il.remove(3);
    assert(b == false);
  }

  void testNextPrev() {
    IntList il;
    il.addBack(1);
    il.addBack(2);

    assert(il.head->next->prev->data == 1);
    assert(il.tail->prev->next->data == 2);
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddFront2();

  t.testAddBack();
  t.testAddBack2();
  t.testAddSize();

  t.testCopy();
  t.testAssignment();

  t.testRemoveFront();
  t.testRemoveBack();
  t.testRemoveMiddle();
  t.testReturnValueofRemove();
  t.testNextPrev();
  t.testDeleteSize1();
  t.testDeleteSize3();

  return EXIT_SUCCESS;
}
