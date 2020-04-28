#ifndef INTLIST_H
#define INTLIST_H

class intlist{
private:
    struct node{
        int value;
        node* next;
    };

    struct node* head;
    struct node* curr;
    struct node* aux;
public:

    intlist();
    int AddNode(int _new);
    int DeleteNode(int _old);
    void PrintList();
    ~intlist();
};

#endif