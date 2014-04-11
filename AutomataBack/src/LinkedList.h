#ifndef __LINKEDLIST_H_INCLUDED__
#define __LINKEDLIST_H_INCLUDED__

#include "Node.h"
#include <string>

class LinkedList {
    Node* first;
    int length;

    public:
    LinkedList();
    LinkedList(Node*);
    Node* getFirst();
    void addNode(Node*);
    void print();
    int getLength();
    std::string toString();
};

#endif