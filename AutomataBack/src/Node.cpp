#include "Node.h"
#include <stdio.h>

Node::Node(int data) {
    this->data = data;
    this->next = 0;
}

int Node::getData() {
    return this->data;
}

Node* Node::getNext () {
    return this->next;
}

void Node::setNext(Node* next) {
    this->next = next;
}

void Node::print() {
    printf("I'm a node and I contain %d. Next up is %d\n", this->data, this->next);
}