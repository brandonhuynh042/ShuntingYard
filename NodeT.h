#ifndef NODET_H
#define NODET_H
#include <iostream>
#include "BTree.h"
using namespace std;

class NodeT {
 public:
  NodeT(BTree* newTree);                  // constructor
  ~NodeT();                                    // destructor
  void setValue (BTree* newValue);      // setting the value of the node
  void setNext(NodeT* newNext);
  BTree* getValue();                      // getting the value of the node
  NodeT* getNext();                            // getting the next node
 protected:
  BTree* value;                           // value which the node holds
  NodeT* next;                                 // stores next node in list
};
#endif
