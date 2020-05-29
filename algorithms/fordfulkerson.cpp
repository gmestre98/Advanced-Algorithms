/******************************************************************************
 *
 * File Name: karger.cpp
 * Author:    Gonçalo Mestre & Pedro Reis
 * Last Modification: 28 May 2020
 *
 * NAME
 *  fordfulkerson - functions used to implement Ford-Fulkerson's algorithm
 *
 * DESCRIPTION
 *  This file contains the implementation of all functions used in the
 * implementation of Ford-Fulkerson's algorithm for the computation of the 
 * minimum cut size by using the Min-Cut Max-Flow Theorem. This done for three 
 * different graph representations.
 *
 *****************************************************************************/

#include "fordfulkerson.hpp"

std::function<int (int, int)> min = [](int a, int b) { return (a < b) ? a : b; };

/**
 * hasMorePaths: Computes an incrementing path from ´source´ to ´sink´ using
 * DFS algorithm.
 * 
 * \param residualGraph: graph where to look
 * \param src: source node
 * \param sink: destination node
 * \param parent[]: array of nodes' parents
 * 
 * \return true if it founds any path and stores it in parent or false
 * otherwise
 */
bool hasMorePaths(Graph* residualGraph, int src, int sink, int parent[]) {
	bool visited[residualGraph->getV()];
	memset(visited, 0, sizeof(visited));

	std::queue<int> queue;
	queue.push(src);

	visited[src] = true;
	parent[src] = -1;

	while (!queue.empty()) {
		int u = queue.front();
		queue.pop();

		for (int v = 0; v < residualGraph->getV(); ++v) {
			if (visited[v] == false && residualGraph->isAdjacent(u, v)) {
				queue.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}

	return (visited[sink] == true);
}

/**
 * fordfulkerson: Computes Ford-Fulkerson Algorithm to obtain Maximum Flow
 * between source and sink. Uses Adjacency Matrix data-structure for representng
 * the graph
 * 
 * \param graph: represented by Adjacency Matrix data structure
 * \param src: source of the flow
 * \param sink: sink of the flow
 * 
 * \return: maximum flow between src and sink
 */
int fordfulkerson(AdjMatrix* graph, int src, int sink) {
	int v, u;

	AdjMatrix* residualGraph = new AdjMatrix(graph->getV());
	residualGraph->Copyadjm(graph);

	int parent[graph->getV()];

	int maxFlow = 0;

	while (hasMorePaths(residualGraph, src, sink, parent)) {
		int flow = INT_MAX;

		for (v = sink; v != src; v = parent[v]) {
			u = parent[v];
			flow = min(flow, residualGraph->isAdjacent(u, v)); 
		}

		for (v = sink; v != src; v = parent[v]) {
			u = parent[v];
			residualGraph->removeEdge(u, v);
		}

		maxFlow += flow;

	}

	delete residualGraph;
	return maxFlow;
	
}

/**
 * fordfulkerson: omputes Ford-Fulkerson Algorithm to obtain the Minimum Cut
 * by using the Min-Cut Max-Flow Theorem. Uses Adjacency Matrix data-structure 
 * for representng the graph.
 * 
 * \param graph represented by Adjacency Matrix data structure
 * 
 * \return Minimum Cut size for graph
 */
int fordfulkerson(AdjMatrix* graph) {
	int mincut = INT_MAX;
	int maxFlow = 0;

	for (int src = 0; src < graph->getV(); ++src) {
		for (int sink = graph->getV() - 1; sink > 0; --sink) {
			if (src != sink) {
				maxFlow = fordfulkerson(graph, src, sink);
			}

			if (maxFlow != 0) {
				mincut = min(mincut, maxFlow);
			}
		}
	}

	return mincut;
}

/**
 * fordfulkerson: Computes Ford-Fulkerson Algorithm to obtain Maximum Flow
 * between source and sink. Uses Adjacency List data-structure for representng
 * the graph
 * 
 * \param graph: represented by Adjacency List data structure
 * \param src: source of the flow
 * \param sink: sink of the flow
 * 
 * \return: maximum flow between src and sink
 */
int fordfulkerson(AdjList* graph, int src, int sink) {
	int u, v;

	AdjList* residualGraph = new AdjList(*graph);

	int parent[graph->getV()];

	int maxFlow = 0;

	while(hasMorePaths(residualGraph, src, sink, parent)) {
		int flow = INT_MAX;

		for (v = sink; v != src; v = parent[v]) {
			u = parent[v];
			flow = min(flow, residualGraph->isAdjacent(u, v)); 
		}

		for (v = sink; v != src; v = parent[v]) {
			u = parent[v];
			residualGraph->removeEdge(u, v);
		}

		maxFlow += flow;
	}
	
	delete residualGraph;
	return maxFlow;
}

/**
 * fordfulkerson: omputes Ford-Fulkerson Algorithm to obtain the Minimum Cut
 * by using the Min-Cut Max-Flow Theorem. Uses Adjacency List data-structure 
 * for representng the graph.
 * 
 * \param graph represented by Adjacency List data structure
 * 
 * \return Minimum Cut size for graph
 */
int fordfulkerson(AdjList* graph) {
	int mincut = INT_MAX;
	int maxFlow = 0;

	for (int src = 0; src < graph->getV(); ++src) {
		for (int sink = graph->getV() - 1; sink > 0; --sink) {
			if (src != sink) {
				maxFlow = fordfulkerson(graph, src, sink);
			}

			if (maxFlow != 0) {
				mincut = min(mincut, maxFlow);
			}
		}
	}

	return mincut;
}

/**
 * fordfulkerson: Computes Ford-Fulkerson Algorithm to obtain Maximum Flow
 * between source and sink. Uses CSR data-structure for representng the 
 * graph
 * 
 * \param graph: represented by CSR data structure
 * \param src: source of the flow
 * \param sink: sink of the flow
 * 
 * \return: maximum flow between src and sink
 */
int fordfulkerson(CSRGraph* graph, int src, int sink) {
	//int src = 0; // first vertice
	//int sink = graph->getV() - 1; // last vertice
	int u, v;
	graph->Print();

	CSRGraph* residualGraph = new CSRGraph(*graph);
	
	int parent[graph->getV()];

	int maxFlow = 0;

	while(hasMorePaths(residualGraph, src, sink, parent)) {
		int flow = INT_MAX;

		for (v = sink; v != src; v = parent[v]) {
			u = parent[v];

			flow = min(flow, residualGraph->isAdjacent(u, v)); 
		}

		for (v = sink; v != src; v = parent[v]) {
			u = parent[v];
			residualGraph->removeEdge(u, v);
		}

		maxFlow += flow;
	}

	delete residualGraph;
	return maxFlow;
}

/**
 * fordfulkerson: omputes Ford-Fulkerson Algorithm to obtain the Minimum Cut
 * by using the Min-Cut Max-Flow Theorem. Uses CSR data-structure for 
 * representng the graph.
 * 
 * \param graph represented by CSR data structure
 * 
 * \return Minimum Cut size for graph
 */
int fordfulkerson(CSRGraph* graph) {
	int mincut = INT_MAX;
	int maxFlow = 0;

	for (int src = 0; src < graph->getV(); ++src) {
		for (int sink = graph->getV() - 1; sink > 0; --sink) {
			if (src != sink) {
				maxFlow = fordfulkerson(graph, src, sink);
			}

			if (maxFlow != 0) {
				mincut = min(mincut, maxFlow);
			}
		}
	}

	return mincut;
}