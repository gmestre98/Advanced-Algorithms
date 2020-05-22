#include <cmath>

#include "karger.hpp"

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


int contract(AdjMatrix* adj_matrix){
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
            //printNestedList(aux);
            mergevertadjm(mat, &aux, first, second, size, vert, i, j);
            /*printNestedList(aux);
            for (int a = 0; a < size; ++a) {
                for (int b = 0; b < size; ++b) {
                    std::cout << mat[a * size + b] << " ";
                }
                std::cout << std::endl;
            }*/
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
            if(adj_matrix->isAdjacent(*it1, *it2) == 1)
                ret = ret + 1;
        }
        
    }
    aux.erase(aux.begin(), aux.end());
    return ret;
}


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

// N dara so para mandar tudo la para dentro e depois seleciono que contract quero usar?
int karger(AdjMatrix* adj_matrix){
    int n = adj_matrix->getV();
    long long int nruns = n*n* (int) log2((double) n);
    int i = 0, result = 0, ret;
    while(i < nruns){
        i = i + 1;
        result = contract(adj_matrix);
        if(i==1 || result < ret)
            ret = result;
        std::cout << "ret is on: " << ret << "\n";
    }
    return ret;
}
