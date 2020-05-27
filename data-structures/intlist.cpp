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
IntList::IntList() : _head(nullptr), _curr(nullptr), _aux(nullptr) { }

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





































///// FUNÇOES QUE DEPOIS TIVE DE CAGAR, PODEM SER UTEIS, ANTES DA ENTREGA APAGAMOS



/**
 *  IntList::deleteAllNodes: deletes all nodes of the list
 *
void IntList::deleteAllNodes(){
    _curr = _head;
    while(_curr != nullptr){
        _aux = _curr->next;
        delete _curr;
        _curr = _aux;
    }
    _head = nullptr;
}



/**
 *  IntList::CopyList: copies all nodes of the current list to a given list
 *
 *  \param newlist list where the nodes are being inserted
 *
void IntList::CopyList(IntList* newlist){
    _curr = _head;
    while(_curr != nullptr){
        newlist->addNode(_curr->value);
        _curr = _curr->next;
    }
}

/**
 *  IntList::returnHead: returns the head of the list
 *
struct node* IntList::returnHead(){
    return _head;
}

/**
 *  IntList::MergeListWith: moves all nodes of a given list that are not on the current
 * one to it
 *
 *  \param oldlist
 *
void IntList::MergeListWith(IntList* oldlist){
    struct node* curroldlist = newlist->returnHead();
    _curr = _head;
    struct node dummy;
    struct node* tail = &dummy;
    struct node* aux;
    dummy.next = nullptr;

    while(1){
        if(_curr == nullptr){
            tail->next = curroldlist;
            break;
        }
        else if(curroldlist == nullptr){
            tail->next = _curr;
            break;
        }

        if(curr->value < curroldlist->value){
            tail->next = curr;
            tail = curr;
            curr = curr->next;
            tail->next = nullptr;
        }
        else if(curr->value == curroldlist->value){
            aux = curroldlist;
            curroldlist = curroldlist->next;
            delete aux;
        }
        else{
            tail->next = curroldlist;
            tail = curroldlist;
            curroldlist = curroldlist->next;
            tail->next = nullptr;
            movenode(&tainext, &a);
        }
    }
    _head = dummy->next;
    //set old head to null
}*/