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
  memset(input, 0, sizeof(input));
  do {
    cout << "Please enter an expression! Type 'QUIT' to quit." << endl;
    cin.getline(input, 30);
    if (strcmp(input, "QUIT") == 0) {
     quit = true;
    }
    else {
      int i = 0;
      while (input[i] != '\0') {
	if (isspace(input[i])) {
	  i++;
	}
	else {
	  cout << "sending in " << input[i] << endl;
	  cout << "the stack is: ";
	  printQueue(stackHead);
	  cout << endl;
	  parseInput(input[i], stackHead, queueHead);
	  i++;
	}
      }
      cout << "finished" << endl;
      printQueue(stackHead);
      while (stackHead != NULL) {
	Node* add = new Node(stackHead->getValue());
	cout << "adding " << add->getValue() << endl;
	enqueue(queueHead, add);
	stackHead = pop(stackHead);
      }
      cout << "printing..." << endl;
      printQueue(queueHead);
      while (queueHead != NULL) {
	pop(queueHead);
      }
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
    cout << "added to queue " << add->getValue() << endl;
    return;
  }
  else {
    if (in == '(') {
      push(stackHead, add);
      return;
    }
    if (in == ')') {
        while (stackHead != NULL && stackHead->getValue() != '(') {
	Node* queueAdd = new Node(stackHead->getValue());
	enqueue(queueHead, queueAdd);
	stackHead = pop(stackHead);
      }
	if (stackHead != NULL) {
      stackHead = pop(stackHead);
      return;
	}
	else {
	  return;
	}
    }
    if (stackHead == NULL) {
      push(stackHead, add);
      return;
    }
    else {
      int preStack = 0;
      int preIn = 0;
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
	while (stackHead != NULL && stackHead->getValue() != '(') {
	  if (stackHead->getValue() == '+' || stackHead->getValue() == '-') {
	    preStack = 1;
	  }
	  else if (stackHead->getValue() == '*' || stackHead->getValue() == '/') {
	    preStack = 2;
	  }
	  else if (stackHead->getValue() == '^') {
	    preStack = 3;
	  }
	  if (preStack >= preIn) {
	    Node* temp = new Node(stackHead->getValue());
	    enqueue(queueHead, temp);
	    stackHead = pop(stackHead);
	  }
	  else {
	    break;
	  }
	}
    }      
      push(stackHead, add);
    }
}

void printQueue(Node* queueHead) {
  Node* curr = queueHead;
  while (curr != NULL) {
    cout << curr->getValue();
    curr = curr->getNext();
  }
  cout << endl;
}

