#include <cstdlib>
#include <iostream>
#include <exception>
#include <stdexcept>
#include "intlist.hpp"

IntList::IntList() : _head(nullptr), _curr(nullptr), _aux(nullptr) { }

void IntList::addNode(int newNode) noexcept(false) {
    struct node* a = new node;
    a->next = nullptr;
    a->value = newNode;

    if(_head != nullptr){
        _curr = _head;
        while(_curr->next != nullptr && _curr->value != newNode)
            _curr = _curr->next;
        if(_curr->value != newNode){
            _curr->next = a;
        }
        else{
            throw std::domain_error("That node already existed, why are you adding it? You dumb?");
        }
    }
    else{
        _head = a;
    }
}

int IntList::deleteNode(int old) {
    struct node* a = nullptr;
    _curr = _head;
    _aux = _head;
    while(_curr != nullptr && _curr->value != old){
        _aux = _curr;
        _curr = _curr->next;
    }

    if(_curr == nullptr){
        free(a);
        return 0;
    }
    else{
        a = _curr;
        _curr = _curr->next;
        _aux->next = _curr;
        if(a == _head){
            _head = _head->next;
            _aux = nullptr;
        }
        delete a;
        return 1;
    }
}

void IntList::printList() {
    _curr = _head;
    std::cout << "(";
    while(_curr != nullptr){
        std::cout << _curr->value << ",";
        _curr = _curr->next;
    }
    std::cout << ")";
}

IntList::~IntList() {
    _curr = _head;
    while(_curr != nullptr){
        _aux = _curr->next;
        delete _curr;
        _curr = _aux;
    }
    _head = nullptr;
}