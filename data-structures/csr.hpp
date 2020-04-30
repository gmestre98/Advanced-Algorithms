#ifndef CSR_H
#define CSR_H

#include "graph.hpp"
#include "adj-matrix.hpp"

class CSRGraph : public Graph{
    int* _ones;
    int* _offset;
public:
    CSRGraph(int size) noexcept(false);
    void ReadGraph(AdjMatrix* adjm) noexcept(false);
    void Print();
    ~CSRGraph();
};

#endif