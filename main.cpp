#include <climits>
#include <fstream>
#include <iostream>
#include <ctime>

#include "data-structures/adj-matrix.hpp"
#include "data-structures/adj-list.hpp"
#include "data-structures/csr.hpp"
#include "algorithms/karger.hpp"
#include "algorithms/uniformwedge.hpp"
#include "algorithms/fordfulkerson.hpp"
#include "graph-generator/graph-loader.hpp"

int main() {
    srand(time(NULL));

	GraphLoader* graphLoader = new GraphLoader();

	std::ofstream csvFordFulkersonAdjMatrix;
	csvFordFulkersonAdjMatrix.open("fordfulkersonAdjMatrix.csv");
	csvFordFulkersonAdjMatrix << "V,E,VE3,time,MinCut\n";
	
	std::cout << "Welcome!" << std::endl;

	
	int count = 1;
	/*std::cout << "Computing Ford-Fulkerson for Adjacency Matrix:" << std::endl;
	while (graphLoader->hasMoreGraphs()) {
		std::cout << "\t- Graph number " << count++ << std::endl;
		AdjMatrix* adjmatrix = graphLoader->loadNextGraphAsAdjMatrix();

		int V = adjmatrix->getV();
		int E = adjmatrix->getE();
		int V3 = V * V * V;

		const clock_t begin = std::clock();
		int mincut = fordfulkerson(adjmatrix);
		const clock_t end = std::clock();
		const clock_t elapsedTime = end - begin;

		csvFordFulkersonAdjMatrix << V << "," << E << "," << (E*V3) << "," << (elapsedTime) << "," << mincut << "\n";
		delete adjmatrix;
	}

	csvFordFulkersonAdjMatrix.close();
	std::cout << "Finished!" << std::endl << std::endl;
	*/
/*
	std::ofstream csvFordFulkersonAdjList;
	csvFordFulkersonAdjList.open("fordfulkersonAdjList.csv");
	csvFordFulkersonAdjList << "V,E,VE3,time,MinCut\n";

	count = 1;
	std::cout << "Computing Ford-Fulkerson for Adjacency List:" << std::endl;
	std::cout << "CLOCKS PER SEC" << CLOCKS_PER_SEC << std::endl;
	while (graphLoader->hasMoreGraphs()) {
		std::cout << "\t- Graph number " << count++ << std::endl;
		AdjList* graph = graphLoader->loadNextGraphAsAdjList();

		int V = graph->getV();
		int E = graph->getE();
		int V3 = V * V * V;

		const clock_t begin = std::clock();
		int mincut = fordfulkerson(graph);
		const clock_t end = std::clock();
		const clock_t elapsedTime = end - begin;

		csvFordFulkersonAdjMatrix << V << "," << E << "," << (E*V3) << "," << (elapsedTime) << "," << mincut << "\n";
		delete graph;
	}

	csvFordFulkersonAdjList.close();

	delete graphLoader;
	
	std::cout << "Finished!" << std::endl << std::endl;
	*/
	graphLoader = new GraphLoader();
	
	std::ofstream csvFordFulkersonCSR;
	csvFordFulkersonCSR.open("fordfulkersonCSR.csv");
	csvFordFulkersonCSR << "V,E,VE3,time,MinCut\n";

	count = 1;
	std::cout << "Computing Ford-Fulkerson for CSR:" << std::endl;
	while (graphLoader->hasMoreGraphs()) {
		std::cout << "\t- Graph number " << count++ << std::endl;
		CSRGraph* graph = graphLoader->loadNextGraphAsCSR();

		int V = graph->getV();
		int E = graph->getE();
		int V3 = V * V * V;

		const clock_t begin = std::clock();
		int mincut = fordfulkerson(graph);
		const clock_t end = std::clock();
		const clock_t elapsedTime = end - begin;

		csvFordFulkersonAdjMatrix << V << "," << E << "," << (E*V3) << "," << (elapsedTime) << "," << mincut << "\n";

		delete graph;
	}
	csvFordFulkersonCSR.close();

	delete graphLoader; 

	std::cout << "Finished!" << std::endl << std::endl;
/*
	graphLoader = new GraphLoader();

	std::ofstream kargerAdjMatrix;
	kargerAdjMatrix.open("kargerAdjMatrix.csv");
	kargerAdjMatrix << "V,E,time,MinCut\n";

	count = 1;
	std::cout << "Computing Karger for Adjacency Matrix:" << std::endl;
	while (graphLoader->hasMoreGraphs()) {
		std::cout << "\t- Graph number " << count++ << std::endl;
		AdjMatrix* graph = graphLoader->loadNextGraphAsAdjMatrix();

		int V = graph->getV();
		int E = graph->getE();
		int V3 = V * V * V;

		const clock_t begin = std::clock();
		int mincut = kargeradjm(graph);
		const clock_t end = std::clock();
		const clock_t elapsedTime = end - begin;

		kargerAdjMatrix << V << "," << E << "," << (E*V3) << float(elapsedTime) / CLOCKS_PER_SEC<< "," << mincut << "\n";
		delete graph;
	}
	kargerAdjMatrix.close();
	delete graphLoader;

	std::cout << "Finished!" << std::endl << std::endl;

	graphLoader = new GraphLoader();
	std::ofstream kargerAdjList;
	kargerAdjList.open("kargerAdjList.csv");
	kargerAdjList << "V,E,time,MinCut\n";

	count = 1;
	std::cout << "Computing Karger for Adjacency List:" << std::endl;
	while (graphLoader->hasMoreGraphs()) {
		std::cout << "\t- Graph number " << count++ << std::endl;
		AdjList* graph = graphLoader->loadNextGraphAsAdjList();

		int V = graph->getV();
		int E = graph->getE();
		int V3 = V * V * V;

		const clock_t begin = std::clock();
		int mincut = kargeradjl(graph);
		const clock_t end = std::clock();
		const clock_t elapsedTime = end - begin;

		kargerAdjList << V << "," << E << "," << (E*V3) << float(elapsedTime) /CLOCKS_PER_SEC << "," << mincut << "\n";
		delete graph;
	}
	kargerAdjList.close();
	std::cout << "Finished!" << std::endl << std::endl;
	delete graphLoader;
	graphLoader = new GraphLoader();
	std::ofstream kargerCSR;
	kargerCSR.open("kargerCSR.csv");
	kargerCSR << "V,E,time,MinCut\n";

	count = 1;
	std::cout << "Computing Karger for CSR:" << std::endl;
	while (graphLoader->hasMoreGraphs()) {
		std::cout << "\t- Graph number " << count++ << std::endl;
		CSRGraph* graph = graphLoader->loadNextGraphAsCSR();

		int V = graph->getV();
		int E = graph->getE();
		int V3 = V * V * V;

		const clock_t begin = std::clock();
		int mincut = kargercsr(graph);
		const clock_t end = std::clock();
		const clock_t elapsedTime = end - begin;

		kargerCSR << V << "," << E << "," << (E*V3) << float(elapsedTime) / CLOCKS_PER_SEC << "," << mincut << "\n";
		delete graph;
	}
	kargerCSR.close();
	std::cout << "Finished!" << std::endl << std::endl;
*/
	std::cout << "Thank you! Good bye!" << std::endl;

	//delete graphLoader;
}