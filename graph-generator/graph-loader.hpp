#ifndef GRAPH_LOADER_H
#define GRAPH_LOADER_H

#include <vector>
#include <string>
#include <type_traits>
#include <fstream>
#include <dirent.h>

#include "../data-structures/adj-matrix.hpp"
#include "../data-structures/adj-list.hpp"
#include "../data-structures/csr.hpp"

#define GENERATED_GRAPHS_PATH "generated_graphs/gn_random_graphs"

class GraphLoader {
	std::vector<std::string> _fileNames;
	long unsigned int _currentFileIndex;
public:
	GraphLoader() noexcept(false);
	AdjMatrix* loadNextGraphAsAdjMatrix();
	AdjList* loadNextGraphAsAdjList();
	CSRGraph* loadNextGraphAsCSR();
	bool hasMoreGraphs() { return _currentFileIndex < _fileNames.size(); }
	~GraphLoader();
};

#endif