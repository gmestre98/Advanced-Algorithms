#include <iostream>
#include <fstream>
#include <dirent.h>
#include <sys/types.h>

#include "graph-loader.hpp"

#define GENERATED_GRAPHS_PATH "generated_graphs/gn_random_graphs"

GraphLoader::GraphLoader() noexcept(false) : _currentFileIndex(0) {
	_fileNames = std::vector<std::string>();

	struct dirent* entry;
	DIR* dir = opendir(GENERATED_GRAPHS_PATH);

	if (dir == nullptr) {
		throw std::domain_error("Expected diretory \"generated_graphs/gn_random_graphs\" to exist, but it does not! :(");
	}

	while ((entry = readdir(dir)) != nullptr)  {
		std::string fileName = entry->d_name;

		if (fileName != "." && fileName != "..") {
			_fileNames.push_back(entry->d_name);
		}
	}

	closedir(dir);
}

AdjMatrix* GraphLoader::loadNextGraphAsAdjMatrix() {
	if (_currentFileIndex >= _fileNames.size()) {
		throw std::out_of_range("There are no graphs to load!");
	}

	std::ifstream file(((std::string) GENERATED_GRAPHS_PATH) + "/" + _fileNames[_currentFileIndex++]);
	
	int numberOfNodes;
	file >> numberOfNodes;

	AdjMatrix* matrix = new AdjMatrix(numberOfNodes);

	if (file.is_open()) {
		while (!file.eof()) {
			int i, j;
			file >> i >> j;
			matrix->addEdge(i, j);
		}

		file.close();	
	} else {
		std::cerr << "Cannot open the file" << std::endl;
	}

	return matrix;
}

AdjList* GraphLoader::loadNextGraphAsAdjList() {
	if (_currentFileIndex >= _fileNames.size()) {
		throw std::out_of_range("There are no graphs to load!");
	}

	std::ifstream file(((std::string) GENERATED_GRAPHS_PATH) + "/" + _fileNames[_currentFileIndex++]);

	int numberOfNodes;
	file >> numberOfNodes;

	AdjList* adjList = new AdjList(numberOfNodes);

	if (file.is_open()) {
		while (!file.eof()) {
			int i, j;
			file >> i >> j;
			adjList->addEdge(i, j);
		}

		file.close();	
	} else {
		std::cerr << "Cannot open the file" << std::endl;
	}

	return adjList;
}

CSRGraph* GraphLoader::loadNextGraphAsCSR() {
	if (_currentFileIndex >= _fileNames.size()) {
		throw std::out_of_range("There are no graphs to load!");
	}

	AdjMatrix* adjMatrix = loadNextGraphAsAdjMatrix();

	CSRGraph* csr = new CSRGraph(adjMatrix->getV());
	csr->ReadGraph(adjMatrix);
	
	return csr;
}

GraphLoader::~GraphLoader() {
	delete _fileNames;
}