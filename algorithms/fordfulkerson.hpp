/******************************************************************************
 *
 * File Name: karger.cpp
 * Author:    Gonçalo Mestre & Pedro Reis
 * Last Modification: 28 May 2020
 *
 * NAME
 *  fordfulkerson - functions used to implement Ford-Fulkerson's algorithm
 *
 * DESCRIPTION
 *  This file contains the implementation of all functions used in the
 * implementation of Ford-Fulkerson's algorithm for the computation of the 
 * minimum cut size by using the Min-Cut Max-Flow Theorem. This done for three 
 * different graph representations.
 *
 *****************************************************************************/

#ifndef FORDFULKERSON_H
#define FORDFULKERSON_H

#include <climits>
#include <functional>
#include <queue>
#include <cstring>

#include "../data-structures/adj-matrix.hpp"
#include "../data-structures/adj-list.hpp"
#include "../data-structures/csr.hpp"

int fordfulkerson(AdjMatrix* graph);
int fordfulkerson(AdjList* graph);
int fordfulkerson(CSRGraph* graph);

#endif