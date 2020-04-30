#include "data-structures/adj-matrix.hpp"
#include "data-structures/adj-list.hpp"
#include "data-structures/csr.hpp"

int main() {

	AdjList* Paul = new AdjList(3);
	Paul->addEdge(1, 0);
	Paul->addEdge(1, 0);
	Paul->addEdge(0, 2);
	Paul->Print();

	delete Paul;

	AdjMatrix* adj_matrix = new AdjMatrix(6);
	adj_matrix -> print();
	adj_matrix -> addEdge(0, 2);
	adj_matrix -> addEdge(0, 3);
	adj_matrix -> addEdge(1, 4);
	adj_matrix -> addEdge(1, 5);
	adj_matrix -> addEdge(1, 2);
	adj_matrix -> addEdge(3, 4);
	adj_matrix -> print();

	CSRGraph* csr = new CSRGraph(6);
	csr -> ReadGraph(adj_matrix);
	csr -> Print();
	delete csr;
}