/******************************************************************************
 *
 * File Name: intlist.hpp
 * Author:    Gonçalo Mestre & Pedro Reis
 * Last Modification: 24 May 2020
 *
 * NAME
 *  intlist - creation of the class for an integer list representation
 *
 * DESCRIPTION
 *  This file contains the declaration of the class of the integer list,
 * specifying what parts of this class should be public or private
 *
 *****************************************************************************/
#ifndef INTLIST_H
#define INTLIST_H

#include <list>

struct node{
    int value;
    node* next;
};


class IntList{
private:
    struct node* _head;
    struct node* _curr;
    struct node* _aux;

public:

    IntList();
    void addNode(int newNode) noexcept(false);
    int deleteNode(int old);
    int existsNode(int value);
    void printList();
    int findNodes(std::list<int>& j);
    ~IntList();
};

#endif