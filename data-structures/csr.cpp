/******************************************************************************
 *
 * File Name: csr.cpp
 * Author:    Gonçalo Mestre & Pedro Reis
 * Last Modification: 24 May 2020
 *
 * NAME
 *  csr - creation of the object for the compressed sparse row
 *
 * DESCRIPTION
 *  This file contains the declaration of all functions used for the object of 
 * the compressed sparse row graph representation
 *
 *****************************************************************************/
#include "csr.hpp"

/**
 * CSRGraph::CSRGraph: Compressed sparse row constructor to initialize the 
 * graph
 *
 * \param size number of vertices in the graph
 */
CSRGraph::CSRGraph(int size) noexcept(false) {
    setV(size);
    setE(0);
    _ones = nullptr;

	if(size <= 0){
		throw std::invalid_argument("You cannot create a graph without vertexes ;)");
	}

    _offset = (int*)malloc((size+1)*sizeof(int));

	if(_offset == nullptr){
		throw std::bad_alloc();
	}
}

/**
 * CSRGraph::CSRGraph: CSR Graph copy constructor
 */
CSRGraph::CSRGraph(const CSRGraph& other) {
    setV(other.getV());
    setE(other.getE());
    
    size_t sizeOnes = other.getE() * sizeof(int);
    size_t sizeOffset = (other.getV() + 1) * sizeof(int);

    _ones = (int*) malloc(sizeOnes);
    _offset = (int*) malloc(sizeOffset);

    memcpy(_ones, other._ones, sizeOnes);
    memcpy(_offset, other._offset, sizeOffset);
}

/**
 * CSRGraph::ReadGraph: Reads the graph into a CSR from the adjacency matrix
 *
 * \param adjm adjacency matrix object from where the graph is read
 */
void CSRGraph::ReadGraph(AdjMatrix* adjm) noexcept(false) {
    int mrows = getV();
    int mcols = getV();
    int count=0;
    bool* m = adjm->getm();

    if(m == nullptr){
        throw std::range_error("The matrix is pointing to nullptr");
    }

    if(adjm->getV() != getV()){
        throw std::range_error("That is not a correct matrix");
    }

    if (_ones != nullptr) {
        throw std::runtime_error("CSR is already set!");
    }

    // Getting the total number of edges
    for(int i=0; i < mrows; ++i){
        for(int j=0; j < mcols; ++j){
            if(m[i*mrows + j] == true)
                count = count + 1;
        }
    }

    setE(count);
    _ones = (int*)malloc(count*sizeof(int));

	if(_ones == nullptr){
		throw std::bad_alloc();
	}
 
    count = 0;
    for(int i=0; i < mrows; ++i){
        _offset[i] = count;
        for(int j=0; j < mcols; ++j){
            if(m[i*mrows + j] == true){
                _ones[count] = j;
                count = count + 1;
            }
        }
    }
    _offset[getV()] = count;
}

/**
 * CSRGraph::isAdjacent: verifies if two nodes are adjacent
 *
 * \param i first node
 * \param j second node
 */
bool CSRGraph::isAdjacent(int i, int j) noexcept(false){
    if(i < 0 || i >= getV() || j < 0 || j >= getV()){
        throw std::range_error("The value of i or j is not correct!");
    }
    for(int a=_offset[i]; a < _offset[i+1]; ++a){
        if(_ones[a] == j)
            return true;
    }
    return false;
}

/**
 *	AdjList::findAdjacent: verifies if any of the vertices in a given list
 * are adjacent with the vertex given
 *
 *	\param i vertex given
 *	\param j list of vertices
 */
int CSRGraph::findAdjacent(int i, std::list<int>& j) noexcept(false){
    std::list<int>::iterator it;

    if(i < 0 || i >= getV()){
        throw std::range_error("The value of i is not correct!");
    }
    for(it = j.begin(); it != j.end(); ++it){
        if(*it < 0 || *it >= getV()){
            throw std::range_error("The value of some j is not correct");
        }
    }
    it = j.begin();
    for(int a=_offset[i]; a<_offset[i+1]; ++a){
        while(it != j.end() && *it < _ones[a])
            ++it;
        if(*it == _ones[a])
            return 1;
    }
    return 0;
}

/**
 *  CSRGraph::degree: returns the degree of a node
 *
 *  \param v the node
 */
int CSRGraph::degree(int v){
    int d = _offset[v+1]-_offset[v];
    return d;
}

/**
 *  CSRGraph::RandomWedge(int v)
 *
 *  \param v the node for which the random wedge is selected
 */
void CSRGraph::RandomWedge(int v, struct wedge* w){
    int size = _offset[v+1] - _offset[v];
    int r = rand() % size;
    int s;
    do{
        s = rand() % size;
    }while(s == r);
    w->a = v;
    w->b = _ones[_offset[v] + r];
    w->c = _ones[_offset[v] + s];
}

/**
 *  CSRGraph::triangle: returns 1 if the wedge forms a triangle, 0
 * otherwise
 *
 *  \param a first wedge node
 *  \param b second wedge node
 *  \param c third wedge node
 */
int CSRGraph::triangle(int a, int b, int c){
    if(isAdjacent(a, b) && isAdjacent(b, c) && isAdjacent(c, a))
        return 1;
    
    return 0;
}

/**
 *  CSRGraph::Print: Prints the csr graph
 */
void CSRGraph::Print(){
	for (int i = 0; i < getV(); ++i) {
        int count = 0;
		for (int j = 0; j < getV(); ++j) {
            if(count + _offset[i] < getE()  &&  _ones[count+_offset[i]] == j  && 
                (count + _offset[i]) < _offset[i+1]){
                std::cout << "1 ";
                count = count + 1;
            }
            else
                std::cout << "0 ";
		}
		std::cout << std::endl;
	}
}

/**
 * 
 */
void CSRGraph::removeEdge(int u, int v) {
    if (u < 0 || v < 0) {
		throw std::out_of_range("indexes below 0");
	}

	if (u >= getV() || v >= getV() ) {
		throw std::out_of_range("indexes out of range");
	}

    for(int i = _offset[u]; i < _offset[u + 1]; ++i) {
        if (_ones[i] == v) {
            _ones[i] = -1;
        }
    }
    
    for (int j = _offset[v]; j < _offset[v + 1]; ++j) {
        if (_ones[j] == u) {
            _ones[j] = -1;
        }
    }
}

bool CSRGraph::exists(int u, int v) {
    if(u < 0 || u >= getV() || v < 0 || v >= getV()){
        throw std::range_error("The value of i or j is not correct!");
    }

    for (int i = _offset[u]; i < _offset[u + 1]; ++i) {
        if (_ones[i] == v) {
            return true;
        }
    }

    return false;
}

/**
 * CSRGraph::~CSRGraph: Compressed sparse row destructor to destroy the 
 * graph
 */
CSRGraph::~CSRGraph(){
    free(_ones);
    free(_offset);
    setV(0);
    setE(0);
}




































///// FUNÇOES QUE DEPOIS TIVE DE CAGAR, PODEM SER UTEIS, ANTES DA ENTREGA APAGAMOS



/**
 * CSRGraph::isDefined: Verifies if the csr graph structure is already defined
 *
int CSRGraph::isDefined() noexcept(false){
    if(_offset != nullptr && _ones != nullptr)
        return 1;
    return 0;
}

/**
 * CSRGraph::getOffset: returns the offset array of the graph
 *
 * \param copy array being changed to a copy of the offset array
 *
void CSRGraph::getOffset(int* copy){
    for(int i=0; i <= getV(); ++i)
        copy[i] = _offset[i];
}*/

/**
 * CSRGraph::getOnes: returns the ones array of the graph
 *
 * \param copy array being changed to a copy of the ones array
 *
void CSRGraph::getOnes(int* copy){
    for(int i=0; i <= getE(); ++i)
        copy[i] = _ones[i];
}*/

/**
 * CSRGraph::CopyCSR: Copies an old csr graph to the current object
 *
 * \param old csr graph being copied
 *
void CopyCSR(CSRGraph* old) noexcept(false){
    if(old->isDefined() == 0){
        throw std::runtime_error("Old CSR is not defined");
    }
    if(old->getV() != getV()){
        throw std::range_error("That is not a correct graph");
    }
    if(_ones != nullptr) {
        throw std::runtime_error("CSR is already set!");
    }
    setE(old->getE());
    originalE = old->getE();
    _ones = (int*)malloc((old->getE())*sizeof(int));
    old->getOffset(_offset);
    old->getOnes(_ones);
}*/