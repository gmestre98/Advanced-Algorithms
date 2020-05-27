/******************************************************************************
 *
 * File Name: csr.hpp
 * Author:    Gonçalo Mestre & Pedro Reis
 * Last Modification: 24 May 2020
 *
 * NAME
 *  csr - creation of the object for the compressed sparse row
 *
 * DESCRIPTION
 *  This file contains the declaration of the object of the compressed sparse
 * row specifying what parts of this object should be public or private
 *
 *****************************************************************************/
#ifndef CSR_H
#define CSR_H

#include "graph.hpp"
#include "adj-matrix.hpp"
#include <list>
#include <time.h>

/**
 * Implementation of a compressed sparse row
 *
 * The compressed sparse row is implemented for graph representation, using
 * O(V + E) space,
 * O(degree(V)) for worst case on  verifying an edge
 *
 */
class CSRGraph : public Graph{
    int* _ones;
    int* _offset;
public:
    CSRGraph(int size) noexcept(false);
    void ReadGraph(AdjMatrix* adjm) noexcept(false);
    int isAdjacent(int i, int j) noexcept(false);
    int findAdjacent(int i, std::list<int>& j);
    int degree(int v);
    void RandomWedge(int v, struct wedge* w);
    int triangle(int a, int b, int c);
    void Print();
    ~CSRGraph();
};

#endif