//Eric Bonilla
//COEN 12
//10-23-14
//Lab 3
//Hash Table

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "set.h"

//Defining states of hash table
#define EMPTY 0
#define FILLED 1
#define DELETED 2

//Finds element *elt and returns its index. If not found, returns -1
int findElement(SET *sp, char *elt, bool *found);

//Declaring hash function
unsigned hashString(char *s);

//Defining structure members
struct set {
	int count;
	int length;
	char ** elts;
    char * flags;
};

//Big O runtime 0(1), creates and initializes a new set, maximum capacity of maxElts
SET * createSet(int maxElts) {
	SET *sp;
	sp = malloc(sizeof(SET));

	//If malloc fails, quit the program
	assert(sp!=NULL);

	//Assigning values to set members
	sp->count = 0;
	sp->length = maxElts;
	sp->elts = malloc(sizeof(char*)*maxElts);
    
    sp->flags = malloc(sizeof(char)*maxElts);
	assert(sp->elts!=NULL && sp->flags!=NULL);
    
    //Initialize all flags to EMPTY
    int i;
    for (i = 0; i < maxElts; i++)
        sp->flags[i] = EMPTY;

	return sp;
}

//Big O runtime 0(n), Destroy a set *sp by deallocating memory
void destroySet(SET *sp) {

	//Make sure the set is actually there before trying to delete it
	assert(sp!=NULL);

	//Will only try to free sp->count FILLED elements
	int i;
    for (i=0; i<sp->count; i++) {
        if (sp->flags[i]==FILLED)
            free(sp->elts[i]);
    }
    
    //Free flags
    free(sp->flags);

	//Free the array itself
	free(sp->elts);

	//Free the entire set
	free(sp);
}

//return number of elements in set *sp
int numElements(SET *sp) {
    
	//If sp is not found, quit the program
	assert(sp!=NULL);
	return sp->count;
}


//Big O average case runtime 0(1), worst case 0(n), Add an element to a set *sp, return whether the set changed
bool addElement(SET *sp, char *elt) {
	assert(sp!=NULL && elt!=NULL);

	if (sp->count == sp->length)
		return false;
	   
	bool found;
	int temp = findElement(sp, elt, &found);

    //Sets flag of added element to FILLED
	if (found == false) {
        sp->elts[temp] = strdup(elt);
		sp->flags[temp] = FILLED;
		sp->count++;
		return true;
	}
	   
	   return false;
}

//Big O average case runtime 0(1), worst case, Return whether element elt is part of a set *sp, used to search for an element
bool hasElement(SET *sp, char *elt) {

	bool found;
	assert(sp != NULL);

	findElement(sp, elt, &found);
	return found;
}


//Big O average case runtime 0(1), worst case 0(n), searches the array using a hash function
int findElement(SET *sp, char *elt, bool *found) {
    assert(sp!= NULL && elt!=NULL);
    
    *found = false;
    unsigned int hash = hashString(elt);
    
    int i;
    int loc;
    
    int del = -1;
    //Searches until the end of the array
    for (i=0; i<sp->length; i++) {
        loc = (hash+i)%sp->length;
        
        //Once the loop reaches a deleted location, del is set to that location to save it
        if (del == -1 && sp->flags[loc] == DELETED)
            del = loc;
        //Once the loop reaches an empty location, return that location
        if (sp->flags[loc] == EMPTY) {
            //If a deleted location has first been found, return that location
            if (del!=-1)
                return del;
            else
                return loc;
        }
        
        //If the target element is found
        if (sp->flags[loc] == FILLED && strcmp(elt, sp->elts[loc]) == 0) {
            *found = true;
            return loc;
        }
    }
    
    return del;
}



//Big O average case runtime 0(1). worst case 0(n), Remove an element from set *sp
bool removeElement(SET *sp, char *elt) {
    assert(sp!=NULL && elt!=NULL);

    bool found;
    int i;
   
   	//Find the element to delete
   	int temp = findElement(sp, elt, &found);
    
    //Free the element and set its flag to DELETED
    if (found == true) {
        free(sp->elts[temp]);
        sp->flags[temp] = DELETED;
        sp->count--;
        return true;
    }

    else
       return false;
}


//Big O runtime 0(n), hash function for inserting, deleting, and finding
unsigned hashString(char *s) {
    unsigned hash = 0;
    
    while (*s != '\0')
        hash = 31*hash + *s++;
    
    return hash;
}
