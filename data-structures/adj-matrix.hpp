#ifndef ADJ_MATRIX_H
#define ADJ_MATRIX_H

#include <stdlib.h>
#include <stdexcept>
#include <iostream>
#include "graph.hpp"

//template<typename T>
class AdjMatrix : public Graph {
	bool* _matrix;
public:
	AdjMatrix();
	AdjMatrix(int size) throw ();

	void addEdge(int i, int j) throw ();
	void print();
	bool* getm();
	int* copymtoint();
	bool isAdjacent(int i, int j);
	~AdjMatrix();
};

#endif