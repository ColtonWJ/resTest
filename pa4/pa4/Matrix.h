//-----------------------------------------------------------------------------      
//Colton Jeffrey                                                                     
//cwjeffre                                                                           
//pa4                                                                                
//                                                                                   
//Matrix.h
//header file for Matrix ADT
//-----------------------------------------------------------------------------


#ifndef MATRIX_H_INCLUDE_
#define MATRIX_H_INCLUDE_


#include<stdlib.h>
#include <stdio.h>
#include <math.h>
#include "List.h"




// Exported type
typedef struct MatrixObj* Matrix;


// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state. 
Matrix newMatrix(int n);


// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM);


// Access functions


// size()
// Return the size of square Matrix M.
int size(Matrix M);


// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M);


// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise. 
int equals(Matrix A, Matrix B);


// Manipulation procedures



// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M);


// changeEntry()
// Changes the ith row, jth column of M to the value x.
 // Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x);


// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A
Matrix copy(Matrix A);


// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A);


// scalarMult()
// Returns a reference to a new Matrix object representing xA
Matrix scalarMult(double x, Matrix A);


// sum()
// Returns a reference to a new Matrix object representing A+B
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B);


// diff()
// Returns a reference to a new Matrix obj representing A-B
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B);

// product()
// Returns a reference to a new Matrix obj representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B);


//prints matrix in correct formatt
void printMatrix(FILE* out, Matrix M);

//may need private helper funtions like Vector Dot and such




#endif
