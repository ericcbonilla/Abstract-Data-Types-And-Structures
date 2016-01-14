//Eric Bonilla
//COEN 12
//10-9-14
//Lab 2
//Unsorted

#include "set.h"

//Defining structure members
struct set {
	int count;
	int length;
	char ** elts;
};

//Big O runtime 0(1), Creates and initializes a new set, maximum capacity of maxElts
SET * createSet(int maxElts) {
	SET *sp;
	sp = malloc(sizeof(SET));

	//If malloc fails, quit the program
	assert(sp!=NULL);

	//Assigning values to set members
	sp->count = 0;
	sp->length = maxElts;
	sp->elts = malloc(sizeof(char*)*maxElts);

	//
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

//Big O runtime: 0(1), return number of elements in set *sp
int numElements(SET *sp) {
	//If sp is not found, quit the program
	assert(sp!=NULL);
	return sp->count;
}

//Big O runtime 0(n), Add an element to a set *sp, return whether the set changed
bool addElement(SET *sp, char *elt) {
	assert(sp!=NULL);
	bool found;
    
    //To check if the element exists first
    if (findElement(sp, elt, &found)!= -1)
        return false;

	//if (sp->count >= 0) {
		
		//Allocate memory for the string
        	elt=strdup(elt);

		//Store the element in the next open slot
		sp->elts[sp->count] = elt;

		//Increment count after adding an element
		sp->count++;
		return true;
	//}

	//else
	//	return false;
}

//Big O runtime 0(n), Return whether element elt is part of a set *sp, used to search for an element
bool hasElement(SET *sp, char *elt) {
	assert(sp != NULL);
	bool found;

    //If findElement returns -1, the element does not exist
    if (findElement(sp, elt, &found) == -1)
        return false;
    
    //Otherwise the element exists
    return true;
    
    /*l
    //Finding element with strcmp
	int i;
	for(i=0; i<sp->count; i++) {
		if(strcmp(elt, sp->elts[i]) ==0) {
			return true;
		}
	}

	return false;
     */
}

//Big O runtime 0(n), Finds element *elt and returns its index. If not found, returns -1
int findElement(SET *sp, char *elt, bool *found) {
	assert(sp != NULL);
    
    //Returning the index of the element if the element is found
	int i;
	for(i=0; i<sp->count; i++) {
		if(strcmp(elt, sp->elts[i]) == 0) {
			return i;
			*found = true;
		}
	}
    
    //Otherwise return -1, which can't be part of the index
    return -1;
}

//Big O runtime 0(n) Remove an element from set *sp using linear search
bool removeElement(SET *sp, char *elt) {
    assert(sp!=NULL);
    bool found;
    
    //Find the element to delete
    int temp = findElement(sp, elt, &found);
    
    //If the element is not found
    if (temp == -1)
        return false;

    //Replacing the element to be deleted with the last element of the array
    sp->elts[temp] = sp->elts[sp->count-1];
    sp->count--;
	
	return true;
}
