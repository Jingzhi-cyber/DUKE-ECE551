#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!

  priority_queue_t pq;

  for (int i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      pq.push(new Node(i, counts[i]));
    }
  }

  while (pq.size() > 1) {
    Node * node1 = pq.top();
    pq.pop();
    Node * node2 = pq.top();
    pq.pop();

    Node * newNode = new Node(node1, node2);
    pq.push(newNode);
  }

  Node * root = pq.top();
  pq.pop();
  return root;
}
