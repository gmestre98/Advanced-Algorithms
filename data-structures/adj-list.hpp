#ifndef ADJ_LIST_H
#define ADJ_LIST_H

#include <stdlib.h>
#include <stdexcept>
#include "graph.hpp"
#include "intlist.hpp"

class AdjList : public Graph{
    intlist* _adjlist = NULL;
public:
    AdjList(int size);
    void AddEdge(int i, int j) throw ();
    void Print();
    void SpecificPrint(int vertex);
    ~AdjList();
};
#endif    