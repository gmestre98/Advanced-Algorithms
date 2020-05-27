#include "fordfulkerson.hpp"

std::function<int (int, int)> min = [](int a, int b) { return (a < b) ? a : b; };

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

int fordfulkerson(AdjMatrix* graph) {
	int src = 0; // first vertice
	int sink = graph->getV() - 1; // last vertice
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

int fordfulkerson(AdjList* graph) {
	int src = 0; // first vertice
	int sink = graph->getV() - 1; // last vertice
	int u, v;

	AdjList* resiudalGraph = new AdjList(*graph);
	resiudalGraph->addEdge(0, 5);

	graph->Print();
	resiudalGraph->Print();
	delete resiudalGraph;
	return 0;
}