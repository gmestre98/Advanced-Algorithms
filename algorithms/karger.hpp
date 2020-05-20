#ifndef KARGER_H
#define KARGER_H

#include <stdlib.h>
#include <stdexcept>
#include <iostream>
#include <list>
#include <time.h>
#include "../data-structures/adj-matrix.hpp"
#include "../data-structures/adj-list.hpp"
#include "../data-structures/csr.hpp"

void printNestedList(std::list<std::list<int> >);
int contractadjm(AdjMatrix*);
void mergevertadjm(int*, std::list<std::list<int> >*, int, int, int, int, int, int);
int logarithm(int);
int kargeradjm(AdjMatrix*);

#endif