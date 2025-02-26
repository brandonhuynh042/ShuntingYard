#include "NodeT.h"
#include "BTree.h"
// Constructor for Node object
NodeT::NodeT(BTree* newValue) {
  value = newValue;
  next = NULL;
}

// Destructor for Node object
NodeT::~NodeT() {
  next = NULL;
}

// Set the value for the node
void NodeT::setValue(BTree* newValue) {
  value = newValue;
}

// get the value of the node
BTree* NodeT::getValue() {
  return value;
}

// set the pointer to the next node
void NodeT::setNext(NodeT* newNext) {
  next = newNext;
}

// Get the pointer to the next node
NodeT* NodeT::getNext() {
  return next;
}
