#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>

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
    void decE (){
        --e;
    }
    int getV (){
        return v;
    }
    int getE (){
        return e;
    }
};


#endif