#include "csr.hpp"

CSRGraph::CSRGraph(int size){
    setV(size);
    setE(0);
	if(size <= 0){
		std::cout << "You cannot create a graph without vertexes ;)\n";
		exit(-1);
	}
    offset = (int*)malloc((size+1)*sizeof(int));
	if(offset == NULL){
		std::cout << "Allocation error!\n";
		exit(-1);
	}
}

void CSRGraph::ReadGraph(AdjMatrix* adjm){
    int mrows = getV();
    int mcols = getV();
    int length;
    int count=0;
    bool* m = adjm->getm();

    if(m == NULL){
        std::cout << "The matrix is pointing to null\n";
        exit(-1);
    }
    if(adjm->getV() != getV()){
        std::cout << "That is not a correct matrix\n";
        exit(-1);
    }

    // Getting the total number of edges
    for(int i=0; i < mrows; ++i){
        for(int j=0; j < mcols; ++j){
            if(m[i*mrows + j] == true)
                count = count + 1;
        }
    }
    setE(count);
    ones = (int*)malloc(count*sizeof(int));
	if(ones == NULL){
		std::cout << "Allocation error!\n";
		exit(-1);
	}
 
    count = 0;
    for(int i=0; i < mrows; ++i){
        offset[i] = count;
        for(int j=0; j < mcols; ++j){
            if(m[i*mrows + j] == true){
                ones[count] = j;
                count = count + 1;
            }
        }
    }
    offset[getV()] = count;
}

void CSRGraph::Print(){
	for (int i = 0; i < getV(); ++i) {
        int count = 0;
		for (int j = 0; j < getV(); ++j) {
            if(count + offset[i] < getE()  &&  ones[count+offset[i]] == j  && 
                (count + offset[i]) < offset[i+1]){
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
    free(ones);
    free(offset);
    setV(0);
    setE(0);
}