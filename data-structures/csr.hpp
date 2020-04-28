#ifndef CSR_H
#define CSR_H

#include "graph.hpp"
#include "adj-matrix.hpp"

class CSRGraph : public Graph{
    int* ones;
    int* offset;
public:
    CSRGraph(int size);
    void ReadGraph(AdjMatrix* adjm);
    void Print();
    ~CSRGraph();
};

#endif