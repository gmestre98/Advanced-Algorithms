/******************************************************************************
 *
 * File Name: graph.hpp
 * Author:    Gonçalo Mestre & Pedro Reis
 * Last Modification: 24 May 2020
 *
 * NAME
 *  graph - creation of the object graph for the other graph representations to
 * inherit
 *
 * DESCRIPTION
 *  This file contains the declaration of the object of the graph and general
 * object functions for the graph representations
 *
 *****************************************************************************/
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>

struct wedge{
    int a;
    int b;
    int c;
};

class Graph{
    int v, e;
public:
    Graph(){}
    void setV (int newv){
        v = newv;
    }
    void setE (int newe){
        e = newe;
    }
    void incV (){
        ++v;
    }
    void incE (){
        ++e;
    }
    void decV (){
        --v;
    }
    void decE () {
        --e;
    }
    int getV () const {
        return v;
    }
    int getE () const {
        return e;
    }

    virtual bool isAdjacent(int i, int j) = 0;
};

#endif