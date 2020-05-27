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

    if(array[m] <= val && array[m+1] > val)
        return m;
    if(array[m] > val)
        return binarySearch(val, array, start, m-1);
    return binarySearch(val, array, m+1, end);
}

double uwedgecsr(CSRGraph* csr){
    int totalwedges = 0;
    long long int sampsize = 1000;
    int r, index;
    struct wedge w;
    int *accwedgecount = (int*)malloc((csr->getV()+1)*sizeof(int));
    float ret;
    for(int v=0; v < csr->getV(); ++v){
        accwedgecount[v] = totalwedges;
        totalwedges = totalwedges + csr->degree(v)*(csr->degree(v)-1)/2;
    }
    accwedgecount[csr->getV()] = totalwedges;
    int sum = 0;
    for(int i=0; i < sampsize; ++i){
        r = RandomNumber(totalwedges);
        //std::cout << "rand:" << r << "\n";
        index = binarySearch(r, accwedgecount, 0, csr->getV());
        csr->RandomWedge(index, &w);
        sum = sum + csr->triangle(w.a, w.b, w.c);
    }
    std::cout << "SOMA: " << sum << "\n";
    ret = (double)totalwedges*(double)sum/(double)(3*sampsize);
    std::cout << "RET: " << ret << "\n";
    return ret;
}

/*int uwedgeadjm(AdjMatrix* adjm){
    int totalwedges = 0;
    long long int sampsize = 1000000;
    int r, index;
    struct wedge w;
    int *accwedgecount = (int*)malloc(adjm->getV()*sizeof(int));
    for(int v=0; v < adjm->getV(); ++v){
        accwedgecount[v] = totalwedges;
        totalwedges = totalwedges + adjm->degree(v)*(adjm->degree(v)-1)/2;
    }
    int sum = 0;
    for(int i=0; i < sampsize; ++i){
        r = RandomNumber(totalwedges);
        index = binarySearch(r, accwedgecount);
        adjm->RandomWedge(index, &w);
        sum = sum + adjm->triangle(w);
    }
    return sum/(3*sampsize);
}*/