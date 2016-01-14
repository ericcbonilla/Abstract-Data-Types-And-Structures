//Eric Bonilla
//COEN 12
//11-9-14
//Project 4
//Deque created using circular, doubly-linked list

//All operations are 0(1) except for destroyDeque

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "deque.h"

struct node {
    int data;
    struct node *next;
    struct node *prev;
};

struct deque {
    int count;
    struct node *head;
};

//Creates and initializes a new deque
DEQUE * createDeque(void) {
    DEQUE *dp;
    dp = malloc(sizeof(DEQUE));
    
    //Assert that the set is not NULL
    assert(dp!=NULL);
    
    //Initializing structure members, head is the dummy node
    dp->count = 0;
    dp->head = malloc(sizeof(struct node));

    dp->head->next = dp->head;
    dp->head->prev = dp->head;
    
    return dp;
}

//Destroys the deque pointed by *dp by deallocating memory
void destroyDeque(DEQUE *dp) {
    assert(dp!=NULL);

    struct node *deleted = dp->head->next;
	int i;
	
	for (i=0; i<dp->count-1; i++) {
		free(deleted->prev);
		deleted = deleted->next;
	}

	free(deleted);
    
    //Free the deque
    free(dp);
}

//Counts the number of items in the deque pointed by *dp
int numItems(DEQUE *dp) {
	assert(dp!=NULL);

	//int counter = dp->count;
	return dp->count;
}

//Add an item x to the first slot of the deque
void addFirst(DEQUE *dp, int x) {
	assert(dp!=NULL);
    
    //printf("addFirst\n");

	struct node *newnode;
	newnode = (struct node *)(malloc(sizeof(struct node)));

	newnode->data = x;

    //Add the new node in front of the dummy node and increment the counter
	newnode->next = dp->head->next;
	newnode->prev = dp->head;
	dp->count++;

	//Setting the next and previous pointers for the new node
	dp->head->next->prev = newnode;
	dp->head->next = newnode;
}

//Add an item x to the last slot of the deque
void addLast(DEQUE *dp, int x) {
	assert(dp!=NULL);

	struct node *newnode;
	newnode = (struct node *)(malloc(sizeof(struct node)));

	newnode->data = x;

    //Add the new node behind the dummy node and increment the counter
	newnode->next = dp->head;
	newnode->prev = dp->head->prev;
	dp->count++;

	//Setting the next and previous pointers for the new node
	dp->head->prev->next = newnode;
	dp->head->prev = newnode;
}

//Remove and return an item from the first slot of the deque
int removeFirst(DEQUE *dp) {
	assert(dp!=NULL && dp->count!=0);

	//declaring the item to be removed
	struct node * temp = dp->head->next;

	dp->count--;

	int tempData = temp->data;

	temp->next->prev = dp->head;
	dp->head->next = temp->next;
    

	//Free the node and return its data
	free(temp);
	return tempData;
}

//Remove and return an item from the last slot of the deque
int removeLast(DEQUE *dp) {
	assert(dp!=NULL && dp->count!=0);

	//declaring the item to be removed
	struct node * temp = dp->head->prev;

	dp->count--;

	int tempData = temp->data;

	temp->prev->next = dp->head;
	dp->head->prev = temp->prev;
    
    //printf("removeLast\n");

	//Free the node and return its data
	free(temp);
	return tempData;
}

//Return the value of the first location in the deque
int getFirst(DEQUE *dp) {
	assert(dp!=NULL && dp->head->next!=NULL);

	return(dp->head->next->data);
}

//Return the value of the last location in the deque
int getLast(DEQUE *dp) {
	assert(dp!=NULL && dp->head->prev!=NULL);

	return(dp->head->prev->data);
}
