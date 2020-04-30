#include "csr.hpp"

CSRGraph::CSRGraph(int size) noexcept(false) {
    setV(size);
    setE(0);

	if(size <= 0){
		throw std::invalid_argument("You cannot create a graph without vertexes ;)");
	}

    _offset = (int*)malloc((size+1)*sizeof(int));

	if(_offset == nullptr){
		throw std::bad_alloc();
	}
}

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

CSRGraph::~CSRGraph(){
    free(_ones);
    free(_offset);
    setV(0);
    setE(0);
}