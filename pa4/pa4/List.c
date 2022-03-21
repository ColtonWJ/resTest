//-----------------------------------------------------------------------------
//Colton Jeffrey
//cwjeffre
//pa4 
//
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
  // int data;

  void* data;
   Node next;
   Node prev;
} NodeObj;

// private QueueObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
   int cursorIndex;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(void* data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   N->prev = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(){
   List L;
   L = malloc(sizeof(ListObj));            //allocating space for the list
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->cursorIndex = -1;                    //default is undefined
   return(L);
}

// freeList()  destructor
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) { 
      while( !isEmpty(*pL) ) { 
         deleteFront(*pL); 
      }
      free(*pL);
      *pL = NULL;
   }
}


// Access functions -----------------------------------------------------------

// front()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
void* front(List L){
   if( L==NULL ){
      fprintf(stderr, "List Error: calling front() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(L) ){
      fprintf(stderr,"List Error: calling front() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   return(L->front->data);
}

//back
//returns the data from the back of the list
//Pre: !isEmpty(L) 
void* back(List L) {
   if( L==NULL ){
      fprintf(stderr, "List Error: calling back() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(L) ){
      fprintf(stderr,"List Error: calling back() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   return (L->back->data);
}


//get 
//returns the data from the node that the cursor points to
//Pre: length >0, index>0
void* get(List L) {
   if( L==NULL ){
      fprintf(stderr,"List Error: calling get() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(L) ){
      fprintf(stderr, "List Error: calling get() on an empty List");
      exit(EXIT_FAILURE);
   }
   if( L->cursorIndex < 0){
      fprintf(stderr, "List Error: calling get() when index is undefined (-1)");
      exit(EXIT_FAILURE);
   }
   return(L->cursor->data);
}

//index
//returns the index of the cursor Element if defined, -1 otherwise
int index(List L) {
   if( L==NULL ){
      fprintf(stderr,"List Error: calling index() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->cursorIndex);

}


// length()
// Returns the length of L.
int length(List L){
   if( L==NULL ){
      fprintf(stderr, "List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->length);
}

// isEmpty()
// Returns true (1) if List is empty, otherwise returns false (0)
bool isEmpty(List L){
   if( L==NULL ){
      fprintf(stderr, "List Error: calling isEmpty() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->length==0);
}


// Manipulation procedures ----------------------------------------------------

// append()
// Places new Node with data at the back of List.
void append(List L, void* x){
   Node N = newNode(x);  //create new node to be added

   if( L==NULL ){
      fprintf(stderr, "List Error: calling append() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   
   if( isEmpty(L) ) {          //if empty N becomes both front and back
      L->front = L->back = N; 
   }else{                      //add to back of list and point prev back to previous back
                               // then change the back of list pointer 
      L->back->next = N; 
      N->prev = L->back;
      L->back = N; 
   }
   
   L->length++;    //add one to the length
}

// Insert new element into L. If L is non-empty, 
// insertion takes place before front element.
void prepend(List L, void* x){
   Node N = newNode(x);  //create new node to be added

   if( L==NULL ){
      fprintf(stderr, "List Error: calling prepend() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   
   if(isEmpty(L)){
     L->front = L->back = N;
   }
   else {
     L->front->prev = N;
     N->next = L->front;
     L->front = N;
   }
   if(L->cursorIndex != -1) {
     L->cursorIndex++;
   }

   L->length++;
} 



// DeleteFront()
// Deletes data at front of List.
// Pre: !isEmpty(L)
void deleteFront(List L){
   Node N = NULL;  //create node pointer

   if( L==NULL ){
      fprintf(stderr, "List Error: calling deleteFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(L) ){
      fprintf(stderr, "List Error: calling deleteFront() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   
   //if cursor also points to the front of List
   if(L->cursor == L->front) {
     L->cursor = NULL;
     L->cursorIndex = -1;
   }
   else{
     L->cursorIndex--;
   }
   
   N = L->front;   //N points to the front of the list
   if( length(L)>1 ) { //length > 1
      L->front = L->front->next; 
      L->front->prev = NULL;
   }else{ //List has one element
      L->front = L->back = NULL; 
   }
   L->length--;     //adjust length
   freeNode(&N);    //delete node at front and free memory 
}

//deletes last element in List
//Pre !isEmpty()
void deleteBack(List L){
  Node N = NULL;    //node pointer

  if( L==NULL ){
    fprintf(stderr, "List Error: deleteBack() on NULL List reference\n");
    exit(EXIT_FAILURE);
   }
   if( isEmpty(L) ){
      fprintf(stderr, "List Error: calling deleteBack() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   
   //if cursor is on last List node cursor becomes undefined
   if(L->cursor == L->back){
     L->cursor = NULL;
     L->cursorIndex = -1;
   }
   
   N = L->back; //n is a pointer to the back element
   if(length(L) > 1) {
     L->back = L->back->prev;
     L->back->next = NULL;
   }
   else { //there is only one element in the list
     L->front = L->back = NULL;
   }
   
   L->length--;
   freeNode(&N);
   
}


//delete cursor element making cursor element undefined
//Pre: length >0 index >= 0
void delete(List L){
  Node N = NULL;   //create node pointer

  if( L==NULL ){
   fprintf(stderr, "List Error: delete() on NULL List reference\n");
   exit(EXIT_FAILURE);
  }
  if( isEmpty(L) ){
   fprintf(stderr, "List Error: calling delete() on an empty List\n");
   exit(EXIT_FAILURE);
  }
  if( L->cursorIndex == -1 ){
   fprintf(stderr, "List Error: calling delete() on undefined cursor\n");
   exit(EXIT_FAILURE);
  }
   
  N = L->cursor;   //make N point where cursor pointed
   
   //if length is one
  if(L->length == 1){
     L->front = L->back = NULL;
    
    L->cursor = NULL;
    L->cursorIndex = -1;
    L->length--;
    freeNode(&N);
    return;
  }
   
   //if the cursor points to front
  if(L->cursor == L->front) {
    
    L->front = L->cursor->next;
    L->cursor->next->prev = NULL;
    L->cursor->next =NULL;
    L->cursor = NULL;
    L->cursorIndex = -1;
    freeNode(&N);
    L->length--;
    return;
  }
   
   //if cursor points to back of list
  if(L->cursor == L->back) {
    L->back = L->cursor-> prev;
      
   
    L->back->next = NULL;
    L->cursor-> prev = NULL;
    


    L->cursor = NULL;        //dereference cursor
    L->cursorIndex = -1;
    L->length--;             //adjust length
    freeNode(&N);            //delete node that cursor pointed at
    return;
  } 
  
  //cursor points to a node between two other nodes
  L->cursor->next->prev = L->cursor->prev;    //connect nodes on either side of cursor
  L->cursor->prev->next = L->cursor->next;
  
  L->cursor = NULL;        //derefrence cursor
  L->cursorIndex = -1;
  L->length--;             //adjust length
  freeNode(&N);            //delete node that cursor pointed at
  
}


//Resets L to its original empty state (maybe use destructor and constructor here)
void clear(List L){
     if( L==NULL ){
      fprintf(stderr, "List Error: clear() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   //delete front node until list is empty
   if(L!=NULL) { 
      while( !isEmpty(L) ) { 
         deleteFront(L); 
         //L->length--;
      }     
   }//if
  
   L->cursor = NULL;
   L->cursorIndex = -1;
}

//overwrites the cursor element data to x
//pre length >0 index >0
void set(List L, void* x){
  if( L==NULL ){
    fprintf(stderr, "List Error: set() on NULL List reference\n");
    exit(EXIT_FAILURE);
   }
   if( isEmpty(L) ){
    fprintf(stderr, "List Error: calling set() on an empty List\n");
    exit(EXIT_FAILURE);
   }
   if( L->cursorIndex == -1 ){
    fprintf(stderr, "List Error: calling set() on undefined cursor\n");
    exit(EXIT_FAILURE);
   }

   L->cursor->data = x;       //sets cursor node data to x
}

//If L is nonempty set cursor to the front element, otherwise do nothing
//pre !isEmpty()
void moveFront(List L){
  if( L==NULL ){
    fprintf(stderr, "List Error: moveFront() on NULL List reference\n");
    exit(EXIT_FAILURE);
   }
  if( isEmpty(L) ){
    fprintf(stderr, "List Error: calling moveFront() on an empty List\n");
    exit(EXIT_FAILURE);
   }
 
   L->cursorIndex = 0;
   L->cursor = L->front;
}

//if L is nonempty set the cursor to the back element of the list, else do nothing
//cursorIndex is set to the length of the list -1
void moveBack(List L){
  if( L==NULL ){
    fprintf(stderr, "List Error: moveBack() on NULL List reference\n");
    exit(EXIT_FAILURE);
   }
  if( isEmpty(L) ){
    fprintf(stderr, "List Error: calling moveFront() on an empty List\n");
    exit(EXIT_FAILURE);
  }
    
   L->cursorIndex = L->length - 1;
   L->cursor = L->back;

}

//if cursor is defined and not at front then move cursor one step closer to front
//if cursor defined and at front cursor becomes undefined
//if cursor is undefined do nothing
void movePrev(List L){
  if( L==NULL ){
    fprintf(stderr, "List Error: movePrev() on NULL List reference\n");
    exit(EXIT_FAILURE);
   }
   if(L->cursorIndex == -1) {return;}

   //if cursor points to front element it becomes unidentified
   if(L->cursor == L-> front) {
     L->cursor = NULL;
     L->cursorIndex = -1;
     return;
   }
   
   //if cursor does not point at front then move it one previous of where it is
   L->cursor = L->cursor->prev;
   L->cursorIndex--;
}

//if cursor id defined and not at back move cursor one step closer to back
//if cursor is defined and at back cursor becomes undefined
//if cursor is undefined do nothing
void moveNext(List L){
  if( L==NULL ){
    fprintf(stderr, "List Error: moveNext() on NULL List reference\n");
    exit(EXIT_FAILURE);
   }
   if(L->cursorIndex == -1) {return;}
   
   if(L->cursor == L->back) {
   L->cursor = NULL;
   L->cursorIndex = -1;
   return;
   }
   
   L->cursor = L->cursor->next;
   L->cursorIndex++;
}


// Insert new element before cursor. 
// Pre: length()>0, index()>=0
void insertBefore(List L, void* x){
   if( L==NULL ){
    fprintf(stderr, "List Error: insertBefore() on NULL List reference\n");
    exit(EXIT_FAILURE);
   }
   if( isEmpty(L) ){
    fprintf(stderr, "List Error: calling insertBefore() on an empty List\n");
    exit(EXIT_FAILURE);
   }
   if( L->cursorIndex == -1 ){
    fprintf(stderr, "List Error: calling insertBefore() on undefined cursor\n");
    exit(EXIT_FAILURE);
   }

   Node N = newNode(x);   //create new node to add

   //if cursor points to the front of the list
   if(L->front == L->cursor) {
     N->next = L->cursor;
     L->cursor->prev = N;
     L->front = N;
     L->cursorIndex++;
     L->length++;
     return;
   }

   N->next = L->cursor;              //attach new next to cursor Node
   N->prev = L->cursor->prev;        //attach new prev to node before cursor Node
   L->cursor->prev->next = N;        // prev cursor node next to new Node
   L->cursor->prev = N;              //attach prev cursor to new node
   L->cursorIndex++;                 //update cursor index
   L->length++;
}

// Insert new element after cursor. 
// Pre: length()>0, index()>=0
void insertAfter(List L, void* x){
   if( L==NULL ){
    fprintf(stderr, "List Error: insertBefore() on NULL List reference\n");
    exit(EXIT_FAILURE);
   }
   if( isEmpty(L) ){
    fprintf(stderr, "List Error: calling insertBefore() on an empty List\n");
    exit(EXIT_FAILURE);
   }
   if( L->cursorIndex == -1 ){
    fprintf(stderr, "List Error: calling insertBefore() on undefined cursor\n");
    exit(EXIT_FAILURE);
   }
   
   Node N = newNode(x); //new node to be added
   
   //if cursor points to the back of the list
   if(L->back == L->cursor) {
     N->prev = L->cursor;
     L->cursor->next = N;
     L->back = N;
     L->length++;
     return;
   }
   
   //otherwise
   N->prev = L->cursor;                 //n prev points to cursor node
   N->next = L->cursor->next;           //n next points to node after cursor node
   L->cursor->next->prev = N;           //connect node after cursor prev to new node
   L->cursor->next = N;                 //cursor next now points to n
   L->length++;
} 





// Other Functions ------------------------------------------------------------

/*
//prints a space separated list to the file IO given as a param
void printList(FILE* out, List L){
   
   
   if( L==NULL ){
      fprintf(stderr,"List Error: calling printList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   
   
   //if list is empty
   if(L->length == 0) {
   fprintf(out, "\n");
   return;
   }
   
   Node N = NULL;
   
   fprintf(out, "%d", L->front->data);


   for(N = L->front->next; N != NULL; N = N->next){
      fprintf(out, " %d", N->data);
   }
   
 
}
*/

/*
//returns a new list that has the same int sequence as L 
//the cursor will be unidentified
//L is unchanged
List copyList(List L) {
  List copy = newList(); //new list obj needs to de cleared by caller

  //null check
  //if L is empty
  if(isEmpty(L)){ return(copy);}
 
  //otherwise
  Node N = NULL;
  
  for(N = L->front; N != NULL; N = N->next){
    append(copy, N->data);
  }
   
  
  return(copy);
}
*/


/*
// printList()
// Prints a string representation of List consisting of a space separated list 
// of ints to stdout.
void printer(List L){
   Node N = NULL;   //create node pointer

   if( L==NULL ){
      fprintf(stderr,"List Error: calling printList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   for(N = L->front; N != NULL; N = N->next){
      printf("%d ", N->data);
   }
   printf("\n");
}
*/

/*
// equals()
// Returns true (1) if A is same int sequence as B, false (0) otherwise.
bool equals(List A, List B){
  int eq = 0;
  Node N = NULL;
  Node M = NULL;

  if( A==NULL || B==NULL ){
    fprintf(stderr, "List Error: calling equals() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }

  eq = ( A->length == B->length );
  N = A->front;
  M = B->front;
  while( eq && N!=NULL){
    eq = (N->data==M->data);
    N = N->next;
    M = M->next;
  }
  return eq;
}
*/
