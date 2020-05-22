/******************************************************************************
 *
 * File Name: adj-list.cpp
 * Author:    Gonçalo Mestre & Pedro Reis
 * Last Modification: 21 May 2020
 *
 * NAME
 *  adj-list - the creation of the class for the adjacency list
 *
 * DESCRIPTION
 *  This file contains the declaration of all functions used for the class of 
 * the adjacency list graph representation
 *
 *****************************************************************************/
#include "adj-list.hpp"
#include <exception>
#include <stdexcept>


/**
 * AdjList::AdjList: Adjacency List constructor to initialize the adjacency list
 *
 * \param size number of vertices in the graph
 */
AdjList::AdjList(int size) noexcept(false) {
	setV(size);
	setE(0);
	if(size <= 0){
		throw std::invalid_argument("You cannot create a graph without vertexes ;)");
	}

	_adjlist = new IntList[size];

	if(_adjlist == nullptr){
		throw std::bad_alloc();
	}
}

/**
 * AdjList::addEdge: Adds an unweighted undirected edge to the graph
 *
 * \param i one of the vertices of the edge
 * \param j the other vertex of the edge
 */
void AdjList::addEdge(int i, int j) noexcept (false) {
 	if (i < 0 || j < 0) {
		throw std::out_of_range("indexes below 0");
	}

	if (i >= getV() || j >= getV() ) {
		throw std::out_of_range("indexes out of range");
	}
	if(i == j){
		throw std::logic_error("A vertex can't have an edge with itself");
	}
	
	// A linha de baixo dá borrada, nao entendo porque
	try {
		_adjlist[i].addNode(j);
		_adjlist[j].addNode(i);
		std::cout << "You added a node!" << std::endl;
	} catch (std::exception& err) {
		std::cerr << err.what() << std::endl;
	}
}

/**
 * AdjList::Print: prints the composition of the graph
 */
void AdjList::Print() {
	std::cout << "Graph Composition\n\n";
	for(int i = 0; i < getV(); ++i){
		std::cout << "Vertex: " << i << "has edges with vertexes:\n";
		_adjlist[i].printList();
		std::cout << "\n";
	}
}

/**
 * AdjList::SpecificPrint: prints the edges of a given vertex
 *
 * \param vertex the vertex for which the edges are being printed
 */
void AdjList::SpecificPrint(int vertex) {
	if(vertex > -1 && vertex < getV()){
		std::cout << "Vertex: " << vertex << "has edges with vertexes:\n";
		_adjlist[vertex].printList();
		std::cout << "\n";
	}
	else
		std::cout << "That vertex does not exist!\n";
}

/**
 * AdjList::copylist: returns the adjacency list
 */
void AdjList::copyadjlist(IntList* adjl){
	for(int i=0; i < getV(); ++i){
		_adjlist[i].mergeLists(&adjl[i]);
	}
}

/**
 * AdjList::isAdjacent: verifies the existence of an edge
 */
int AdjList::isAdjacent(int i, int j){
	if(_adjlist[i].existsNode(j))
		return 1;
	return 0;
}



/**
 * AdjList::~Adjlist: adjacency list destructor
 */
AdjList::~AdjList() {
	delete[] _adjlist;
	setV(0);
	setE(0);
}