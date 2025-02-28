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
void infix(BTree* input, int precedence);


/* This program takes in an exp
int main() {
  bool quit = false;
  char input[30];
  Node* stackHead = NULL;
  Node* queueHead = NULL;
  NodeT* tStackHead = NULL;
  do {
    // take in expression
    cout << "Please enter an expression! Type 'QUIT' to quit." << endl;
    cin.getline(input, 30);
    if (strcmp(input, "QUIT") == 0) {
     quit = true;
    }
    else {
      // traverse through input
      int i = 0;
      while (input[i] != '\0') {
	// skip if it's a space
	if (isspace(input[i])) {
	  i++;
	}
	// otherwise, parse it!
	else {
          parseInput(input[i], stackHead, queueHead);
	  i++;
	}
      }
      // once the expresion is parsed, pop everything left from the stack to queue
      while (stackHead != NULL) {
	Node* add = new Node(stackHead->getValue());
	enqueue(queueHead, add);
	stackHead = pop(stackHead);
      }
      /*  while (queueHead != NULL) {
	pop(queueHead);
      }
      */
      // parse the postfix expression into the tree, empty the queue
      while (queueHead != NULL) {
        treeParse(queueHead->getValue(), tStackHead);
        pop(queueHead);
      }
      // user input for how they want it to be printed
      cout << "Type '1' for prefix, '2' for postfix, '3' for infix" << endl;
      int uInput;
      cin >> uInput;
      cin.ignore();
      // prefix
      if (uInput == 1) {
      cout << "prefix: " << endl;
      NodeT* curr = tStackHead;
      while (curr != NULL) {
	printTree(curr->getValue());
	curr = curr->getNext();
      }
      cout << endl;
      }
      // postfix
      else if (uInput == 2) {
        cout << "postfix: " << endl;
        NodeT* curr = tStackHead;
        while (curr != NULL) {
          printTreeBackwards(curr->getValue());
          curr = curr->getNext();
        }
      cout << endl;
      }
      // infix
      else if (uInput == 3) {
	cout << "infix: " << endl;
	NodeT* curr = tStackHead;
	while (curr != NULL) {
	  infix(curr->getValue(), 0);
	  curr = curr->getNext();
	}
	cout << endl;
      }
      // empty the tree stack for the next round of shunting!
      while (tStackHead != NULL) {
	popT(tStackHead);
      }
    }
  } while (quit == false);
  return 0;
}

// pushing to stack
void push(Node* &stackHead, Node* newNode) {
  // set the node as the new head of the linked list
  Node* temp = stackHead;
  stackHead = newNode;
  stackHead->setNext(temp);
}

// popping from stack
Node* pop(Node* &stackHead) {
  if (stackHead == NULL) {
    return stackHead;
  }
  // change head to the second element, free memory
  Node* temp = stackHead;
  stackHead = stackHead->getNext();
  delete temp;
  return stackHead; // return new head
}

// pushT and popT are the same as above, just for tree nodes
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

// queueing node
void enqueue(Node* &stackHead, Node* newNode) {
  if (stackHead == NULL) {
    stackHead = newNode;
    return;
  }
  // traverse to end of queue, add the new node to the end
  Node* curr = stackHead;
  while (curr->getNext() != NULL) {
    curr = curr->getNext();
  }
  curr->setNext(newNode);
}

void dequeue (Node* &stackHead) {
  pop(stackHead);  // pop should be the same??
}

// handling initial exprsesion input
void parseInput(char in, Node* &stackHead, Node* &queueHead) {
  Node* add = new Node(in);
  // if the input is a digit, it immediately goes to the queue
  if (isdigit(in)) {
    enqueue(queueHead, add);
    return;
  }
  else {
    // same if it's a left para
    if (in == '(') {
      push(stackHead, add);
      return;
    }
    // if it's a right para:
    if (in == ')') {
      // pop nodes from the stack to queue until the matching para is found, or it's empty (mismatching)
        while (stackHead != NULL && stackHead->getValue() != '(') {
	Node* queueAdd = new Node(stackHead->getValue());
	enqueue(queueHead, queueAdd);
	stackHead = pop(stackHead);
      }
	// if it's not empty, remove the left para from stack
	if (stackHead != NULL) {
      stackHead = pop(stackHead);
      return;
	}
	else {
	  return;
	}
    }
    // if it's empty
    if (stackHead == NULL) {
      push(stackHead, add);
      return;
    }
    else {
      // determine precedence of input
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
  	while (stackHead != NULL && stackHead->getValue() != '(') {
	  // determine precedence of stack head
	  if (stackHead->getValue() == '+' || stackHead->getValue() == '-') {
	    preStack = 1;
	  }
	  else if (stackHead->getValue() == '*' || stackHead->getValue() == '/') {
	    preStack = 2;
	  }
	  else if (stackHead->getValue() == '^') {
	    preStack = 3;
	  }
	  // if the stack has greater or equal precedence, pop from stack to queue until this isn't the case
	  if (preStack >= preIn) {
	    Node* temp = new Node(stackHead->getValue());
	    enqueue(queueHead, temp);
	    stackHead = pop(stackHead);
	  }
	  // if the input has higher precedence, it can be added straight away
	  else {
	    break;
	  }
	}
    }
    // add the new operator to stack
      push(stackHead, add);
    }
}

void printQueue(Node* queueHead) {
  // traverse through queue, print everything
  Node* curr = queueHead;
  while (curr != NULL) {
    cout << curr->getValue();
    curr = curr->getNext();
  }
  cout << endl;
}

// parsing from the queue to the expression tree
void treeParse(char input, NodeT* &tStackHead) {
  BTree* newTree = new BTree(input);
  // if the tree stack is empty, this is the new head!
  if (tStackHead == NULL) {
    tStackHead = new NodeT(newTree);
    return;
  }
  // if it's a number, it gets pushed to the end of the tree stack
  if (isdigit(input)) {
    NodeT* curr = tStackHead;
    while (curr->getNext() != NULL) {
      curr = curr->getNext();
    }
    NodeT* toAdd = new NodeT(newTree);
    curr->setNext(toAdd);
    return;
  }
  // if there's an operator
  else {
    NodeT* prev = tStackHead->getNext();
    NodeT* prev2 = tStackHead;
    //if there's only two nodes, create a new head with the two node's trees as the children.
    if (prev->getNext() == NULL) {
      NodeT* add = new NodeT(newTree);
      add->getValue()->setLeft(prev2->getValue());
      add->getValue()->setRight(prev->getValue());
      tStackHead = add;
      delete prev;
      delete prev2;
      return;
    }
    // otherwise, traverse through the stack until the end.
    NodeT* curr = tStackHead->getNext()->getNext();
    while (curr->getNext() != NULL) {
      prev2 = prev;
      prev = curr;
      curr = curr->getNext();
    }
    // create a new node, and set the new operator as the parent's of the last two
    NodeT* toAdd = new NodeT(newTree);
    toAdd->getValue()->setLeft(prev->getValue());
    toAdd->getValue()->setRight(curr->getValue());
    // connect it to the third last node
    prev2->setNext(toAdd);
    // delete old nodes
    delete curr;
    delete prev;
    return;
  }
}

// printing in prefix
void printTree(BTree* input) {
  if (input == NULL) {
    return;
  }
  // print the operator before working down the tree recursively to a number (at the leaf)
  cout << input->getValue() << " ";
  printTree(input->getLeft());
  printTree(input->getRight());
}
// printing in postfix
void printTreeBackwards(BTree* input) {
  if (input == NULL) {
    return;
  }
  // work down the tree recursively until it reaches a leaf, print
  printTreeBackwards(input->getLeft());
  printTreeBackwards(input->getRight());
  cout << input->getValue() << " ";
}

// printing in in-fix
void infix(BTree* input, int precedence) {
  if (input == NULL) {
    return;
  }
  // if it's a leaf/number, print.
  if (isdigit(input->getValue())) {
    cout << input->getValue() << " ";
    return;
  }
  else {
    // determine precedence of operator
    int childP = 0;
    if (input->getValue() == '+' || input->getValue() == '-') {
        childP = 1;
      }
    else if (input->getValue() == '*' || input->getValue() == '/') {
        childP = 2;
      }
    else if (input->getValue() == '^') {
        childP = 3;
      }
    // compare to it's parent: if smaller, we need parentheses
    if (precedence != 0 && childP < precedence) {
      cout << " ( ";
      // by going left child, parent, right child, the expression is printed in in-fix.
      infix(input->getLeft(), childP);
      cout << input->getValue() << " ";
      infix(input->getRight(), childP);
      cout << " ) ";
      // these parentheses wrap the child expression with lower precedence
    }
    // otheriwse, it can be printed normally
    else {
      infix(input->getLeft(), childP);
      cout << input->getValue() << " ";
      infix(input->getRight(), childP);
    }
  }
}
