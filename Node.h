#ifndef NODE_H
#define NODE_H
#include <iostream>
using namespace std;

class Node {
 public:
  Node(char newValue);                  // constructor
  ~Node();                                    // destructor
  void setValue (char newValue);      // setting the value of the node
  void setNext(Node* newNext);
  char getValue();                      // getting the value of the node
  Node* getNext();                            // getting the next node
 protected:
  char value;                           // value which the node holds
  Node* next;                                 // stores next node in list
};
#endif
