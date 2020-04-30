#include "adj-list.hpp"
#include <exception>
#include <stdexcept>

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

void AdjList::Print() {
	std::cout << "Graph Composition\n\n";
	for(int i = 0; i < getV(); ++i){
		std::cout << "Vertex: " << i << "has edges with vertexes:\n";
		_adjlist[i].printList();
		std::cout << "\n";
	}
}

void AdjList::SpecificPrint(int vertex) {
	if(vertex > -1 && vertex < getV()){
		std::cout << "Vertex: " << vertex << "has edges with vertexes:\n";
		_adjlist[vertex].printList();
		std::cout << "\n";
	}
	else
		std::cout << "That vertex does not exist!\n";
}

AdjList::~AdjList() {
	delete[] _adjlist;
	setV(0);
	setE(0);
}