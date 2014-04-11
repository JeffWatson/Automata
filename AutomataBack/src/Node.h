#ifndef __NODE_H_INCLUDED__
#define __NODE_H_INCLUDED__

class Node {
    int data;
    Node* next;

    public:
    Node(int);
    int getData();
    Node* getNext();
    void setNext(Node*);
    void print();
};

#endif