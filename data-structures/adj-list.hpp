#ifndef ADJ_LIST_H
#define ADJ_LIST_H

#include <stdlib.h>
#include <stdexcept>
#include "graph.hpp"
#include "intlist.hpp"

class AdjList : public Graph{
    IntList* _adjlist = nullptr;
public:
    AdjList(int size)  noexcept (false);
    void addEdge(int i, int j) noexcept (false);
    void Print();
    void SpecificPrint(int vertex);
    ~AdjList();
};
#endif    