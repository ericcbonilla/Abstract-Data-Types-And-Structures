//Eric Bonilla
//COEN 12
//10-9-14
//Lab 2
//Sorted

#include "set.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

//Finds element *elt and returns its index. If not found, returns -1
int findElement(SET *sp, char *elt, bool *found);

//Defining structure members
struct set {
	int count;
	int length;
	char ** elts;
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

	assert(sp->elts!=NULL);

	return sp;
}

//Big O runtime 0(n), Destroy a set *sp by deallocating memory
void destroySet(SET *sp) {

	//Make sure the set is actually there before trying to delete it
	assert(sp!=NULL);

	//Will only try to free sp->count elements
	int i;
	for(i=0; i<sp->count; i++) {
		free(sp->elts[i]);
	}

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

//Big O runtime 0(n), Add an element to a set *sp, return whether the set changed
bool addElement(SET *sp, char *elt) {
	assert(sp!=NULL && elt!=NULL);
	int i;
	   
	elt = strdup(elt);

	if (sp->count == sp->length)
		return false;
	   
	bool found;
	int temp = findElement(sp, elt, &found);

	if (found == false) {
		for (i = sp->count ; i > temp; i--)
			sp->elts[i] = sp->elts[i-1];
		sp->elts[temp] = elt;
		sp->count++;
		return true;
	}
	   
	   return false;
}

//Big O runtime 0(logn), Return whether element elt is part of a set *sp, used to search for an element
bool hasElement(SET *sp, char *elt) {

	bool found;
	assert(sp != NULL);

	findElement(sp, elt, &found);
	return found;
}

//Big O runtime 0(logn), searches the array using binary search
int findElement(SET *sp, char *elt, bool *found) {
   
	int lo, mid, hi, diff;
	lo = 0;
	hi = sp->count-1;

	//Binary search
	while(lo <= hi) {
		mid = (lo + hi)/2;
		diff = (strcmp(elt, sp->elts[mid]));
		if (diff < 0)
		hi = mid-1;
		else if (diff > 0)
		lo = mid+1;
		else {	//If element is found
			*found = true;
			return mid;
		}
	}

	*found = false;
	return lo;
}

//Big O runtime 0(n), Remove an element from set *sp
bool removeElement(SET *sp, char *elt) {
       assert(sp!=NULL && elt!=NULL);

       bool found;
       int i;
   
   	//Find the element to delete
   	int temp = findElement(sp, elt, &found);
   
   	//If the element is not found
   	if (temp == -1)
           return false;
   
       free(sp->elts[temp]);

       //Replacing the element to be deleted with the last element of the array
       for (i=temp; i<sp->count-1; i++) {
           sp->elts[i] = sp->elts[i+1];
       }
   
       sp->count--;

       return true;
}
