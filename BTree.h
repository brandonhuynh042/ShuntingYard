#ifndef BTREE_H
#define BTREE_H
#include <iostream>
using namespace std;

class BTree {
 public:
  BTree(char newValue);
  ~BTree();
  void setLeft(BTree* newLeft);
  void setRight(BTree* newRight);
  void setValue(char newValue); 
  BTree* getLeft();
  BTree* getRight();
  char getValue();
 protected:
  char value;
  BTree* left;
  BTree* right;
};
#endif
