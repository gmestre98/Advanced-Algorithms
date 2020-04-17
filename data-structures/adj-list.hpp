#ifndef ADJ_LIST_H
#define ADJ_LIST_H

#include <stdlib.h>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <list>

class edge{
    int _pair, _weight;

public:
    edge(int pair, int weight){
        _pair = pair;
        _weight = weight;
    }
};


class AdjList {
    std::vector <std::list<edge> > _adjlist;
    int _size = 0;
public:

    AdjList();
    AdjList(int size) throw();
    void addEdge(int i, int j, int w) const throw ();
    void resize(int new_size) throw ();
    void print();

    ~AdjList();
};




#endif