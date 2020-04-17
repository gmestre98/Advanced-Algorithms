#include "adj-list.hpp"

AdjList::AdjList() : _size(0) {
    _adjlist.resize(0);
}

AdjList::AdjList(int size) throw () : _size(size) {
    _adjlist.resize(size);
}

void AdjList::addEdge(int i, int j, int w) const throw () {
 	if (i < 0 || j < 0 || w <= 0) {
		throw std::out_of_range("indexes below 0");
	}

	if (i >= _size || j >= _size ) {
		throw std::out_of_range("indexes out of range");
	}

    _adjlist[i].push_back(edge(j, w));
    _adjlist[j].push_back(edge(i, w));
}

//void AdjList::resize()