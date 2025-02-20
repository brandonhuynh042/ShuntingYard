#include <iostream>
#include "Node.h"

using namespace std;

void push(Node* &stackHead, Node* newNode);
void pop(Node* &stackHead);
void enqueue(Node* &stackHead, Node* newNode);
void dequeue(Node* &stackHead);
int main() {
  
  return 0;
}

void push(Node* &stackHead, Node* newNode) {
  Node* temp = stackHead;
  stackHead = newNode;
  stackHead->setNext(temp);
}

void pop(Node* &stackHead) {
  if (stackHead == NULL) {
    return;
  }
  Node* temp = stackHead;
  stackHead = stackHead->getNext();
  delete temp;
}

void enqueue(Node* &stackHead, Node* newNode) {
  if (stackHead == NULL) {
    stackHead = newNode;
    return;
  }
  Node* curr = stackHead;
  while (curr->getNext() != NULL) {
    curr = curr->getNext();
  }
  curr->setNext(newNode);
}

void dequeue (Node* &stackHead) {
  pop(stackHead);  // pop should be the same??
}
