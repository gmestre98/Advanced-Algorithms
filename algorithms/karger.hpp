/******************************************************************************
 *
 * File Name: karger.hpp
 * Author:    Gonçalo Mestre & Pedro Reis
 * Last Modification: 21 May 2020
 *
 * NAME
 *  karger - functions used to implement karger's algorithm
 *
 * DESCRIPTION
 *  This file contains the declaration of all functions used in the
 * implementation of karger's algorithm for the computation of the minimum cut
 * size, being this done for three different graph representations
 *
 *****************************************************************************/
#ifndef KARGER_H
#define KARGER_H

#include <stdlib.h>
#include <stdexcept>
#include <iostream>
#include <list>
#include <time.h>
#include "../data-structures/adj-matrix.hpp"
#include "../data-structures/adj-list.hpp"
#include "../data-structures/csr.hpp"

void printNestedList(std::list<std::list<int> >);
int contractadjm(AdjMatrix*);
void mergevertadjm(int*, std::list<std::list<int> >*, int, int, int, int, int, int);
int logarithm(int);
int kargeradjm(AdjMatrix*);
int contractadjl(AdjList*);
void mergevertadjl(IntList*, std::list<std::list<int> >*, int, int, int, int);
int kargeradjl(AdjList*);

#endif