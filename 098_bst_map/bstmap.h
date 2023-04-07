#include <algorithm>
#include <cstdlib>

#include "map.h"

using namespace std;

template<typename K, typename V>
class BstMap : public Map<K, V> {
  struct Node {
    Node * left;
    Node * right;
    K key;
    V value;

    Node() : left(NULL), right(NULL), key(K()), value(V()) {}
    Node(const K & key, const V & value) :
        left(NULL), right(NULL), key(key), value(value) {}
  };

  Node * root;

 public:
  virtual void add(const K & key, const V & value) {
    Node ** current = &root;
    while (*current != NULL) {
      if (key < (*current)->key) {
        current = &(*current)->left;
      }
      else {
        current = &(*current)->right;
      }
    }
    *current = new Node(key, value);
  }
  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * current = root;
    while (current != NULL) {
      if (key == current->key) {
        return current->value;
      }
      else if (key < current->key) {
        current = current->left;
      }
      else {
        current = current->right;
      }
    }
    throw std::invalid_argument("invalid key");
  }

  Node * getSimilarNode(Node * curr) {
    while (curr != NULL && curr->left != NULL) {
      curr = curr->left;
    }
    return curr;
  }
  Node * removeHelper(Node * curr, const K & key) {
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
        curr->value = temp->value;
        curr->right = removeHelper(curr->right, curr->key);
      }
    }

    return curr;
  }

  virtual void remove(const K & key) { removeHelper(root, key); }
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
      root->value = otherRoot->value;
      root->left = copyHelper(root->left, otherRoot->left);
      root->right = copyHelper(root->right, otherRoot->right);
      return root;
    }
    return NULL;
  }

  virtual ~BstMap<K, V>() { destroy(root); }

  BstMap<K, V>() : root(NULL) {}
  BstMap<K, V>(const BstMap<K, V> & rhs) : root(NULL) {
    root = copyHelper(root, rhs.root);
  }

  BstMap<K, V> & operator=(const BstMap<K, V> & rhs) {
    //BstMap<K, V> newMap(rhs);
    //destroy(root);
    //root = NULL;
    //    swap(root, newMap);
    /*
    if (&rhs != this) {
      BstMap<K, V> tempMap = rhs;
      Node * t = root;
      root = tempMap.root;
      tempMap.root = t;
    }
    */
    if (this != &rhs) {
      Node * temp = NULL;
      temp = copyHelper(temp, rhs.root);
      destroy(root);
      root = temp;
    }
    return *this;
  }
};
