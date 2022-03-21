//-----------------------------------------------------------------------------
//Colton Jeffrey
//cwjeffre
//pa4 
//
// List.h
// Header file for List ADT
//-----------------------------------------------------------------------------
#ifndef LIST_H_INCLUDE_
#define LIST_H_INCLUDE_

#include<stdbool.h>


// Exported type --------------------------------------------------------------
typedef struct ListObj* List;


// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty List object. 
List newList();

// freeList()
// Frees all heap memory associated with List *pQ, and sets *pQ to NULL.
void freeList(List* pQ);


// Access functions -----------------------------------------------------------

// front()
// Returns the value at the front of List.
// Pre: !isEmpty(Q)
void* front(List L);

//back()
//returns the data stored in last node of List
// Pre: !isEmpty(Q)
void* back(List L);

//get 
//returns the data from the node that the cursor points to
//Pre: length >0, index>0
void* get(List L);

//index
//returns the index of the cursor Element if defined, -1 otherwise
int index(List L);

// length()
// Returns the length of List L.
int length(List L);

// isEmpty()
// Returns true if List is empty, otherwise returns false.
bool isEmpty(List Q);


// Manipulation procedures ----------------------------------------------------

//clear();
//Resets L to its original empty state
void clear(List L);

//set()
//overwrites the cursor element data to x
//pre length >0 index >0
void set(List L, void* x);

//moveFront()
//If L is nonempty set cursor to the front element, otherwise do nothing
void moveFront(List L); 

//moveBack()
//if L is nonempty set the cursor to the back element of the list, else do nothing
void moveBack(List L); 

//movePrev()
//if cursor is defined and not at front then move cursor one step closer to front
//if cursor defined and at front cursor becomes undefined
//if cursor is undefined do nothing
void movePrev(List L);

//moveNext()
//if cursor id defined and not at back move cursor one step closer to back
//if cursor is defined and at back cursor becomes undefined
//if cursor is undefined do nothing
void moveNext(List L);

//prepend()
// Insert new element into L. If L is non-empty, 
// insertion takes place before front element.
void prepend(List L, void* x); 

//append()
// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, void* x);

//insertBefore()
// Insert new element before cursor. 
// Pre: length()>0, index()>=0
void insertBefore(List L, void* x);

//insertAfter()
// Insert new element after cursor. 
// Pre: length()>0, index()>=0
void insertAfter(List L, void* x); 

//deleteBack
//deletes last element in List
//Pre !isEmpty()
void deleteBack(List L); 

//delete()
//delete cursor element making cursor element undefined
//Pre: length >0 index >= 0
void delete(List L);

// deleteFront()
// Deletes data at front of L.
// Pre: !isEmpty(Q)
void deleteFront(List Q);


// Other Functions ------------------------------------------------------------
/*
// printQueue()
// Prints a string representation of Q consisting of a space separated list 
// of ints to stdout.
void printer(List Q);
*/

//printList()
//prints List to file in the form of a space separated string 
//with front on the left 
//void printList(FILE* out, List L);

/*
//copyList()
//copysList and returns new List
List copyList(List L);

// equals()
// Returns true if A is same int sequence as B, false otherwise.
bool equals(List A, List B);
*/

#endif
