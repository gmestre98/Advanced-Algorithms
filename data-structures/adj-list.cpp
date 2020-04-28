#include "adj-list.hpp"

AdjList::AdjList(int size){
	setV(size);
	setE(0);
	if(size <= 0){
		std::cout << "You cannot create a graph without vertexes ;)\n";
		exit(-1);
	}
	_adjlist = new intlist[size];
	if(_adjlist == NULL){
		std::cout << "Allocation error!\n";
		exit(-1);
	}
}

void AdjList::AddEdge(int i, int j) throw () {
 	if (i < 0 || j < 0) {
		throw std::out_of_range("indexes below 0");
	}

	if (i >= getV() || j >= getV() ) {
		throw std::out_of_range("indexes out of range");
	}
	if(i == j){
		std::cout << "A vertex can't have an edge with itself\n";
		return;
	}
	
	// A linha de baixo dá borrada, nao entendo porque
	if(_adjlist[i].AddNode(j) == 1 && _adjlist[j].AddNode(i) == 1)
		std::cout << "You added a node!\n";
	else
		std:: cout << "That node already existed, why are you adding it? You dumb?\n";
}

void AdjList::Print() {

	std::cout << "Graph Composition\n\n";
	for(int i = 0; i < getV(); ++i){
		std::cout << "Vertex: " << i << "has edges with vertexes:\n";
		_adjlist[i].PrintList();
		std::cout << "\n";
	}
}

void AdjList::SpecificPrint(int vertex) {
	if(vertex > -1 && vertex < getV()){
		std::cout << "Vertex: " << vertex << "has edges with vertexes:\n";
		_adjlist[vertex].PrintList();
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