#include "Graph.h"
#include "LinkedList.h"
#include <stdio.h>
#include <sstream>


Graph::Graph() {
    this->degree = 0;
    this->adjList = new LinkedList*[1000];
}

void Graph::addNode(int index, LinkedList* list) {
    this->adjList[index] = list;
    this->degree++;
}

LinkedList* Graph::getNode(int i) {
    return this->adjList[i];
}

void Graph::print() {
    for(int i = 1; i < this->degree + 1; i ++) {
        LinkedList* node = this->getNode(i);
        if(node != 0 ) {
            printf("Graph node %d\n", i);
            node->print();
        }
    }
}

int Graph::getDegree() {
    return this->degree;
}

std::string Graph::toString() {
    std::stringstream s;

    for(int i = 1; i < this->degree + 1; i ++) {
        LinkedList* node = this->getNode(i);
        if(node != 0 ) {
            s << "Graph vertex " << i << " points to:\n" << node->toString();
        }
    }

    return s.str();
}
