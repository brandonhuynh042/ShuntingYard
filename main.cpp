#include <iostream>
#include <cstring>
#include <cctype>
#include "Node.h"
#include "BTree.h"
using namespace std;

void push(Node* &stackHead, Node* newNode);
Node* pop(Node* &stackHead);
void enqueue(Node* &stackHead, Node* newNode);
void dequeue(Node* &stackHead);
void printQueue(Node* queueHead);
void parseInput(char in, Node* &stackHead, Node* &queueHead);
int main() {
  bool quit = false;
  char input[30];
  Node* stackHead = NULL;
  Node* queueHead = NULL;
  do {
    cout << "Please enter an expression! Type 'QUIT' to quit." << endl;
    cin.getline(input, 30);
    if (strcmp(input, "QUIT") == 0) {
     quit = true;
    }
    else {
      int i = 0;
      while (input[i]) {
	cout << i << endl;
	if (input[i] == ' ') {
	  i++;
	}
	else {
	  cout << "sending in " << input[i] << endl;
	  parseInput(input[i], stackHead, queueHead);
	  i++;
	}
      }
      cout << "finished" << endl;
      while (stackHead != NULL) {
	Node* add = new Node(stackHead->getValue());
	cout << "adding " << add->getValue() << endl;
	enqueue(queueHead, add);
	stackHead = pop(stackHead);
      }
      cout << "printing..." << endl;
      printQueue(queueHead);
    }
  } while (quit == false);
  return 0;
}

void push(Node* &stackHead, Node* newNode) {
  Node* temp = stackHead;
  stackHead = newNode;
  stackHead->setNext(temp);
}

Node* pop(Node* &stackHead) {
  if (stackHead == NULL) {
    return stackHead;
  }
  Node* temp = stackHead;
  stackHead = stackHead->getNext();
  delete temp;
  return stackHead;
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

void parseInput(char in, Node* &stackHead, Node* &queueHead) {
  Node* add = new Node(in);
  if (isdigit(in)) {
    enqueue(queueHead, add);
    return;
  }
  else {
    if (stackHead == NULL || in == '(' || stackHead->getValue() == '(' && stackHead->getValue() != ')') {
      cout << "here" << endl;
      push(stackHead, add);
      cout << stackHead->getValue() << endl;
      return;
    }
    if (in == ')') {
      push(stackHead, add);
      stackHead = pop(stackHead);
      while (stackHead->getValue() != '(') {
	Node* add = new Node(stackHead->getValue());
	enqueue(queueHead, add);
	stackHead = pop(stackHead);
      }
      stackHead = pop(stackHead);
      return;
    }
    else {
      int preStack;
      int preIn;
      cout << "here 2" << endl;
      if (stackHead->getValue() == '+' || stackHead->getValue() == '-') {
	preStack = 1;
      }
      else if (stackHead->getValue() == '*' || stackHead->getValue() == '/') {
	preStack = 2;
      }
      else if (stackHead->getValue() == '^') {
	preStack = 3;
      }
      cout << "prestack is " << preStack << endl;
      if (in == '+' || in == '-') {
        preIn = 1;
      }
      else if (in == '*' || in == '/') {
        preIn = 2;
      }
      else if (in == '^') {
        preIn = 3;
      }
      cout << "prein is " << preIn << endl;
      if (preIn > preStack) {
	push(stackHead, add);
	return;
      }
      else {
	while (stackHead != NULL) {
	  if (preIn <= preStack && stackHead->getValue() != '(') {
	  cout << "here 3" << endl;
	  Node* add2 = new Node(stackHead->getValue());
	  enqueue(queueHead, add);
	  stackHead = pop(stackHead);
	  cout << "here 4" << endl;
	  if (stackHead != NULL) {
	  if (stackHead->getValue() == '+' || stackHead->getValue() == '-') {
	    preStack = 1;
	  }
	  else if (stackHead->getValue() == '*' || stackHead->getValue() == '/') {
	    preStack = 2;
	  }
	  else if (stackHead->getValue() == '^') {
	    preStack = 3;
	  }
	  cout << "here 5" << endl;
	  }
	  }
	}
      }
      push(stackHead, add);
    }
  }
}

void printQueue(Node* queueHead) {
  Node* curr = queueHead;
  //while (curr != NULL) {
    cout << curr->getValue();
    curr = curr->getNext();
        cout << curr->getValue();
    curr = curr->getNext();
    cout << curr->getValue();
    curr = curr->getNext();
    cout << curr->getValue();
    curr = curr->getNext();
    cout << curr->getValue();
    curr = curr->getNext();

    //}
  cout << '\n';
}
