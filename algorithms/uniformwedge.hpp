/******************************************************************************
 *
 * File Name: uniformwedge.cpp
 * Author:    Gonçalo Mestre & Pedro Reis
 * Last Modification: 26 May 2020
 *
 * NAME
 *  uniformedge - implementation of the uniform wedge algorithm to compute the
 * clustering coefficient
 *
 * DESCRIPTION
 *  This file contains the declaration of all functions used in the
 * implementation of the uniform wedge algorithm for the computation of the 
 * clustering coefficient, being this done for three different graph representations
 *
 *****************************************************************************/

#ifndef UWEDGE_H
#define UWEDGE_H

#include <math.h>
#include "../data-structures/csr.hpp"
#include "../data-structures/adj-matrix.hpp"
#include "../data-structures/adj-list.hpp"

int RandomNumber(int);
int binarySearch(int, int*, int, int);
double uwedgecsr(CSRGraph *);

#endif