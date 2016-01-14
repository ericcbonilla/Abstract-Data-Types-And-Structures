//Eric Bonilla
//COEN 12
//12-4-14
//Lab 6
//Deque.c converted to C++

#include <cassert>
#include "deque.h"

struct Node {
    int data;
    Node *next;
    Node *prev;
};

//Constructor: more or less replaces createDeque
Deque::Deque() {
    count = 0;
    head = new Node;
    head -> next = head;
    head -> prev = head;
    return;
}

//Deconstructor: replaces destroyDeque
Deque::~Deque() {
    Node *np = new Node;
    np = head;
    Node *next = new Node;
    do {
        next = np->next;
        delete np;
        np = next;
    } while (np != head);
}

//Returns the number of items in the deque
int Deque::size() {
    return count;
}

//Add an item x to the first slot of the deque
void Deque::addFirst(int x) {
    Node *temp = new Node;
    Node *pNew = new Node;
    
    pNew -> data = x;
    temp = head;
    
    pNew -> prev = temp;
    pNew -> next = temp -> next;
    
    temp -> next -> prev = pNew;
    temp -> next = pNew;
    
    count ++;
}

//Add an item x to the last slot of the deque
void Deque::addLast(int x){
    
    Node *temp = new Node;
    Node *pNew = new Node;
    
    pNew -> data = x;
    temp = head;
    
    pNew -> next = temp;
    pNew -> prev = temp -> prev;
    
    temp -> prev -> next = pNew;
    temp -> prev = pNew;
    
    count ++;
}

//Remove and return an item from the first slot of the deque
int Deque::removeFirst( ){
    assert(count > 0);

    Node *dummy = new Node;
    dummy = head;
    
    Node *np = new Node;
    np = dummy -> next;
    
    dummy -> next = np -> next;
    np -> next -> prev = dummy;
    
    int value = np -> data;
    
    delete np;
    
    count--;
    return value;
}

//Remove and return an item from the last slot of the deque
int Deque::removeLast(){
    assert(count > 0);

    Node *dummy = new Node;
    dummy = head;
    Node *np = new Node;
    np = dummy -> prev;
    
    dummy -> prev = np -> prev;
    np -> prev -> next = dummy;
    
    int value = np -> data;
    
    delete np;
    
    count--;
    return value;
}

//Return the value of the first location in the deque
int Deque::getFirst(){
    return head -> next -> data;;
}

//Return the value of the last location in the deque
int Deque::getLast() {
    return head -> prev -> data;;
}