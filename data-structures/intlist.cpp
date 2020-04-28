#include <cstdlib>
#include <iostream>

#include "intlist.hpp"

intlist::intlist() {
    head = NULL;
    curr = NULL;
    aux = NULL;
}

int intlist::AddNode(int _new) {
    struct node* a = new node;
    a->next = NULL;
    a->value = _new;

    if(head != NULL){
        curr = head;
        while(curr->next != NULL && curr->value != _new)
            curr = curr->next;
        if(curr->value != _new){
            curr->next = a;
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        head = a;
        return 1;
    }
}

int intlist::DeleteNode(int _old) {
    struct node* a = NULL;
    curr = head;
    aux = head;
    while(curr != NULL && curr->value != _old){
        aux = curr;
        curr = curr->next;
    }
    if(curr == NULL){
        free(a);
        return 0;
    }
    else{
        a = curr;
        curr = curr->next;
        aux->next = curr;
        if(a == head){
            head = head->next;
            aux = NULL;
        }
        delete a;
        return 1;
    }
}

void intlist::PrintList() {
    curr = head;
    std::cout << "(";
    while(curr != NULL){
        std::cout << curr->value << ",";
        curr = curr->next;
    }
    std::cout << ")";
}

intlist::~intlist() {
    curr = head;
    while(curr != NULL){
        aux = curr->next;
        delete curr;
        curr = aux;
    }
    head = NULL;
}