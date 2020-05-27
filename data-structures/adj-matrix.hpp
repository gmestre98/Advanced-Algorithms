/******************************************************************************
 *
 * File Name: adj-matrix.hpp
 * Author:    Gonçalo Mestre & Pedro Reis
 * Last Modification: 24 May 2020
 *
 * NAME
 *  adj-matrix - creation of the object for the adjacency matrix
 *
 * DESCRIPTION
 *  This file contains the declaration of the class of the adjacency matrix
 * specifying what parts of this class should be public or private
 *
 *****************************************************************************/
#ifndef ADJ_MATRIX_H
#define ADJ_MATRIX_H

#include <stdlib.h>
#include <stdexcept>
#include <iostream>
#include "graph.hpp"

/**
 * Implementation of an adjacency list
 *
 * The adjacency list is implemented for graph representation, using
 * O(V^2) space,
 * O(1) for verifying an edge
 * O(1) for edge insertion
 *
 */
class AdjMatrix : public Graph {
	bool* _matrix;
public:
	AdjMatrix();
	AdjMatrix(int size) throw ();

	void addEdge(int i, int j) throw ();
	void removeEdge(int i, int j) noexcept (false);
	void print();
	bool* getm();
	void Copyadjm(AdjMatrix* old);
	void ContractEdge(int i, int j);
	bool isAdjacent(int i, int j);
	int degree(int v);
	void RandomWedge(int v, struct wedge* w);
	int triangle(int a, int b, int c);
	~AdjMatrix();
};

#endif