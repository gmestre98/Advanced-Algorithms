#include "data-structures/adj-matrix.hpp"
#include "data-structures/adj-list.hpp"
#include "data-structures/csr.hpp"
#include "algorithms/karger.hpp"
#include "graph-generator/graph-loader.hpp"

int main() {
	int  mincut1;
	AdjMatrix* adj_matrix = new AdjMatrix(6);
	adj_matrix -> addEdge(0, 2);
	adj_matrix -> addEdge(0, 3);
	adj_matrix -> addEdge(1, 4);
	adj_matrix -> addEdge(1, 5);
	adj_matrix -> addEdge(1, 2);
	adj_matrix -> addEdge(3, 4);
	adj_matrix -> print();
	mincut1 = karger(adj_matrix);
	std::cout << "\nMin Cut size: " << mincut1 << "\n";
	adj_matrix -> print();

	GraphLoader* graphLoader = new GraphLoader();
	
	while(graphLoader->hasMoreGraphs()) {
		AdjMatrix* new_adj_matrix = graphLoader->loadNextGraphAsAdjMatrix();
		std::cout << std::endl;
		new_adj_matrix->print();
		delete new_adj_matrix;
	}
	
	delete graphLoader;
}