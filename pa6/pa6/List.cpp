//-----------------------------------------------------------------------------
//Colton Jeffrey
//cwjeffre
//pa6
//
//List.cpp
//implementation file for List ADT
//-----------------------------------------------------------------------------




#include<string>
#include<iostream>
#include<stdexcept>
#include "List.h"




//private constructor -------------

//Node constructor
List::Node::Node(ListElement x){
  data = x;
  next = nullptr;
  prev = nullptr;
}


//Class Constructors & Destructors ------------------------


//do we make the dummy nodes here?
//Creates new List in the empty state.
List::List() {
  
  frontDummy = new Node(-1);
  backDummy = new Node(-2);
  frontDummy->next = backDummy;
  backDummy->prev = frontDummy;
  frontDummy->prev = nullptr;
  backDummy->next = nullptr;
  
  beforeCursor = frontDummy;
  afterCursor = backDummy;
  pos_cursor = 0;
  num_elements =0;

}

 
//copy constructor
List::List(const List& L){
  

  Node* M = nullptr;  // M will be a pointer to new nodes to be inserted into list

  //if L is notNull then load elements into new list
  if(L.frontDummy != nullptr) {
    Node* N = L.frontDummy;  //N will go through list param
    M = new Node(N->data); //M creates new nodes in the new copy List
    frontDummy = M;  //assign front of list to M

    while(N->next != nullptr){
      N = N->next;
      M->next = new Node(N->data); //make new node and conenct M to it
      M->next->prev = M;           // connect that new node back to M
      M = M->next;                 //move M to the newly created node
    }


    //now the lists should have Identical elements

    backDummy = M;       //M should be on last element of list which should be backDummy Node
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor =0;
    num_elements = L.num_elements;

  }//if 

}

//destructor
List::~List() {
  Node* temp = frontDummy;

  while(frontDummy) {
    temp = frontDummy;
    frontDummy = frontDummy->next;
    delete temp; temp=0;
  }

}

//Access functions ---------------------------------------

//length()
//returns the length of the list.
int List::length() const {
  return(num_elements);
}

//front()
//Returns the front element in this List.
// Pre: length() >0
ListElement List::front() const{
  if(num_elements == 0) {
    throw std::length_error("List: front(): empty list");
  }
  return(frontDummy->next->data);

}


//back()
//Returns the front element in this List.
//pre: length()>0
ListElement List::back() const{
  if(num_elements ==0){
    throw std::length_error("List: back(): empty list");
  }
  return(backDummy -> prev -> data);
}


//position()
//Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
  if(0 > pos_cursor || num_elements < pos_cursor){
    throw std::length_error("List: position(): undefined pos_cursor\n");
  }
  return(pos_cursor);
}


//peekNext()
//Returns the element after the cursor.
//pre: position() < length()
ListElement List::peekNext() const{
  if(pos_cursor >= num_elements){
    throw std::range_error("List: peekNext(): cursor at back");
  }
  return(afterCursor->data);
}

//peekPrev()
//Returns the element before the cursor.
//pre: postition() >0
ListElement List::peekPrev() const{
  if(pos_cursor <= 0){
    throw std::range_error("List: peekPrev(): cursor at front");
  }
  return(beforeCursor->data);
}

//Manipulation procedures ------------------------------------------------------


//clear()
//Deletes all elements in this List, setting it to the empty state.
//does not delete the dummy Nodes
void List::clear() {
  pos_cursor =0;
  int initSize = num_elements;

  beforeCursor = frontDummy;
  afterCursor = frontDummy->next;

  for(int i=0; i < initSize; i++) {
    eraseAfter();
  }

}

//MoveFront()
//Moves cursor to position 0 in List
void List::moveFront() {
  pos_cursor = 0;
  beforeCursor = frontDummy;
  afterCursor = frontDummy->next;
}

//MoveBack()
//Moves cursor to position length in list.
void List::moveBack() {
  pos_cursor = num_elements;
  afterCursor = backDummy;
  beforeCursor = backDummy->prev;
}

//moveNext()
//Advances cursor to next position. Retursns the List elenemt that
//was passed over
//pre: position() < length()
ListElement List::moveNext(){
  if(pos_cursor >= length()) {
    throw std::range_error("List: moveNext(): cursor at back");
  }
  ListElement value = peekNext();
  beforeCursor = beforeCursor->next;
  afterCursor = afterCursor->next;
  pos_cursor++;

  return value;
}

//movePrev()
//Adbaanaces cursor to next lower position. Returns the List element that
//was passed over.
//Pre: position() > 0
ListElement List::movePrev() {
  if(pos_cursor == 0) {
    throw std::range_error("List: movePrev(): cursor at front");
  }

  ListElement value = peekPrev();
  beforeCursor = beforeCursor->prev;
  afterCursor = afterCursor->prev;
  pos_cursor--;
  
  return value;
}



//insertAfter()
//inserts x after the cursor
void List::insertAfter(ListElement x){
  Node* N = new Node(x);

  N->next = afterCursor;
  N->prev = beforeCursor;
  afterCursor->prev = N;
  beforeCursor->next = N;

  afterCursor = N;  
  num_elements++;
}

//insertBefore()
//inserts x before the cursor
void List::insertBefore(ListElement x){
  Node* N = new Node(x);

  N->next = afterCursor;
  N->prev = beforeCursor;
  afterCursor->prev = N;
  beforeCursor->next = N;

  beforeCursor = N;
  pos_cursor++;
  num_elements++;    

}

//setAfter()
//overwrites the List element after the cursor with x
//pre: position() < length
void List::setAfter(ListElement x) {
  if(pos_cursor >= num_elements) {
    throw std::range_error("List: setAfter(): cursor at back");
  } 
  afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){
  if(pos_cursor <= 0) {
    throw std::range_error("List: setBefore(): cursor at front");
  } 
  beforeCursor->data =x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){
  if(pos_cursor >= num_elements) {
    throw std::range_error("List: eraseAfter(): cursor at back");
  }

  Node* toDel = afterCursor;
  
  beforeCursor->next = afterCursor->next;
  afterCursor->next->prev = beforeCursor;
  afterCursor = afterCursor->next;

  delete toDel; toDel = nullptr;

  num_elements--;
  
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
  if(pos_cursor <= 0){
    throw std::range_error("List: eraseBefore(): cursor at front");
  }

  Node* toDel = beforeCursor;

  afterCursor->prev = beforeCursor->prev;
  beforeCursor->prev->next = afterCursor;
  beforeCursor = beforeCursor->prev;
  delete toDel; toDel = nullptr;

  num_elements--;
  pos_cursor--;

}


//Other functions --------------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x){
  int indexX = -1;
  bool found = false;

  //my for loop worked I guess
  while (pos_cursor < num_elements && !found) {
    if(afterCursor->data == x && !found) {
      found = true;
      indexX = pos_cursor +1;
    }

     moveNext(); 
  }

  return indexX;
}


// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x){
  int indexX = -1;
  bool found = false;
  
    
  while(pos_cursor != 0 && !found) {
    if(beforeCursor->data == x){
      found = true;
      indexX = pos_cursor - 1;
    }     

    movePrev();
  }

  return indexX;

}


// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup(){

  int x = 0;

  Node* find;
  Node* temp;
 

  find = frontDummy->next; 

  while(find->next != backDummy) {   
    
     x = find->data;

    temp = find->next;
    while(temp->next != backDummy->next) {
 
      if(temp->data == x) {

	if(temp == afterCursor) { afterCursor = afterCursor->next;}
        if(temp == beforeCursor) { beforeCursor = beforeCursor->prev;}

        Node* toDel = temp;
        temp = temp->next; 
	
        toDel->next->prev = toDel->prev;
        toDel->prev->next = toDel->next;
        toDel->next = nullptr;
        toDel->prev = nullptr;
        delete toDel; toDel = nullptr;
        num_elements--;

      }
      else {temp =temp->next;}
    }//inner while loop


    if(find->next != backDummy) find = find->next;
  }//outer while


  //now place cursor between beforeCursor and AfterCursor
  int count =0;
  Node* look = frontDummy;
  while( look->next != backDummy->next) {
    if(look == beforeCursor) {pos_cursor = count; }
    look = look->next;
    count++;
  }

}




// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const{
  List cat;
  Node* N = this->frontDummy->next;  //pointer to front of this List
  Node* M = L.frontDummy->next;      // pointer to front of param list

  while(N!=nullptr) {
    cat.insertAfter(N->data);
    cat.moveNext();
    N=N->next;
  }
  cat.eraseBefore();

  while(M != nullptr) {
    cat.insertAfter(M->data);
    cat.moveNext();
    M = M->next;
  }

  cat.eraseBefore();

  cat.moveFront();
  return cat;

}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
  bool eq = false;
  Node* N = nullptr;
  Node* M = nullptr;

  eq = (this->num_elements == R.num_elements);
  N = this->frontDummy->next;
  M = R.frontDummy->next;

  while(eq && N!= nullptr) {
    eq = (N->data == M->data);
    N = N->next;
    M = M->next;
  }

  return eq;
}



//to_string()
//Returns a string representation of this List consisting of a 
//comma seperated sequence of elements, surrounded by parenthese.
std::string List::to_string() const{

  Node * itr= frontDummy->next;

  std::string listStr;
  // std::sting value;

  listStr = "(";
  for(int i=0; i < num_elements; i++) {
    std::string value = std::to_string(itr->data);

    if(i != 0) { listStr += ", ";}
    listStr += value;
    itr = itr->next;
  }
  listStr +=  ")";
  return listStr;
}




//overriden Operators -------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ){
  return stream << L.List::to_string();

}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ){
  return A.List::equals(B);
}


// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
  if( this != &L) { //not self assignment
    //make a copy of L
    List temp = L;
    
    
    //swap copy field with 
    std::swap(frontDummy, temp.frontDummy);
    std::swap(backDummy, temp.backDummy);
    std::swap(afterCursor, temp.afterCursor);
    std::swap(beforeCursor,temp.beforeCursor);
    std::swap(pos_cursor, temp.pos_cursor);
    std::swap(num_elements, temp.num_elements);
  }

  return *this;

}




