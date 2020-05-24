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

void printNestedList(std::list<std::list<int>>);
int logarithm(int);
void createauxlist(int);
void generatetworandom(int*, int*, int);
std::list<int>& getlist(int j);
int contractcsr(CSRGraph*);
int kargercsr(CSRGraph*);
int contractadjm(AdjMatrix*);
int kargeradjm(AdjMatrix*);

#endif