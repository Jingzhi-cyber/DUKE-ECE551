#include <algorithm>
#include <cstdlib>

#include "set.h"

using namespace std;

template<typename T>
class BstSet : public Set<T> {
  struct Node {
    Node * left;
    Node * right;
    T key;

    Node() : left(NULL), right(NULL), key(T()) {}
    Node(const T & key) : left(NULL), right(NULL), key(key) {}
  };

  Node * root;

 public:
  virtual void add(const T & key) {
    Node ** current = &root;
    while (*current != NULL) {
      if (key < (*current)->key) {
        current = &(*current)->left;
      }
      else {
        current = &(*current)->right;
      }
    }
    *current = new Node(key);
  }

  virtual bool contains(const T & key) const {
    Node * current = root;
    while (current != NULL) {
      if (key == current->key) {
        return true;
      }
      else if (key < current->key) {
        current = current->left;
      }
      else {
        current = current->right;
      }
    }
    return false;
  }

  Node * getSimilarNode(Node * curr) {
    while (curr != NULL && curr->left != NULL) {
      curr = curr->left;
    }
    return curr;
  }
  Node * removeHelper(Node * curr, const T & key) {
    if (curr == NULL) {
      return NULL;
    }
    else if (key < curr->key) {
      curr->left = removeHelper(curr->left, key);
    }
    else if (key > curr->key) {
      curr->right = removeHelper(curr->right, key);
    }
    else {
      // leaf node
      if (curr->left == NULL && curr->right == NULL) {
        delete curr;
        curr = NULL;
      }
      else if (curr->left == NULL) {
        Node * temp = curr->right;
        delete curr;
        curr = temp;
      }
      else if (curr->right == NULL) {
        Node * temp = curr->left;
        delete curr;
        curr = temp;
      }
      else {
        Node * temp = getSimilarNode(curr->right);
        curr->key = temp->key;
        //curr->value = temp->value;
        curr->right = removeHelper(curr->right, curr->key);
      }
    }

    return curr;
  }

  virtual void remove(const T & key) { removeHelper(root, key); }

  void destroy(Node * root) {
    if (root == NULL) {
      return;
    }
    destroy(root->left);
    destroy(root->right);
    delete root;
  }

  Node * copyHelper(Node * root, const Node * otherRoot) {
    if (otherRoot != NULL) {
      root = new Node;
      root->key = otherRoot->key;
      //      root->value = otherRoot->value;
      root->left = copyHelper(root->left, otherRoot->left);
      root->right = copyHelper(root->right, otherRoot->right);
      return root;
    }
    return NULL;
  }

  virtual ~BstSet<T>() { destroy(root); }

  BstSet<T>() : root(NULL) {}
  BstSet<T>(const BstSet<T> & rhs) : root(NULL) { root = copyHelper(root, rhs.root); };

  BstSet<T> & operator=(const BstSet<T> & rhs) {
    if (&rhs != this) {
      BstSet<T> tempMap = rhs;
      Node * t = root;
      root = tempMap.root;
      tempMap.root = t;
    }
    return *this;
  }
};
