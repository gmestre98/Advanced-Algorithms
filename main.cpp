#include <climits>

#include "data-structures/adj-matrix.hpp"
#include "data-structures/adj-list.hpp"
#include "data-structures/csr.hpp"
#include "algorithms/karger.hpp"
#include "algorithms/uniformwedge.hpp"
#include "algorithms/fordfulkerson.hpp"
#include "graph-generator/graph-loader.hpp"

int main() {
	int mincut1;
	double clust;
    srand(time(NULL));

	/*GraphLoader* gl = new GraphLoader();
	CSRGraph* csr = gl->loadNextGraphAsCSR();
	clust = uwedgecsr(csr);
	std::cout << "clust: " << clust << "\n";
	delete csr;*/


	AdjList* Paul = new AdjList(8);
	Paul -> addEdge(0, 1);
	Paul -> addEdge(0, 2);
	Paul -> addEdge(0, 3);
	Paul -> addEdge(1, 4);
	Paul -> addEdge(1, 7);
	Paul -> addEdge(2, 3);
	Paul -> addEdge(2, 5);
	Paul -> addEdge(3, 4);
	Paul -> addEdge(3, 5);
	Paul -> addEdge(4, 5);
	Paul -> addEdge(4, 6);
	Paul -> addEdge(5, 6);
	Paul -> addEdge(6, 7);
	Paul -> addEdge(4, 7);
	/*mincut1 = kargeradjl(Paul);
	std::cout << "\nMin Cut size: " << mincut1 << "\n";*/
	clust = uwedgeadjl(Paul);
	std::cout << "\nclust coeff:" << clust << "\n";
	clust = uedgeadjl(Paul);
	std::cout << "\nclust coeff:" << clust << "\n";
	clust = uvertexadjl(Paul);
	std::cout << "\nclust coeff:" << clust << "\n";
	delete Paul;

	AdjMatrix* adj_matrix = new AdjMatrix(8);
	adj_matrix -> addEdge(0, 1);
	adj_matrix -> addEdge(0, 2);
	adj_matrix -> addEdge(0, 3);
	adj_matrix -> addEdge(1, 4);
	adj_matrix -> addEdge(1, 7);
	adj_matrix -> addEdge(2, 3);
	adj_matrix -> addEdge(2, 5);
	adj_matrix -> addEdge(3, 4);
	adj_matrix -> addEdge(3, 5);
	adj_matrix -> addEdge(4, 5);
	adj_matrix -> addEdge(4, 6);
	adj_matrix -> addEdge(5, 6);
	adj_matrix -> addEdge(6, 7);
	adj_matrix -> addEdge(4, 7);
	clust = uwedgeadjm(adj_matrix);
	std::cout << "\nclust coeff:" << clust << "\n";
	clust = uedgeadjm(adj_matrix);
	std::cout << "\nclust coeff:" << clust << "\n";
	clust = uvertexadjm(adj_matrix);
	std::cout << "\nclust coeff:" << clust << "\n";
	/*mincut1 = kargeradjm(adj_matrix);
	std::cout << "\nMin Cut size: " << mincut1 << "\n";*/
	CSRGraph* csr = new CSRGraph(8);
	csr -> ReadGraph(adj_matrix);
    delete adj_matrix;
	/*mincut1 = kargercsr(csr);
	std::cout << "\nMin Cut size:" << mincut1 << "\n";*/
	clust = uwedgecsr(csr);
	std::cout << "\nclust coeff:" << clust << "\n";
	clust = uedgecsr(csr);
	std::cout << "\nclust coeff:" << clust << "\n";
	clust = uvertexcsr(csr);
	std::cout << "\nclust coeff:" << clust << "\n";
	delete csr;

	/*AdjMatrix* m = new AdjMatrix(6);
	AdjList* m = new AdjList(6);
	m->addEdge(0, 1);
	m->addEdge(0, 2);
	m->addEdge(1, 2);
	m->addEdge(1, 3);
	m->addEdge(2, 4);
	m->addEdge(3, 5);
	m->addEdge(3, 4);
	m->addEdge(4, 5);
*/
	

	CSRGraph* a = new CSRGraph(6);
	AdjList* m = new AdjList(6);
	m->addEdge(0, 1);
	m->addEdge(0, 2);
	m->addEdge(1, 2);
	m->addEdge(1, 3);
	m->addEdge(2, 4);
	m->addEdge(3, 5);
	m->addEdge(3, 4);
	m->addEdge(4, 5);
	//a->ReadGraph(m);

	int mc = fordfulkerson(m); //INT_MAX;
	/*int maxFlow = 0;// = fordfulkerson(m);
	for (int src = 0; src < a->getV(); ++src) {
		for (int sink = a->getV() - 1; sink > 0; --sink) {
			std::cout << "przed ford fulkerson" << std::endl;
			std::cout << "sink jest " << sink << std::endl;
			std::cout << "src jest " << src << std::endl;

			if (src != sink) {
				maxFlow = fordfulkerson(a, src, sink);
			}

			
			std::cout << "max flow jest " << mc << std::endl;
			if (mc > maxFlow) {
				mc = maxFlow;
			}
		}
		std::cout << "czesc" << std::endl;
	}*/
	

	delete m;
	delete a;
	std::cout << "min cut e " << mc << std::endl;

}