/******************************************************************************
 *
 * File Name: intlist.cpp
 * Author:    Gonçalo Mestre & Pedro Reis
 * Last Modification: 24 May 2020
 *
 * NAME
 *  intlist - creation of a class for an integer list representation
 *
 * DESCRIPTION
 *  This file contains the declaration of all functions used for the integer
 * list class
 *
 *****************************************************************************/
#include <cstdlib>
#include <iostream>
#include <exception>
#include <stdexcept>
#include "intlist.hpp"

/**
 *  IntList::IntList: Integer List constructor to initialize the integer list
 */
IntList::IntList() : _head(nullptr), _curr(nullptr), _aux(nullptr), _tail(nullptr) { }

IntList::IntList(const IntList& other) : _head(nullptr), _curr(nullptr), _aux(nullptr), _tail(nullptr) {
    for (IntListIterator it = other.begin(); it != other.end(); it++) {
        addNode((*it)->value);
    }
}

/**
 *  IntList::addNode: adds a new node to the integer list
 *
 *  \param newNode value for the node
 */
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
    }
    else{
        _head = a;
    }    
    _tail = a->next;
}

/**
 *  IntList::deleteNode: deletes a node on the integer list if it exists
 *
 *  \param old value of the node to delete
 */
int IntList::deleteNode(int old) {
    struct node* a = nullptr;
    _curr = _head;
    _aux = _head;
    while(_curr != nullptr && _curr->value != old){
        _aux = _curr;
        _curr = _curr->next;
    }

    if(_curr == nullptr){
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
        if (a == _tail) {
            _tail = _aux;
        }
        delete a;
        return 1;
    }
}

/**
 *  IntList::existsNode: verifies if a value exists on the list
 */
int IntList::existsNode(int value){
    _curr = _head;
    while(_curr != nullptr){
        if(_curr->value == value)
            return 1;
        _curr = _curr->next;
    }
    return 0;
}

/**
 *  IntList::printList: prints all nodes of the list
 */
void IntList::printList() {
    _curr = _head;
    std::cout << "(";
    while(_curr != nullptr){
        std::cout << _curr->value << ",";
        _curr = _curr->next;
    }
    std::cout << ")";
}

/**
 *  IntList::findNodes: returns one if the list has any value of the ones in a
 * given list
 *
 *  \param j list of integer values
 */
int IntList::findNodes(std::list<int>& j){
    std::list<int>::iterator it;
    it = j.begin();
    _curr = _head;
    while(_curr != nullptr){
        while(it != j.end() && *it < _curr->value)
            ++it;
        if(*it == _curr->value)
            return 1;
        _curr = _curr->next;
    }
    return 0;
}

IntList::IntListIterator IntList::begin() const { 
    return IntList::IntListIterator(_head);
}

IntList::IntListIterator IntList::end() const {
    return IntList::IntListIterator(_tail);
}

void IntList::copy(IntList* newList) {
    for (IntListIterator it = begin(); it != end(); it++) {
        newList->addNode((*it)->value);
    }
}

/**
 *  size: returns the size of a list
 */
int IntList::size(){
    int ret = 0;
    _curr = _head;
    while(_curr != nullptr){
        _curr = _curr->next;
        ret = ret + 1;
    }
    return ret;
}

/**
 *  IntList::getAdjacentX:
 *
 *  \param x the position of the adjacent in that list
 */
int IntList::getAdjacentX(int x){
    int count = 0;
    _curr = _head;
    while(_curr != nullptr && count != x){
        _curr = _curr->next;
        count = count + 1;
    }
    return _curr->value;
}

/**
 *  IntList::~IntList: integer list destructor to destroy the list
 */
IntList::~IntList() {
    _curr = _head;
    while(_curr != nullptr){
        _aux = _curr->next;
        delete _curr;
        _curr = _aux;
    }
    _head = nullptr;
}

IntList::IntListIterator::IntListIterator(node* pointed) : _pointed(pointed) { }

IntList::IntListIterator::IntListIterator(const IntListIterator& other) {
    _pointed = other._pointed;
}

IntList::IntListIterator& IntList::IntListIterator::operator++() {
    //_pointed = _pointed->next;
    node* aux = _pointed->next;
    _pointed = aux;
    return *this;
}

IntList::IntListIterator& IntList::IntListIterator::operator++(int) {
    /*IntListIterator tmp(*this);
    operator++();
    return tmp;*/
    node* aux = _pointed->next;
    _pointed = aux;
    return *this;
}

bool IntList::IntListIterator::operator==(const IntListIterator& other) {
    return (_pointed == other._pointed);
}

bool IntList::IntListIterator::operator!=(const IntListIterator& other) {
    return (_pointed != other._pointed);
}

node* IntList::IntListIterator::operator*() {
    return _pointed;
}