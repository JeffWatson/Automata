#include "LinkedList.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>

LinkedList::LinkedList() {
    this->first = NULL;
    this->length = 0;
}

LinkedList::LinkedList(Node* begin) {
    this->first = begin;

    Node* ptr = begin;
    int size = 1;
    while(ptr->getNext() != 0) {
        ptr = ptr->getNext();
        size++;
    }
    this->length = size;
}

Node* LinkedList::getFirst() {
    if (this->first != NULL) {
        return this->first;
    }
    return NULL;
}

void LinkedList::addNode(Node* newNode) {
    Node* node = getFirst();

    if (node == NULL) {
        this->first = newNode;
    } else {
        for(int i = 0; i <this->length - 1; i++) {
            node = node->getNext();
        }
        node->setNext(newNode);
    }

    this->length++;
}

void LinkedList::print() {
    Node* node = first;

    if(first == NULL) {
        printf("The list is empty :(\n");
    } else if (length == 1) {
        printf("Node data is: %d\n", node->getData());
    } else {
        for(int i = 0; i < length; i++){
            printf("Node data is: %d\n", node->getData());
            node = node->getNext();
         }
    }
}

int LinkedList::getLength() {
    return this->length;
}

std::string LinkedList::toString() {
    std::stringstream s;

    if(first == NULL )  {
        s << "The list is empty :(\n";
    } else if (length == 1) {
        s << "Edge data is: " <<  first->getData() << "\n";
    }  else {
        Node* node = this->first;

        for(int i = 0; i < length; i++){
            s << "Edge data is: " << node->getData() << "\n";
            node = node->getNext();
        }
    }

    return s.str();
}