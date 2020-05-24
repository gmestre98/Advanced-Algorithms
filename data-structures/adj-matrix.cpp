/******************************************************************************
 *
 * File Name: adj-matrix.cpp
 * Author:    Gonçalo Mestre & Pedro Reis
 * Last Modification: 24 May 2020
 *
 * NAME
 *  adj-matrix - creation of the object for the adjacency list
 *
 * DESCRIPTION
 *  This file contains the declaration of all functions used for the object of 
 * the adjacency matrix graph representation
 *
 *****************************************************************************/
#include "adj-matrix.hpp"

/**
 *	AdjMatrix::AdjMatrix: Adjacency matrix constructor to initialize the graph
 *
 *	\param size number of vertices in the graph
 */
AdjMatrix::AdjMatrix() {
	_matrix = nullptr;
	setV(0);
	setE(0);
}

/**
 *	AdjMatrix::AdjMatrix: Adjacency matrix constructor to initialize the graph
 *
 *	\param size number of vertices in the graph
 */
AdjMatrix::AdjMatrix(int size) throw () {
	size_t n = size*size;
	setV(size);
	setE(0);

	_matrix = (bool*)malloc(n*sizeof(bool));
	if (_matrix != nullptr) {
		for (int i = 0; i < (getV() * getV()); ++i) {
			_matrix[i] = false;
		}
	}else {
		throw std::bad_alloc();
	}
}

/**
 *	AdjMatrix::addEdge: adds an edge to the adjacency matrix
 *
 *	\param i first node of the edge
 *	\param j second node of the edge
 */
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

/**
 *	AdjMatrix::print: prints the adjacency matrix
 */
void AdjMatrix::print() {
	for (int i = 0; i < getV(); ++i) {
		for (int j = 0; j < getV(); ++j) {
			std::cout << _matrix[i * getV() + j] << " ";
		}
		std::cout << std::endl;
	}
}

/**
 *	AdjMatrix::getm: returns the adjacency matrix
 */
bool* AdjMatrix::getm(){
	return _matrix;
}

/**
 *	AdjMatrix::Copyadjm: Copies an old adjacency matrix to a new object
 *
 *	\param old adjm graph being copied
 */
void AdjMatrix::Copyadjm(AdjMatrix* old) noexcept(false){
	if(old->getm() == nullptr){
		throw std::runtime_error("Old Adjacency matrix is not defined");
	}
	if(old->getV() != getV()){
		throw std::range_error("Graphs dimensions do not agree");
	}
	setE(old->getE());
	for(int i=0; i < getV(); ++i){
		for(int j=0; j < getV(); ++j){
			if(old->isAdjacent(i, j) == 1)
				_matrix[i * getV() + j] = true;
		}
	}
}

/**
 *	AdjMatrix::ContractEdge: Contracts an edge and merges the two vertices being the
 * merged one represented on the line and column of the original vertex with the lowest
 * index
 *
 *	\param i first node of the edge
 *	\param j second node of the edge
 */
void AdjMatrix::ContractEdge(int i, int j){
	int min, max;
	if(i > j){
		min = j;
		max = i;
	}
	else{
		min = i;
		max = j;
	}
	_matrix[i * getV() + j] = false;
	_matrix[i * getV() + i] = false;
	_matrix[j * getV() + i] = false;
	_matrix[j * getV() + j] = false;
	for(int a=0; a < getV(); ++a){
		if(_matrix[max * getV() + a] == true)
			_matrix[min * getV() + a] = true;
		_matrix[max * getV() + a] = false;
		if(_matrix[a * getV() + max] == true)
			_matrix[a * getV() + min] = true;
		_matrix[a * getV() + max] = false;
	}
}


/**
 *	AdjMatrix::isAdjacent: verifies if two nodes are adjacent
 *
 *	\param i first node
 *	\param j second node
 */
int AdjMatrix::isAdjacent(int i, int j){
	if(_matrix[i * getV() + j] == true)
		return 1;
	return 0;
}

/**
 *	AdjMatrix::~AdjMatrix: Adjacency matrix destructor to destroy the graph
 */
AdjMatrix::~AdjMatrix() {
	free(_matrix);
	setV(0);
	setE(0);