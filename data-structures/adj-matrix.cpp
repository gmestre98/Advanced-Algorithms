#include "adj-matrix.hpp"

AdjMatrix::AdjMatrix() : _size(0) {
	_matrix = nullptr;
}

AdjMatrix::AdjMatrix(int size) throw () : _size(size) {
	size_t n = _size * sizeof(bool);

	_matrix = (bool*) malloc(n * n);

	if (_matrix != nullptr) {
		for (int i = 0; i < (_size * _size); ++i) {
			_matrix[i] = false;
		}
	} else {
		throw std::bad_alloc();
	}
}

void AdjMatrix::addEdge(int i, int j) const throw () {
	if (i < 0 || j < 0) {
		throw std::out_of_range("indexes below 0");
	}

	if (i >= _size || j >= _size ) {
		throw std::out_of_range("indexes out of range");
	}

	_matrix[i * _size + j] = true;
	_matrix[j * _size + i] = true;
}

void AdjMatrix::resize(int new_size) throw () {
	if (new_size <= _size) {
		throw std::invalid_argument("new size must be bigger than the previous size");
	}

	size_t n = new_size * sizeof(bool);
	bool* new_matrix = (bool*) malloc(n * n);

	for (int i = 0; i < (new_size * new_size); ++i) {
		new_matrix[i] = false;
	}

	for (int i = 0; i < _size; ++i) {
		for (int j = 0; j < _size; ++j) {
			new_matrix[i * new_size + j] = _matrix[i * _size + j];
		}
	}

	bool* old_matrix = _matrix;
	_matrix = new_matrix;
	new_matrix = old_matrix;
	
	free(new_matrix);

	_size = new_size;
}

void AdjMatrix::print() {
	for (int i = 0; i < _size; ++i) {
		for (int j = 0; j < _size; ++j) {
			std::cout << _matrix[i * _size + j] << " ";
		}
		std::cout << std::endl;
	}
}

AdjMatrix::~AdjMatrix() {
	free(_matrix);
	delete this;
}