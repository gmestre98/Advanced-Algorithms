#include "data-structures/adj-matrix.hpp"
#include "data-structures/adj-list.hpp"
#include "data-structures/csr.hpp"
#include "algorithms/karger.hpp"

int main() {
	int  mincut1;
    srand(time(NULL));

	/*AdjList* Paul = new AdjList(4);
	Paul->addEdge(0, 1);
	Paul->addEdge(0, 2);
	Paul->addEdge(1, 2);
	Paul->addEdge(1, 3);
	Paul->addEdge(2, 3);
	Paul->Print();
	mincut1 = kargeradjl(Paul);
	std::cout << "\nMin Cut size: " << mincut1 << "\n";
	delete Paul;*/

	AdjMatrix* adj_matrix = new AdjMatrix(6);
	adj_matrix -> addEdge(0, 2);
	adj_matrix -> addEdge(0, 3);
	adj_matrix -> addEdge(1, 4);
	adj_matrix -> addEdge(1, 5);
	adj_matrix -> addEdge(1, 2);
	adj_matrix -> addEdge(3, 4);
	adj_matrix -> print();
	/*mincut1 = kargeradjm(adj_matrix);
	std::cout << "\nMin Cut size: " << mincut1 << "\n";*/
	adj_matrix -> print();
	CSRGraph* csr = new CSRGraph(6);
	csr -> ReadGraph(adj_matrix);
	csr -> Print();
	delete csr;
}