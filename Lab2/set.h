//Eric Bonilla
//COEN 12
//4-8-14
//Project 2

/*
 * File:        set.h
 *
 * Description: This file contains the public function and type
 *              declarations for a set abstract data type for strings.  A
 *              set is an unordered collection of distinct elements.
 *
 *              Note that this file uses the bool type, but does not define
 *              it.  You should include <stdbool.h> beforehand.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#ifndef SET_H
#define SET_H

typedef struct set SET;

//Creates and initializes a new set, maximum capacity of maxElts
SET *createSet(int maxElts);

//Destroy a set *sp by deallocating memory
void destroySet(SET *sp);

//Add an element to a set *sp, return whether the set changed
bool addElement(SET *sp, char *elt);

//Remove an element from set *sp
bool removeElement(SET *sp, char *elt);

//Return whether element elt is part of a set *sp, used to search for an element
bool hasElement(SET *sp, char *elt);

//Finds element *elt and returns its index. If not found, returns -1
int findElement(SET *sp, char *elt, bool *found);

//return number of elements in set *sp
int numElements(SET *sp);

# endif /* SET_H */
