#include "data-structures/adj-matrix.hpp"

int main() {
	AdjMatrix* adj_matrix = new AdjMatrix(2);

	adj_matrix -> addEdge(1, 0);
	adj_matrix -> print();

	adj_matrix -> resize(3);
	adj_matrix -> print();
	
	free(adj_matrix);
	return 0;
}