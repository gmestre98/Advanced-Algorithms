/******************************************************************************
 *
 * File Name: adj-list.cpp
 * Author:    Gonçalo Mestre & Pedro Reis
 * Last Modification: 24 May 2020
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
 *	AdjList::AdjList: Adjacency List constructor to initialize the adjacency list
 *
 *	\param size number of vertices in the graph
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
 *	AdjList::addEdge: Adds an unweighted undirected edge to the graph
 *
 *	\param i one of the vertices of the edge
 *	\param j the other vertex of the edge
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
	} catch (std::exception& err) {
		std::cerr << err.what() << std::endl;
	}
}

/**
 *	AdjList::Print: prints the composition of the graph
 */
void AdjList::Print() {
	std::cout << "Graph Composition\n\n";
	for(int i = 0; i < getV(); ++i){
		std::cout << "Vertex: " << i << "has edges with vertices:\n";
		_adjlist[i].printList();
		std::cout << "\n";
	}
}

/**
 *	AdjList::SpecificPrint: prints the edges of a given vertex
 *
 *	\param vertex the vertex for which the edges are being printed
 */
void AdjList::SpecificPrint(int vertex) {
	if(vertex > -1 && vertex < getV()){
		std::cout << "Vertex: " << vertex << "has edges with vertices:\n";
		_adjlist[vertex].printList();
		std::cout << "\n";
	}
	else
		std::cout << "That vertex does not exist!\n";
}

/**
 *	AdjList::isAdjacent: verifies the existence of an edge
 */
int AdjList::isAdjacent(int i, int j){
	if(_adjlist[i].existsNode(j))
		return 1;
	return 0;
}

/**
 *	AdjList::findAdjacent: verifies if any of the vertices in a given list
 * are adjacent with the vertex given
 *
 *	\param i vertex given
 *	\param j list of vertices
 */
int AdjList::findAdjacent(int i, std::list<int>& j) noexcept(false){
    std::list<int>::iterator it;
	int ret;

    if(i < 0 || i >= getV()){
        throw std::range_error("The value of i is not correct!");
    }
    for(it = j.begin(); it != j.end(); ++it){
        if(*it < 0 || *it >= getV()){
            throw std::range_error("The value of some j is not correct");
        }
    }
	ret = _adjlist[i].findNodes(j);
    return ret;
}

/**
 *	AdjList::~Adjlist: adjacency list destructor
 */
AdjList::~AdjList() {
	delete[] _adjlist;
	setV(0);
	setE(0);
}


































///// FUNÇOES QUE DEPOIS TIVE DE CAGAR, PODEM SER UTEIS, ANTES DA ENTREGA APAGAMOS




/**
 *	AdjList::ReturnList(i): Returns the pointer to of one of the integer lists
 *
 *	\param i the number of the node
 */
/*IntList* AdjList::ReturnList(int i) noexcept(false){
	if(i < 0 || i >= getV()){
		throw std::range_error("That is not a valid node");
	}
	return &(_adjlist[i]);
}


/**
 *	AdjList::Copyadjl: Copies an old adjacency list to a new object
 *
 *	\param old adjl graph being copied
 *
void AdjList::Copyadjl(AdjList* old) noexcept(false){
	if(old->getE() == 0){
		throw std::runtime_error("Old Adjacency list is not defined");
	}
	if(old->getV() != getV()){
		throw std::range_error("Graphs dimensions do not agree");
	}

	for(int i=0; i < getV(); ++i){
		(old->ReturnList(i))->CopyList(&_adjlist[i]);
	}
}*/
/*/**
 *	AdjList::ContractEdge: contracts an edge of the graph and merges
 * the vertices
 *
 *	\param i first node of the edge
 *	\param j second node of the edge
 *
void AdjList::ContractEdge(int i, int j) noexcept(false){
	int min, max;
	if(i > j){
		min = j;
		max = i;
	}
	else{
		min = i;
		max = j;
	}

	// Delete node
	_adjlist[i].deleteNode(j);
	_adjlist[j].deleteNode(i);
	// Merge List
	_adjlist[max].MergeListInto(&_adjlist[min]);
	// Delete List
	_adjlist[max].deleteAllNodes();
}*/