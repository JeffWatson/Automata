#ifndef __GRAPH_H_INCLUDED__
#define __GRAPH_H_INCLUDED__

#include "LinkedList.h"
#include <string>

class Graph {
    LinkedList** adjList;
    int degree;

    public:
    Graph();
    void addNode(int, LinkedList*);
    LinkedList* getNode(int i);
    void print();
    int getDegree();
    std::string toString();
};

#endif