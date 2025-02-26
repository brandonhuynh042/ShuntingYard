#include <iostream>
#include <cstring>
#include <cctype>
#include "Node.h"
#include "BTree.h"
#include "NodeT.h"
using namespace std;

void push(Node* &stackHead, Node* newNode);
Node* pop(Node* &stackHead);
void pushT(NodeT* &tStackHead, NodeT* newNode);
NodeT* popT(NodeT* &tStackHead);
void enqueue(Node* &stackHead, Node* newNode);
void dequeue(Node* &stackHead);
void printQueue(Node* queueHead);
void parseInput(char in, Node* &stackHead, Node* &queueHead);
void treeParse(char input, NodeT* &tStackHead);
void printTree(BTree* input);
void printTreeBackwards(BTree* input);

int main() {
  bool quit = false;
  char input[30];
  Node* stackHead = NULL;
  Node* queueHead = NULL;
  NodeT* tStackHead = NULL;
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
      /*  while (queueHead != NULL) {
	pop(queueHead);
      }
      */
      while (queueHead != NULL) {
        treeParse(queueHead->getValue(), tStackHead);
        pop(queueHead);
      }
      cout << "Type '1' for prefix, '2' for postfix, '3' for infix" << endl;
      int uInput;
      cin >> uInput;
      if (uInput == 1) {
      cout << "prefix: " << endl;
      NodeT* curr = tStackHead;
      while (curr != NULL) {
	printTree(curr->getValue());
	curr = curr->getNext();
      }
      cout << endl;
      }
      else if (uInput == 2) {
        cout << "postfix: " << endl;
        NodeT* curr = tStackHead;
        while (curr != NULL) {
          printTreeBackwards(curr->getValue());
          curr = curr->getNext();
        }
      cout << endl;
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

void pushT(NodeT* &tStackHead, NodeT* newNode) {
  NodeT* temp = tStackHead;
  tStackHead = newNode;
  tStackHead->setNext(temp);
}

NodeT* popT(NodeT* &tStackHead) {
  if (tStackHead == NULL) {
    return tStackHead;
  }
  NodeT* temp = tStackHead;
  tStackHead = tStackHead->getNext();
  delete temp;
  return tStackHead;
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

void treeParse(char input, NodeT* &tStackHead) {
  BTree* newTree = new BTree(input);
  if (tStackHead == NULL) {
    tStackHead = new NodeT(newTree);
    return;
  }
  if (isdigit(input)) {
    NodeT* curr = tStackHead;
    while (curr->getNext() != NULL) {
      curr = curr->getNext();
    }
    NodeT* toAdd = new NodeT(newTree);
    curr->setNext(toAdd);
    return;
  }
  else {
    NodeT* prev = tStackHead->getNext();
    NodeT* prev2 = tStackHead;
    //find the two last nodes
    if (prev->getNext() == NULL) {
      cout << "here" << endl;
      NodeT* add = new NodeT(newTree);
      add->getValue()->setLeft(prev2->getValue());
      add->getValue()->setRight(prev->getValue());
      cout << "here 2" << endl;
      tStackHead = add;
      delete prev;
      delete prev2;
      return;
    }
    NodeT* curr = tStackHead->getNext()->getNext();
    while (curr->getNext() != NULL) {
      prev2 = prev;
      prev = curr;
      curr = curr->getNext();
    }
    NodeT* toAdd = new NodeT(newTree);
    toAdd->getValue()->setLeft(prev->getValue());
    toAdd->getValue()->setRight(curr->getValue());
    prev2->setNext(toAdd);
    delete curr;
    delete prev;
    return;
  }
}

void printTree(BTree* input) {
  if (input == NULL) {
    return;
  }
  cout << input->getValue() << " ";
  printTree(input->getLeft());
  printTree(input->getRight());
}

void printTreeBackwards(BTree* input) {
  if (input == NULL) {
    return;
  }
  printTreeBackwards(input->getLeft());
  printTreeBackwards(input->getRight());
  cout << input->getValue() << " ";
}



