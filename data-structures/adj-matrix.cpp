#include "adj-matrix.hpp"


AdjMatrix::AdjMatrix() {
	_matrix = nullptr;
	setV(0);
	setE(0);
}

AdjMatrix::AdjMatrix(int size) throw () {
	size_t n = size*size;
	setV(size);
	setE(0);

	_matrix = (bool*)malloc(n*sizeof(bool));
	if (_matrix != nullptr) {
		for (int i = 0; i < (getV() * getV()); ++i) {
			_matrix[i] = false;
		}
	} else {
		throw std::bad_alloc();
	}
}

void AdjMatrix::addEdge(int i, int j) throw () {
	if (i < 0 || j < 0) {
		throw std::out_of_range("indexes below 0");
	}

	if (i >= getV() || j >= getV() ) {
		throw std::out_of_range("indexes out of range");
	}

	_matrix[i * getV() + j] = true;
	_matrix[j * getV() + i] = true;
	incE();
}

void AdjMatrix::print() {
	for (int i = 0; i < getV(); ++i) {
		for (int j = 0; j < getV(); ++j) {
			std::cout << _matrix[i * getV() + j] << " ";
		}
		std::cout << std::endl;
	}
}

bool* AdjMatrix::getm(){
	return _matrix;
}


AdjMatrix::~AdjMatrix() {
	delete[] _matrix;
	setV(0);
	setE(0);
}