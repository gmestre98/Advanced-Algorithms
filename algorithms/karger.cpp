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
void printNestedList(std::list<std::list<int> > nested_list) 
{ 
    std::cout << "[\n";
  
    // nested_list`s iterator(same type as nested_list) 
    // to iterate the nested_list 
    std::list<std::list<int> >::iterator nested_list_itr; 
  
    // Print the nested_list 
    for (nested_list_itr = nested_list.begin(); 
         nested_list_itr != nested_list.end(); 
         ++nested_list_itr) { 
  
        std::cout << "  ["; 
  
        // normal_list`s iterator(same type as temp_list) 
        // to iterate the normal_list 
        std::list<int>::iterator single_list_itr; 
  
        // pointer of each list one by one in nested list 
        // as loop goes on 
        std::list<int>& single_list_pointer = *nested_list_itr; 
  
        for (single_list_itr = single_list_pointer.begin(); 
             single_list_itr != single_list_pointer.end(); 
             single_list_itr++) { 
            std::cout << " " << *single_list_itr << " "; 
        } 
        std::cout << "]\n"; 
    } 
    std::cout << "]"; 
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
 *  createauxlist: creates an auxiliary list of integer lists with size lists,
 * also fills the first node of each list with the number of the list
 *
 * \param size number of integer lists to create
 */
void createauxlist(int size){
    std::list<int> single_list;
    for(int a=0; a < size; ++a){
        single_list.push_back(a);
        aux.push_back(single_list);
        single_list.erase(single_list.begin(), single_list.end());
    }
}

/**
 *  generatetworandom: generates two different random numbers
 *
 *  \param i the first random number
 *  \param j the second random number
 *  \param n the possible range of the generated numbers, from 0 to n-1
 */
void generatetworandom(int* i, int* j, int n){
    *i = rand() % n;
    do{
        *j = rand() % n;
    }while(*i == *j);
}

/**
 *  getlist: returns pointer to integer list j of the nested list
 *
 *  \param j the list number of the list being returned
 */
std::list<int>& getlist(int j){
    std::list<std::list<int> >::iterator it;
    it = aux.begin();
    advance(it, j);
    return *it;
}

/**
 *  joinsets: Joins two sets of nodes
 *
 *  \param i first set of nodes number
 *  \param j second set of nodes number
 */
void joinsets(int i, int j){
    std::list<std::list<int>>::iterator it1;
    std::list<std::list<int>>::iterator it2;
    int min, max;
    if(i > j){
        min = j;
        max = i;
    }
    it1 = aux.begin();
    advance(it1, i);
    it2 = aux.begin();
    advance(it2, j);
    (*it1).merge(*it2);
    aux.erase(it2);
}

/**
 *  countedgescsr: returns the count of edges on a given cut
 * 
 *  \param csr graph representation for which the size of min cut is being computed
 */
int countedgescsr(CSRGraph* csr){
    int ret=0;
    std::list<std::list<int>>::iterator it;
    std::list<int>::iterator it1, it2;
    for(it1 = (*(aux.begin())).begin(); it1 != (*(aux.begin())).end(); ++it1){
        it = aux.begin();
        advance(it, 1);
        for(it2 = (*it).begin(); it2 != (*it).end(); ++it2){
            if(csr->isAdjacent(*it1, *it2) == 1)
                ret = ret + 1;
        }
    }
    return ret;
}


/**
 *  contractcsr: implementation of karger's contraction algorithm for a csr and
 * computation of the mincut size
 *
 *  \param csr graph to contract and obtain the mincut size
 */
int contractcsr(CSRGraph* csr){
    int i, j;
    int vert = csr->getV();
    int size = vert;
    int ret;
    createauxlist(size);
    while(vert > 2){
        generatetworandom(&i, &j, vert);
        std::list<int>::iterator it;
        std::list<int>& ilist = getlist(i);
        for(it = ilist.begin(); it != ilist.end(); ++it){
            if(csr->findAdjacent(*it, getlist(j))){
                joinsets(i, j);
                vert = vert - 1;
                break;
            }
        }
    }
    ret = countedgescsr(csr);
    aux.erase(aux.begin(), aux.end());
    return ret;
}

/**
 *  kargercsr: applies the contraction algorithm the necessary number of
 * times to obtain a correct size of the minimum cut with certainty
 *
 *  \param csr graph for which the size of the minimum cut is being computed
 */
int kargercsr(CSRGraph* csr){
    int n = csr->getV();
    long long int nruns = n*n*logarithm(n);
    int i = 0;
    int result = 0;
    int ret;
    while(i < nruns){
        i = i + 1;
        result = contractcsr(csr);
        if(i==1 || result < ret)
            ret = result;
        //std::cout << "\nret is on: " << ret << "\n";
    }
    return ret;
}

/**
 *  countedgesadjm: returns the count of edges on a given cut
 * 
 *  \param adj_matrix graph representation for which the size of min cut is being computed
 */
int countedgesadjm(AdjMatrix* adj_matrix){
    int ret=0;
    std::list<std::list<int>>::iterator it;
    std::list<int>::iterator it1, it2;
    for(it1 = (*(aux.begin())).begin(); it1 != (*(aux.begin())).end(); ++it1){
        it = aux.begin();
        advance(it, 1);
        for(it2 = (*it).begin(); it2 != (*it).end(); ++it2){
            if(adj_matrix->isAdjacent(*it1, *it2) == 1)
                ret = ret + 1;
        }
    }
    return ret;
}

/**
 *  contractadjm: implementation of karger's contraction algorithm for a csr and
 * computation of the mincut size
 *
 *  \param adj_matrix graph to contract and obtain the mincut size
 */
int contractadjm(AdjMatrix* adj_matrix){
    int i, j;
    int vert = adj_matrix->getV();
    int size = vert;
    int ret;
    AdjMatrix* copy = new AdjMatrix(adj_matrix->getV());
    copy->Copyadjm(adj_matrix);
    createauxlist(size);
    while(vert > 2){
        generatetworandom(&i, &j, vert);
        std::list<int>& ilist = getlist(i);
        std::list<int>& jlist = getlist(j);
        if(copy->isAdjacent(*(ilist.begin()), *(jlist.begin()))){
            copy->ContractEdge(*(ilist.begin()), *(jlist.begin()));
            joinsets(i, j);
            vert = vert - 1;
        }
    }
    delete copy;
    ret = countedgesadjm(adj_matrix);
    aux.erase(aux.begin(), aux.end());
    return ret;
}

/**
 *  kargeradjm: applies the contraction algorithm the necessary number of
 * times to obtain a correct size of the minimum cut with certainty
 *
 *  \param adj_matrix graph for which the size of the minimum cut is being
 * computed
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
        //std::cout << "\nret is on: " << ret << "\n";
    }
    return ret;
}

/**
 *  countedgesadjl: returns the count of edges on a given cut
 * 
 *  \param adj_list graph representation for which the size of min cut is being computed
 */
int countedgesadjl(AdjList* adj_list){
    int ret=0;
    std::list<std::list<int>>::iterator it;
    std::list<int>::iterator it1, it2;
    for(it1 = (*(aux.begin())).begin(); it1 != (*(aux.begin())).end(); ++it1){
        it = aux.begin();
        advance(it, 1);
        for(it2 = (*it).begin(); it2 != (*it).end(); ++it2){
            if(adj_list->isAdjacent(*it1, *it2) == 1)
                ret = ret + 1;
        }
    }
    return ret;
}

/**
 *  contractadjl: implementation of karger's contraction algorithm for a csr and
 * computation of the mincut size
 *
 *  \param adj_list graph to contract and obtain the mincut size
 */
int contractadjl(AdjList* adj_list){
    int i, j;
    int vert = adj_list->getV();
    int size = vert;
    int ret;
    createauxlist(size);
    while(vert > 2){
        generatetworandom(&i, &j, vert);
        std::list<int>::iterator it;
        std::list<int>& ilist = getlist(i);
        for(it = ilist.begin(); it != ilist.end(); ++it){
            if(adj_list->findAdjacent(*it, getlist(j))){
                joinsets(i, j);
                vert = vert - 1;
                break;
            }
        }
    }
    ret = countedgesadjl(adj_list);
    aux.erase(aux.begin(), aux.end());
    return ret;
}

/**
 *  kargeradjl: applies the contraction algorithm the necessary number of
 * times to obtain a correct size of the minimum cut with certainty
 *
 *  \param adj_list graph for which the size of the minimum cut is being
 * computed
 */
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
        //std::cout << "\nret is on: " << ret << "\n";
    }
    return ret;
}