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
#include <iterator>

typedef struct node{
    int value;
    node* next;
} node;


class IntList{
private:
    struct node* _head;
    struct node* _curr;
    struct node* _aux;
    struct node* _tail;

public:

    class IntListIterator : public std::iterator<std::forward_iterator_tag, node> {
        node* _pointed;
    public:
        IntListIterator(node* pointed);
        IntListIterator(const IntListIterator& other);
        IntListIterator& operator++();
        IntListIterator& operator++(int);
        bool operator==(const IntListIterator& other);
        bool operator!=(const IntListIterator& other);
        node* operator*();
    };

    IntList();
    IntList(const IntList& other);
    void addNode(int newNode) noexcept(false);
    int deleteNode(int old);
    int existsNode(int value);
    void printList();
    int findNodes(std::list<int>& j);
    IntListIterator begin() const;
    IntListIterator end() const;
    void copy(IntList* newList);
    ~IntList();
};

#endif