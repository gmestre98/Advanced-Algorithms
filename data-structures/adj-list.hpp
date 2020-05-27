/******************************************************************************
 *
 * File Name: adj-list.hpp
 * Author:    Gonçalo Mestre & Pedro Reis
 * Last Modification: 24 May 2020
 *
 * NAME
 *  adj-list - the creation of the class for the adjacency list
 *
 * DESCRIPTION
 *  This file contains the declaration of the class of the adjacency list,
 * specifying what parts of this class should be public or private
 *
 *****************************************************************************/
#ifndef ADJ_LIST_H
#define ADJ_LIST_H

#include <stdlib.h>
#include <stdexcept>
#include "graph.hpp"
#include "intlist.hpp"
#include <list>


/**
 * Implementation of an adjacency list
 *
 * The adjacency list is implemented for graph representation, using
 * O(V + E) space,
 * O(degree(V)) for worst case on  verifying an edge
 * O(degree(V)) edge insertion
 *
 */
class AdjList : public Graph{
    IntList* _adjlist = nullptr;
    void copyAdjList(AdjList* other);
public:
    AdjList(int size)  noexcept (false);
    AdjList(const AdjList& object) noexcept (false);
    void addEdge(int i, int j) noexcept (false);
    void Print();
    void SpecificPrint(int vertex);
    bool isAdjacent(int i, int j);
    int findAdjacent(int i, std::list<int>& j) noexcept(false);
    ~AdjList();
};
#endif    