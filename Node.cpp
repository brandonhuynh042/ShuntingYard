#include "Node.h"
// Constructor for Node object
Node::Node(char newValue) {
  value = newValue;
  next = NULL;
}

// Destructor for Node object
Node::~Node() {
  next = NULL;
}

// Set the value for the node
void Node::setValue(char newValue) {
  value = newValue;
}

// get the value of the node
char Node::getValue() {
  return value;
}

// set the pointer to the next node
void Node::setNext(Node* newNext) {
  next = newNext;
}

// Get the pointer to the next node
Node* Node::getNext() {
  return next;
}
