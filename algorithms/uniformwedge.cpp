/******************************************************************************
 *
 * File Name: uniformwedge.cpp
 * Author:    Gonçalo Mestre & Pedro Reis
 * Last Modification: 26 May 2020
 *
 * NAME
 *  uniformedge - implementation of the uniform wedge algorithm to compute the
 * clustering coefficient
 *
 * DESCRIPTION
 *  This file contains the implementation of all functions used in the
 * implementation of the uniform wedge algorithm for the computation of the
 * clustering coefficient, being this done for three different graph representations
 *
 *****************************************************************************/

#include "uniformwedge.hpp"

/**
 *  RandomNumber: generates a random number from 0 to n-1
 *
 *  \param n number of possible numbers generated
 */
int RandomNumber(int n){
    int a = rand() % n;
    return a;
}

/**
 *  binarySearch: performs binary search for a value on an array
 *
 *  \param val the value being searched
 *  \param array 
 */
int binarySearch(int val, int* array, int start, int end){
    int m = start + ((end - start)/2);
    //std::cout << "m: " << m << "\narray[m]: " << array[m] << "\nstart: " << start << "\nend: " << end << "\n";
    if(array[m] <= val && array[m+1] > val)
        return m;
    if(array[m] > val)
        return binarySearch(val, array, start, m-1);
    return binarySearch(val, array, m+1, end);
}

/**
 *  uwedgecsr: calculates and returns the clustering coefficient of a csr
 * graph
 *
 *  \param csr the graph for which the clustering coefficient is computed
 */
double uwedgecsr(CSRGraph* csr){
    int totalwedges = 0;
    int r, index;
    struct wedge w;
    int *accwedgecount = (int*)malloc((csr->getV()+1)*sizeof(int));
    double ret;
    for(int v=0; v < csr->getV(); ++v){
        accwedgecount[v] = totalwedges;
        totalwedges = totalwedges + csr->degree(v)*(csr->degree(v)-1)/2;
    }
    accwedgecount[csr->getV()] = totalwedges;
    int sum = 0;
    for(int i=0; i < SAMPSIZE; ++i){
        r = RandomNumber(totalwedges);
        index = binarySearch(r, accwedgecount, 0, csr->getV());
        csr->RandomWedge(index, &w);
        sum = sum + csr->triangle(w.a, w.b, w.c);
    }
    ret = (double)totalwedges*(double)sum/(double)(3*SAMPSIZE);
    free(accwedgecount);
    return ret;
}

/**
 *  uwedgeadjm: calculates and returns the clustering coefficient of an
 * adjacency matrix graph
 *
 *  \param adjm the graph for which the clustering coefficient is computed
 */
double uwedgeadjm(AdjMatrix* adjm){
    int totalwedges = 0;
    int r, index, d;
    struct wedge w;
    int *accwedgecount = (int*)malloc((adjm->getV()+1)*sizeof(int));
    double ret;
    for(int v=0; v < adjm->getV(); ++v){
        accwedgecount[v] = totalwedges;
        d = adjm->degree(v);
        totalwedges = totalwedges + d*(d-1)/2;
    }
    accwedgecount[adjm->getV()] = totalwedges;
    int sum = 0;
    for(int i=0; i < SAMPSIZE; ++i){
        r = RandomNumber(totalwedges);
        index = binarySearch(r, accwedgecount, 0, adjm->getV());
        adjm->RandomWedge(index, &w);
        sum = sum + adjm->triangle(w.a, w.b, w.c);
    }
    ret = (double)totalwedges*(double)sum/(double)(3*SAMPSIZE);
    free(accwedgecount);
    return ret;
}

/**
 *  uwedgeadjl: calculates and returns the clustering coefficient of an
 * adjacency list graph
 *
 *  \param adjl the graph for which the clustering coefficient is computed
 */
double uwedgeadjl(AdjList* adjl){
    int totalwedges = 0;
    int r, index, d;
    struct wedge w;
    int *accwedgecount = (int*)malloc((adjl->getV()+1)*sizeof(int));
    double ret;
    for(int v=0; v < adjl->getV(); ++v){
        accwedgecount[v] = totalwedges;
        d = adjl->degree(v);
        totalwedges = totalwedges + d*(d-1)/2;
    }
    accwedgecount[adjl->getV()] = totalwedges;
    int sum = 0;
    for(int i=0; i < SAMPSIZE; ++i){
        r = RandomNumber(totalwedges);
        index = binarySearch(r, accwedgecount, 0, adjl->getV());
        adjl->RandomWedge(index, &w);
        sum = sum + adjl->triangle(w.a, w.b, w.c);
    }
    ret = (double)totalwedges*(double)sum/(double)(3*SAMPSIZE);
    free(accwedgecount);
    return ret;
}

/**
 *  uedgecsr: calculates and returns the clustering coefficient of a csr
 * graph
 *
 *  \param csr the graph for which the clustering coefficient is computed
 */
double uedgecsr(CSRGraph* csr){
    int s1estimate = 0;
    int r, index, d;
    struct wedge w;
    for(int i=0; i < SAMPSIZE; ++i){
        r = RandomNumber(csr->getV());
        if(csr->degree(r) == 1)
            s1estimate = s1estimate + 1;
    }
    s1estimate = csr->getV()*s1estimate/SAMPSIZE;
    int sum = 0;
    for(int i=0; i < SAMPSIZE; ++i){
        do{
            r = RandomNumber(2*(csr->getE()));
            index = csr->SearchEdge(r, 0, csr->getV());
            d = csr->degree(index);
        }while(d <= 1);
        csr->RandomWedge(index, &w);
        sum = sum + csr->triangle(w.a, w.b, w.c)*(d-1);
    }
    double ret = (2*((double)csr->getE()) - (double)s1estimate)*(double)sum/(6*(double)SAMPSIZE);
    return ret;
}

/**
 *  uedgeadjm: calculates and returns the clustering coefficient of an
 * adjacency matrix graph
 *
 *  \param adjm the graph for which the clustering coefficient is computed
 */
double uedgeadjm(AdjMatrix* adjm){
    int totaledges = 0;
    int s1estimate = 0;
    int r, index, d;
    struct wedge w;
    int *accedgecount = (int*)malloc((adjm->getV()+1)*sizeof(int));
    for(int v=0; v < adjm->getV(); ++v){
        accedgecount[v] = totaledges;
        totaledges = totaledges + adjm->degree(v);
    }
    accedgecount[adjm->getV()] = totaledges; 
    for(int i=0; i < SAMPSIZE; ++i){
        r = RandomNumber(adjm->getV());
        if(adjm->degree(r) == 1)
            s1estimate = s1estimate + 1;
    }
    s1estimate = adjm->getV()*s1estimate/SAMPSIZE;
    int sum = 0;
    for(int i=0; i < SAMPSIZE; ++i){
        do{
            r = RandomNumber(2*(adjm->getE()));
            index = binarySearch(r, accedgecount, 0, adjm->getV());
            d = adjm->degree(index);
        }while(d <= 1);
        adjm->RandomWedge(index, &w);
        sum = sum + adjm->triangle(w.a, w.b, w.c)*(d-1);
    }
    double ret = (2*((double)adjm->getE()) - (double)s1estimate)*(double)sum/(6*(double)SAMPSIZE);
    free(accedgecount);
    return ret;
}

/**
 *  uedgeadjl: calculates and returns the clustering coefficient of an
 * adjacency list graph
 *
 *  \param adjl the graph for which the clustering coefficient is computed
 */
double uedgeadjl(AdjList* adjl){
    int totaledges = 0;
    int s1estimate = 0;
    int r, index, d;
    struct wedge w;
    int *accedgecount = (int*)malloc((adjl->getV()+1)*sizeof(int));
    for(int v=0; v < adjl->getV(); ++v){
        accedgecount[v] = totaledges;
        totaledges = totaledges + adjl->degree(v);
    }
    accedgecount[adjl->getV()] = totaledges; 
    for(int i=0; i < SAMPSIZE; ++i){
        r = RandomNumber(adjl->getV());
        if(adjl->degree(r) == 1)
            s1estimate = s1estimate + 1;
    }
    s1estimate = adjl->getV()*s1estimate/SAMPSIZE;
    int sum = 0;
    for(int i=0; i < SAMPSIZE; ++i){
        do{
            r = RandomNumber(2*(adjl->getE()));
            index = binarySearch(r, accedgecount, 0, adjl->getV());
            d = adjl->degree(index);
        }while(d <= 1);
        adjl->RandomWedge(index, &w);
        sum = sum + adjl->triangle(w.a, w.b, w.c)*(d-1);
    }
    double ret = (2*((double)adjl->getE()) - (double)s1estimate)*(double)sum/(6*(double)SAMPSIZE);
    free(accedgecount);
    return ret;
}

/**
 *  uvertexcsr: calculates and returns the clustering coefficient of a csr
 * graph
 *
 *  \param csr the graph for which the clustering coefficient is computed
 */
double uvertexcsr(CSRGraph* csr){
    int s1estimate = 0;
    int r, index, d;
    struct wedge w;
    for(int i=0; i < SAMPSIZE; ++i){
        r = RandomNumber(csr->getV());
        if(csr->degree(r) == 1 || csr->degree(r) == 0)
            s1estimate = s1estimate + 1;
    }
    s1estimate = csr->getV()*s1estimate/SAMPSIZE;
    int sum = 0;
    for(int i=0; i < SAMPSIZE; ++i){
        do{
            index = RandomNumber(csr->getV());
            d = csr->degree(index);
        }while(d <= 1);
        csr->RandomWedge(index, &w);
        sum = sum + csr->triangle(w.a, w.b, w.c)*d*(d-1)/2;
    }
    double ret = ((double)csr->getV() - (double)s1estimate)*(double)sum/(3*(double)SAMPSIZE);
    return ret;
}
/**
 *  uvertexadjm: calculates and returns the clustering coefficient of an
 * adjacency matrix graph
 *
 *  \param adjm the graph for which the clustering coefficient is computed
 */
double uvertexadjm(AdjMatrix* adjm){
    int totaledges = 0;
    int s1estimate = 0;
    int r, index, d;
    struct wedge w;
    for(int i=0; i < SAMPSIZE; ++i){
        r = RandomNumber(adjm->getV());
        if(adjm->degree(r) == 1)
            s1estimate = s1estimate + 1;
    }
    s1estimate = adjm->getV()*s1estimate/SAMPSIZE;
    int sum = 0;
    for(int i=0; i < SAMPSIZE; ++i){
        do{
            index = RandomNumber(adjm->getV());
            d = adjm->degree(index);
        }while(d <= 1);
        adjm->RandomWedge(index, &w);
        sum = sum + adjm->triangle(w.a, w.b, w.c)*(d-1)*d/2;
    }
    double ret = ((double)adjm->getV() - (double)s1estimate)*(double)sum/(3*(double)SAMPSIZE);
    return ret;
}

/**
 *  uvertexadjl: calculates and returns the clustering coefficient of an
 * adjacency list graph
 *
 *  \param adjl the graph for which the clustering coefficient is computed
 */
double uvertexadjl(AdjList* adjl){
    int totaledges = 0;
    int s1estimate = 0;
    int r, index, d;
    struct wedge w;
    for(int i=0; i < SAMPSIZE; ++i){
        r = RandomNumber(adjl->getV());
        if(adjl->degree(r) == 1)
            s1estimate = s1estimate + 1;
    }
    s1estimate = adjl->getV()*s1estimate/SAMPSIZE;
    int sum = 0;
    for(int i=0; i < SAMPSIZE; ++i){
        do{
            index = RandomNumber(adjl->getV());
            d = adjl->degree(index);
        }while(d <= 1);
        adjl->RandomWedge(index, &w);
        sum = sum + adjl->triangle(w.a, w.b, w.c)*(d-1)*d/2;
    }
    double ret = ((double)adjl->getV() - (double)s1estimate)*(double)sum/(3*(double)SAMPSIZE);
    return ret;
}