#ifndef INTLIST_H
#define INTLIST_H

class IntList{
private:
    struct node{
        int value;
        node* next;
    };

    struct node* _head;
    struct node* _curr;
    struct node* _aux;

public:

    IntList();
    void addNode(int newNode) noexcept(false);
    int deleteNode(int old);
    void deleteAllNodes();
    int existsNode(int value);
    void mergeLists(IntList* updated);
    void printList();
    ~IntList();
};

#endif