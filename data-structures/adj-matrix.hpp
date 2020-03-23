#ifndef ADJ_MATRIX_H
#define ADJ_MATRIX_H

#include <stdlib.h>
#include <stdexcept>
#include <iostream>

//template<typename T>
class AdjMatrix {
	bool* _matrix = nullptr;
	int   _size   = 0;
public:
	AdjMatrix();
	AdjMatrix(int size) throw ();

	void addEdge(int i, int j) const throw ();
	void resize(int new_size) throw ();
	void print();

	~AdjMatrix();
};

#endif