/******************************************************************************
 *
 * File Name: karger.cpp
 * Author:    Gonçalo Mestre & Pedro Reis
 * Last Modification: 21 May 2020
 *
 * NAME
 *  karger - functions used to implement karger's algorithm
 *
 * DESCRIPTION
 *  This file contains the implementation of all functions used in the
 * implementation of karger's algorithm for the computation of the minimum cut
 * size, being this done for three different graph representations
 *
 *****************************************************************************/
#include "karger.hpp"

std::list<std::list<int>> aux;

/**
 * printNestedList: Function to print the used nested_lists
 * 
 * \param nested_list list to print
 * APAGAR ISTO ANTES DA ENTREGA
 */
using namespace std;
void printNestedList(list<list<int> > nested_list) 
{ 
    cout << "[\n";
  
    // nested_list`s iterator(same type as nested_list) 
    // to iterate the nested_list 
    list<list<int> >::iterator nested_list_itr; 
  
    // Print the nested_list 
    for (nested_list_itr = nested_list.begin(); 
         nested_list_itr != nested_list.end(); 
         ++nested_list_itr) { 
  
        cout << "  ["; 
  
        // normal_list`s iterator(same type as temp_list) 
        // to iterate the normal_list 
        list<int>::iterator single_list_itr; 
  
        // pointer of each list one by one in nested list 
        // as loop goes on 
        list<int>& single_list_pointer = *nested_list_itr; 
  
        for (single_list_itr = single_list_pointer.begin(); 
             single_list_itr != single_list_pointer.end(); 
             single_list_itr++) { 
            cout << " " << *single_list_itr << " "; 
        } 
        cout << "]\n"; 
    } 
    cout << "]"; 
} 


/**
 * contractadjm - Implementation of the contraction algorithm for an adjacency matrix
 *
 * \param adj_matrix graph for which the algorithm is being implemented
 */
int contractadjm(AdjMatrix* adj_matrix){
    int i, j, first, second;
    int vert = adj_matrix->getV();
    int size = vert;
    int ret = 0;
    int* mat = adj_matrix->copymtoint();
    std::list<std::list<int> > aux;
    std::list<int> single_list;
    std::list<std::list<int>>::iterator it;
    for(int a=0; a < size; ++a){
        single_list.push_back(a);
        aux.push_back(single_list);
        single_list.erase(single_list.begin(), single_list.end());
    }
    //Finding the minimum cut
    while(vert > 2){
        i = rand() % vert;
        do{
            j = rand() % vert;
        }while(j == i);
        it = aux.begin();
        advance(it, i);
        first = *((*it).begin());
        it = aux.begin();
        advance(it, j);
        second = *((*it).begin());
        if(mat[first * size + second] > 0){
            mat[first * size + second] = 0;
            mat[second * size + first] = 0;
            mergevertadjm(mat, &aux, first, second, size, vert, i, j);
            vert = vert - 1;
        }
    }
    //Minimum cut size computation
    std::list<int>::iterator it1, it2;
    for(it1 = (*(aux.begin())).begin(); it1 != (*(aux.begin())).end(); ++it1){
        it = aux.begin();
        advance(it, 1);
        for(it2 = (*it).begin(); it2 != (*it).end(); ++it2){
            if(adj_matrix->isAdjacent(*it1, *it2) == 1)
                ret = ret + 1;
        }
        
    }
    aux.erase(aux.begin(), aux.end());
    free(mat);
    return ret;
}

/**
 * mergevertadjm: Merges two graphs of a graph represented with an adjacency matrix
 *
 * \param mat matrix representing the graph
 * \param aux auxiliary list representing the obtained sets list
 * \param min first vertex of the edge being contracted, set position on the matrix
 * \param max second vertex of the edge being contracted, set position on the matrix
 * \param size number of vertices of the original graph
 * \param vert number of vertices of the current graph
 * \param i first vertex of the edge being contracted on the current graph
 * \param j second vertex of the edge being contracted on the current graph
 */
void mergevertadjm(int* mat, std::list<std::list<int> > *aux, int min, int max, int size, int vert, int i, int j){
    std::list<std::list<int>>::iterator it1;
    std::list<std::list<int>>::iterator it2;
    int ajuda;

    if(i > j){
        ajuda = i;
        i = j;
        j = ajuda;
    }
    if(min > max){
        ajuda = min;
        min = max;
        max = ajuda;
    }
    for(int k=0; k < size; ++k){
        mat[min * size + k] = mat[min * size + k] + mat[max * size + k];
        mat[max * size + k] = 0;
    }
    for(int k=0; k < size; ++k){
        mat[k * size + min] = mat[k * size + min] + mat[k * size + max];
        mat[k * size + max] = 0;
    }
    it1 = (*aux).begin();
    advance(it1, i);
    it2 = (*aux).begin();
    advance(it2, j);
    (*it1).merge(*it2);
    (*aux).erase(it2);
}

/**
 * logarithm: Returns the rounded up value of a number's logarithm
 *
 * \param n the number for which the logarithm is being computed
 */
int logarithm(int n){
    int i = 1;
    int ret = 0;
    while(i < n){
        i = i*2;
        ret = ret + 1;
    }
    return ret;
}

/**
 * kargeradjm: Executes karger's contraction algorithm the necessary number of
 * times to compute the minimum cut for the graph represented with an adjacency
 * matrix
 *
 * \param adj_matrix adjacency matrix for which the algorithm is being computed
 */
int kargeradjm(AdjMatrix* adj_matrix){
    int n = adj_matrix->getV();
    long long int nruns = n*n*logarithm(n);
    int i = 0;
    int result = 0;
    int ret;
    while(i < nruns){
        i = i + 1;
        result = contractadjm(adj_matrix);
        if(i==1 || result < ret)
            ret = result;
        std::cout << "ret is on: " << ret << "\n";
    }
    return ret;
}


/**
 *
 */
int contractadjl(AdjList* adj_list){
    int i, j;
    int vert = adj_list->getV();
    int size = vert;
    int ret = 0;
    IntList* adjl = new IntList[adj_list->getV()];
    adj_list->copyadjlist(adjl);
    std::list<std::list<int> > aux;
    std::list<int> single_list;
    std::list<std::list<int>>::iterator it;
    for(int a=0; a < size; ++a){
        single_list.push_back(a);
        aux.push_back(single_list);
        single_list.erase(single_list.begin(), single_list.end());
    }
    while(vert > 2){
        i = rand() % vert;
        do{
            j = rand() % vert;
        }while(j == i);
        if(adjl[i].existsNode(j)){
            adjl[i].deleteNode(j);
            adjl[j].deleteNode(i);
            mergevertadjl(adjl, &aux, i, j, size, vert);
            vert = vert - 1;
        }
        else{
            continue;
        }
    }
    std::list<int>::iterator it1, it2;
    for(it1 = (*(aux.begin())).begin(); it1 != (*(aux.begin())).end(); ++it1){
        it = aux.begin();
        advance(it, 1);
        for(it2 = (*it).begin(); it2 != (*it).end(); ++it2){
            if(adj_list->isAdjacent(*it1, *it2) == 1)
                ret = ret + 1;
        }
        
    }
    aux.erase(aux.begin(), aux.end());
    delete[] adjl;
    return ret;
}

void mergevertadjl(IntList* adjl, std::list<std::list<int> > *aux, int i, int j, int size, int vert){
    std::list<std::list<int>>::iterator it1;
    std::list<std::list<int>>::iterator it2;
    int ajuda;

    if(i > j){
        ajuda = i;
        i = j;
        j = ajuda;
    }
    adjl[j].mergeLists(&adjl[i]);
    adjl[j].deleteAllNodes();
    it1 = (*aux).begin();
    advance(it1, i);
    it2 = (*aux).begin();
    advance(it2, j);
    (*it1).merge(*it2);
    (*aux).erase(it2);
}



int kargeradjl(AdjList* adj_list){
    int n = adj_list->getV();
    long long int nruns = n*n*logarithm(n);
    int i = 0;
    int result = 0;
    int ret;
    while(i < nruns){
        i = i + 1;
        result = contractadjl(adj_list);
        if(i==1 || result < ret)
            ret = result;
        std::cout << "\nret is on: " << ret << "\n";
    }
    return ret;
}