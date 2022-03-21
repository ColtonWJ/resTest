//-----------------------------------------------------------------------------      
//Colton Jeffrey                                                                     
//cwjeffre                                                                           
//pa4                                                                                
//                                                                                   
// Matrix.c
// function definitions of Matrix ADT
//
//-----------------------------------------------------------------------------


#include "Matrix.h"



//typedefs


//Entry object --------
typedef struct EntryObj* Entry;

typedef struct EntryObj{
  int col;
  double value;
}EntryObj;



Entry newEntry(int newCol, double newData) {
  Entry N= malloc(sizeof(EntryObj));

  
  N->col = newCol;
  N->value = newData;
  return(N);
}

void freeEntry(Entry* pN){
  if( pN!=NULL && *pN!=NULL ){
    free(*pN);
    *pN = NULL;
  }
}


//Accessor funcs --------------------------

int getCol(Entry E){
  return(E->col);
}

double getValue(Entry E) {
  return(E->value);
}

void changeValue(Entry E, double x){
  E->value = x;
}

// ----------------------

//Matrix object ---------

typedef struct MatrixObj{
  int size;   //number of columns and rows in the matrix  
  int NNZ;    //number of nonzero entries in the matrix
  
  List* mtrx; //pointer to an array of list pointers

}MatrixObj;


Matrix newMatrix(int n){
 
  Matrix M = malloc(sizeof(MatrixObj));
  M->mtrx = malloc(sizeof(List) * (n+1));

  M->size =n;
  M->NNZ =0;

  for(int i=1; i<n+1;i++) {
    M->mtrx[i] = newList();
  }

  return(M);

}



void freeMatrix(Matrix* pM) {
  Entry toDel = NULL;
 
  int n = size(*pM);
  for (int i =1; i < n+1; i++) {
     if((*pM)->mtrx[i] != NULL) {

      
      //free the entries in each list
      if(!isEmpty((*pM)->mtrx[i])) {moveFront((*pM)->mtrx[i]);}
      for(int k =0; k < length((*pM)->mtrx[i]); k++) {
        toDel = get((*pM)->mtrx[i]);
        freeEntry(&toDel);
	toDel = NULL;
        moveNext((*pM)->mtrx[i]);
      }

     
      //free each list
      freeList(&(*pM)->mtrx[i]); 
    }//if not list Not NULL

  }//for i

  //free matrix
 
  free((*pM)->mtrx);

  free(*pM);
  *pM = NULL;

}


// ----------------------




int size(Matrix M) {
  if(M == NULL){
    printf("Matrix ADT error: calling size() on NULL refrence\n");
  }
  return(M->size);
}

int NNZ(Matrix M) {
  if(M == NULL){
    printf("Matrix ADT error: calling size() on NULL refrence\n");
  }
  return(M->NNZ);
}



//untested as of rn
//returns 1 if equal and 0 if false
int equals(Matrix A, Matrix B) {
  if(A == NULL || B == NULL){
    printf("Matrix ADT error: calling equals() on NULL refrence\n");
  }
  //check that size is same
  if(size(A) != size(B)) { return 0;}

  //go through each row and check that the each corresponding element has the
  //same value

  for(int i =1; i< size(A)+1; i++) {


    if(length(A->mtrx[i]) != length(B->mtrx[i])){ return 0;}

    if(!isEmpty(A->mtrx[i])) { moveFront(A->mtrx[i]);}
    if(!isEmpty(B->mtrx[i])) { moveFront(B->mtrx[i]);}

    for(int k=0; k < length(A->mtrx[i]); k++) {

      if( getValue(get(A->mtrx[i])) != getValue(get(B->mtrx[i]))) { return 0;}

      moveNext(A->mtrx[i]);
      moveNext(B->mtrx[i]);
    }//go through row (list) and compair elements


  }// for i goes through columns of A and B


  return 1; 
}


//Manipulation procedures ------------------------------------

//makeZero()
//Re-sets M to the zero Matrix state 
void makeZero(Matrix M) {
  if(M == NULL){
    printf("Matrix ADT error: calling makeZero() on NULL refrence\n");
  }
  for(int i=1; i<size(M)+1; i++) {

    

    if(!isEmpty(M->mtrx[i])) { moveFront(M->mtrx[i]);}
   
    while(!isEmpty(M->mtrx[i])) {
      changeEntry(M,i, getCol(get(M->mtrx[i])), 0);
      if(!isEmpty(M->mtrx[i]))moveFront(M->mtrx[i]);
    }

  }//for i

  M->NNZ =0;
}



//untested as of yet
//changeEntry()
// changes the ith row, jth column of M to the value x.
//Pre: 1<=i <=size(M), 1<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
  //preconditions
  if(M == NULL){
    printf("Matrix ADT error: calling changeEntry() on NULL refrence\n");
  }
  if(i < 1 || i >size(M)){
    fprintf(stderr, "Matrix ADT error: in changeEntry() row param %d  is out of bounds\n", i);
    exit(-1);
  }
  if(j < 1 || j >size(M)){
    fprintf(stderr, "Matrix ADT error: column param is out of bounds\n");
    exit(-1);
  }
  
  //4 cases

  //put cursor on the value to change if it exists
  bool zero = true;


  if(!isEmpty(M->mtrx[i])) { moveFront(M->mtrx[i]);}


  //goes through row to place cursor on i,j element if it exists 
  for(int k=0; k< length(M->mtrx[i]); k++) {

    //if col is equals j (the column we are looking for then the value is non zero 
    //do not move the cursor forwards
    if(getCol(get(M->mtrx[i])) ==  j) {
      zero = false;
     }
    else if(getCol(get(M->mtrx[i])) < j) {
      moveNext(M->mtrx[i]);
    }
  } 

  //now cursor should be on the ijth element or the one after

  if(zero && x==0) { return;}


  if(!zero && x==0) {
    Entry toDel = NULL;
    toDel = get(M->mtrx[i]);
    freeEntry(&toDel);
    delete(M->mtrx[i]);
    M->NNZ--;
    return;
  }

  //if previously zero need to make a new Entry
  if(zero && x!=0) {
    Entry E = newEntry(j,x);
    if(!isEmpty(M->mtrx[i]) && (index(M->mtrx[i]) != -1)){ insertBefore(M->mtrx[i], E);}
    else{ append(M->mtrx[i], E);}
    M->NNZ++;
    return;
  }

  if(!zero && x!=0) {
    changeValue(get(M->mtrx[i]), x);
    return;
  }

  //ijth entry is zero and x is also zero
  
}



//copy()
//returns a reference to a new Matrix object having the same entries as A
Matrix copy(Matrix A){
  if(A == NULL){
    printf("Matrix ADT error: calling copy() on NULL refrence\n");
  }
  Matrix C = newMatrix(size(A));


  for(int i=1; i< size(A)+1; i++) {
    
    if(!isEmpty(A->mtrx[i])){moveFront(A->mtrx[i]);}
    for(int k=0; k < length(A->mtrx[i]); k++){
      int column = getCol(get(A->mtrx[i]));
      double val = getValue(get(A->mtrx[i]));      

      changeEntry(C ,i, column, val);
  
      moveNext(A->mtrx[i]);
    }//row elements

  }//go down the first column

  return C;
}

//returns a refrence to a new matrix representing the transpose of A
Matrix transpose(Matrix A){
  if(A == NULL){
    printf("Matrix ADT error: calling transpose() on NULL refrence\n");
  }
  Matrix C = newMatrix(size(A));


  for(int i=1; i< size(A)+1; i++) {
    
    if(!isEmpty(A->mtrx[i])){moveFront(A->mtrx[i]);}
    for(int k=0; k < length(A->mtrx[i]); k++){
      int column = getCol(get(A->mtrx[i]));
      double val = getValue(get(A->mtrx[i]));      

      changeEntry(C , column,i, val);
  
      moveNext(A->mtrx[i]);
    }//row elements

  }//go down the first column

  return C;
}




//sum helper function adds to lists together and returns a list of sums
List addLists(List A, List B, List S){
  //  List S = newList();

  if(!isEmpty(A)) moveFront(A);
  if(!isEmpty(B)) moveFront(B);

  while( index(A) != -1 && index(B) != -1) {
    int colA = getCol(get(A));
    int colB = getCol(get(B));    
    double valA = getValue(get(A));
    double valB = getValue(get(B));

    if(colA == colB) {  
      double elSum = valA + valB;
      if(elSum !=0){
        Entry E = newEntry(colA, elSum);
        append(S,E);      
      }
      moveNext(A);
      moveNext(B);
    }

    //if col A is larger than col B add element B to the list
    // move B cursor forwards    
    if(colA > colB) {
      
      if(valB !=0){
        //add B to the sumList
        Entry E = newEntry(colB, valB);
        append(S, E);
      }
      moveNext(B);
    }
    if(colA < colB){
      if(valA !=0) { 
        Entry E = newEntry(colA, valA);
        append(S,E);
      }//if not zero
      moveNext(A);
    }


  }//while neither curor is undefined


  //go through A if A still has elelments
  while(index(A) != -1) {
    int colA = getCol(get(A));
    double valA = getValue(get(A));
    Entry E = newEntry(colA, valA);
    append(S,E);
    moveNext(A);
  }


  //if A is at the end and B still has Elemnts add them to the list S
  while(index(B) != -1) {
    int colB = getCol(get(B));
    double valB = getValue(get(B));
    Entry E = newEntry(colB, valB);
    append(S,E);

    moveNext(B);
  }

  return S;

}




//sum()
//Returns a reference to a new Matrix obj representing A+B
//Pre: size of both matrices is the same
Matrix sum(Matrix A, Matrix B) {
  if(A == NULL || B == NULL){
    printf("Matrix ADT error: calling sum() on NULL refrence\n");
  }
  if( size(A) != size(B)) {
    fprintf(stderr, "Matrix ADT error: in sum() size of matrices are not the same size\n");
    exit(-1);
  }

  Matrix cpB = copy(B);

  Matrix AplusB = newMatrix(size(A));

  for(int i=1; i<size(A)+1; i++) {
    List toSum = newList();

    List toDel = NULL;
    toDel = AplusB->mtrx[i];
    freeList(&toDel);

    AplusB->mtrx[i] = addLists(A->mtrx[i],  cpB->mtrx[i], toSum);
    AplusB->NNZ += length(AplusB->mtrx[i]);
  }

  freeMatrix(&cpB);

  //go through new Matrix


  return AplusB;

}


//sum helper function adds to lists together and returns a list of sums
List diffLists(List A, List B, List S){

  if(!isEmpty(A)) moveFront(A);
  if(!isEmpty(B)) moveFront(B);

  while( index(A) != -1 && index(B) != -1) {
    int colA = getCol(get(A));
    int colB = getCol(get(B));    
    double valA = getValue(get(A));
    double valB = getValue(get(B));

    if(colA == colB) {  
      double elDiff = valA - valB;
      if(elDiff !=0) {
      Entry E = newEntry(colA, elDiff);
      append(S,E);      
      }
      moveNext(A);
      moveNext(B);
    }

    //if col A is larger than col B add element B to the list
    // move B cursor forwards    
    if(colA > colB) {
      
      if(valB !=0){
        //add B to the sumList
        Entry E = newEntry(colB, -1*valB);
        append(S, E);
      }
      moveNext(B);
    }
    if(colA < colB){
      if(valA !=0) { 
        Entry E = newEntry(colA, valA);
        append(S,E);
      }//if not zero
      moveNext(A);
    }


  }//while neither curor is undefined


  //go through A if A still has elelments
  while(index(A) != -1) {
    int colA = getCol(get(A));
    double valA = getValue(get(A));
    Entry E = newEntry(colA, valA);
    append(S,E);
    moveNext(A);
  }


  //if A is at the end and B still has Elemnts add them to the list S
  while(index(B) != -1) {
    int colB = getCol(get(B));
    double valB = getValue(get(B));
    Entry E = newEntry(colB, -1*valB);
    append(S,E);

    moveNext(B);
  }

  return S;

}


Matrix diff(Matrix A, Matrix B) {
  if(A == NULL || B == NULL){
    printf("Matrix ADT error: calling diff() on NULL refrence\n");
  }
  if( size(A) != size(B)) {
    fprintf(stderr, "Matrix ADT error: in diff() size of matrices are not the same size\n");
    exit(-1);
  }

  Matrix AminB = newMatrix(size(A));

  for(int i=1; i<size(A)+1; i++) {
    List toSum = newList();

    List toDel = NULL;
    toDel = AminB->mtrx[i];
    freeList(&toDel);

    AminB->mtrx[i] = diffLists(A->mtrx[i],  B->mtrx[i], toSum);
    AminB->NNZ += length(AminB->mtrx[i]);
  }

  return AminB;

}

///for diff and add can just send the previously allocated lists to addList 
//dont need to make another one and delete the first one


//scalarMult()
//Returns a refrence to a new Matrix Object representing xA
Matrix scalarMult(double x, Matrix A) {
  if(A == NULL){
    printf("Matrix ADT error: calling scalarMult() on NULL refrence\n");
  }
  Matrix scalarM = newMatrix(size(A));
  
  for(int i=1; i<size(A)+1; i++) {


    if(!isEmpty(A->mtrx[i])) { moveFront(A->mtrx[i]);}
    for(int k=0; k < length(A->mtrx[i]); k++) {
      int colA = getCol(get(A->mtrx[i]));
      double valA = getValue(get(A->mtrx[i]));
      double result = valA * x;

      

      if(result !=0) {
        changeEntry(scalarM, i, colA, result);
      }//if
      
      moveNext(A->mtrx[i]);
      
    }//for k

  }//for i

  return scalarM;

}


//dot product
double dot(List A, List B) {
  double sum = 0;

  //go through both list, if col same multiply values and add them to sum
  // if not do nothing 
  //take same loops here as in add lists
  if(!isEmpty(A)) moveFront(A);
  if(!isEmpty(B)) moveFront(B);

  while( index(A) != -1 && index(B) != -1) {
    int colA = getCol(get(A));
    int colB = getCol(get(B));    
    double valA = getValue(get(A));
    double valB = getValue(get(B));
    
    
    if(colA == colB){
       sum += (valA * valB);
       moveNext(A);
       moveNext(B);
    }
    if(colA < colB){
      moveNext(A);
    }
    if(colB < colA){
      moveNext(B);
    }
  }
  
  //once one is done then all will be zero so so not have to go through
  //the rest of the lists
  

  return sum;
}


//product()
//Returns a refrence to a new Matrix object representing A*B
//Pre: size(A) == size(B)
Matrix product(Matrix A, Matrix B) {
  if(A == NULL || B==NULL){
    printf("Matrix ADT error: calling product() on NULL refrence\n");
  }
  Matrix prodM = newMatrix(size(A));
  Matrix T = transpose(B);


  for(int i=1; i< size(A)+1; i++) {
    for(int k=1; k<size(A)+1;k++) {
      // printf("print i , k = %d, %d \n", i, k);
      double elementData = dot(A->mtrx[i], T->mtrx[k]);
      if(elementData != 0) {
        //Entry E = newEntry(k, elementData);
        changeEntry(prodM, i, k, elementData);
      }
    } 
  }


  freeMatrix(&T);
  return prodM;
}


void printMatrix(FILE* out, Matrix M) {
  if(M == NULL){
    printf("Matrix ADT error: calling printMatrix() on NULL refrence\n");
  }  
  //for loop gooes through row numbers
  for(int i=1; i < size(M)+1; i++) {


    if(length(M->mtrx[i]) >0) {
      fprintf(out, "%d:", i);    
    }

    //loop to go through row elements
    if(!isEmpty(M->mtrx[i])) { moveFront(M->mtrx[i]);}
    for(int k=0; k<length(M->mtrx[i]); k++) {

      int column = getCol(get(M->mtrx[i]));
      double value = getValue(get(M->mtrx[i]));

      // precision = floor(10*value) / 10;

      fprintf(out, " (%d, ",column);
      fprintf(out, "%.1f)", value);    

      moveNext(M->mtrx[i]);
    }
    if(length(M->mtrx[i])>0)    fprintf(out, " \n");
  }
  //fprintf(out, )
}



