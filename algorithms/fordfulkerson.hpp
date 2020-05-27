#ifndef FORDFULKERSON_H
#define FORDFULKERSON_H

#include <climits>
#include <functional>
#include <stdio.h>
#include <queue>
#include <cstring>

#include "../data-structures/adj-matrix.hpp"
#include "../data-structures/adj-list.hpp"
#include "../data-structures/csr.hpp"

int fordfulkerson(AdjMatrix* graph);
//int fordfulkerson(AdjList* graph);
//int fordfulkerson(CSRGraph* graph);

#endif