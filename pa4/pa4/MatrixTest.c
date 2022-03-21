
//oooga

#include "Matrix.h"






int main(int argc, char * argv[]) {
  
  Matrix M = newMatrix(5);

  //add to empty list
  changeEntry(M, 1, 2, 6.9);

  //add before an entry
  changeEntry(M,1,1, 7.0);

  //add to entry matrix
  changeEntry(M, 5,5, 5.0);

  //add at end of list that is not empty
  changeEntry(M, 1,5, 8.2);

  //insert between too elements
  changeEntry(M, 1,3, 5.5);
  
  //replace data entry of exsitin node
  changeEntry(M, 1, 2, 3.0);


  //delete an entry 
  changeEntry(M, 1,2,0);

  changeEntry(M,2,1, 7.0);
  changeEntry(M, 4,5, 5.0);
  changeEntry(M, 4,5, 8.2);
  

  // printMatrix(stdout,M);
  // printf("\n");

  Matrix T = transpose(M);
  Matrix C = copy(M);

  //  printMatrix(stdout,M);
  //printf("\n");
  //printMatrix(stdout,T);
  //printf("\n");


  Matrix M1 = newMatrix(5);
  Matrix M2 = newMatrix(5);

  changeEntry(M1, 1 ,1, 3.5);
  changeEntry(M1, 1 ,3, 4.0);
  changeEntry(M1, 1 ,4, 1.2);
  changeEntry(M1, 1 ,5, 10.0);

  changeEntry(M1, 3,4, 3.0);
  changeEntry(M1, 3 ,2, 7.5);
  changeEntry(M1, 3 ,1, 8.5);


  changeEntry(M2, 1 ,1, 1.0);
  changeEntry(M2, 1 ,3, 2.0);
  changeEntry(M2, 1 ,2, 4.5);
  changeEntry(M2, 2 ,5, 10.0);

  changeEntry(M2, 3,3, 2.0);
  changeEntry(M2, 3 ,2, 9.5);
  changeEntry(M2, 3 ,1, 3.5);

  //printMatrix(stdout, M1);
  printf("\n");
 // printMatrix(stdout, M2);
  printf("\n");
  

  Matrix two = newMatrix(3);
  Matrix two2 = newMatrix(3);

  changeEntry(two, 1,1, 1.0);
  changeEntry(two,1,2,2.0);  
  changeEntry(two, 1,3, 3.0);
  
  changeEntry(two,2,1,4.0);  
  changeEntry(two, 2,2, 5.0);
  changeEntry(two,2,3,6.0);

  changeEntry(two,3,1,7.0);  
  changeEntry(two, 3,2, 8.0);
  changeEntry(two,3,3,9.0);
  
  changeEntry(two2,1,1,1.0);  
  changeEntry(two2, 1,3, 1.0);
  changeEntry(two2,3,1,1.0);

  changeEntry(two2,3,2,1.0);  
  changeEntry(two2, 3,3, 1.0);
  // changeEntry(two,2,3,6.0);

  //matrix A
  printf("Matrix A:\n");
  printMatrix(stdout, two);
  printf("\n");
  printf("Matrix B\n");
  printMatrix(stdout,two2);
  printf("\n");
  
  Matrix TB = transpose(two);
  printf("A transpose\n");
  printMatrix(stdout, TB);

  Matrix SCAL = scalarMult(1.50, two);

   Matrix SUM = sum(two, two2);

   Matrix DIFF = diff(M1, M2);

   Matrix PROD = product(two, two2);

   // printMatrix(stdout, SUM);
  printf("\n");
  //printMatrix(stdout, SCAL);
  printf("the product of M1 and M2\n");
  printMatrix(stdout, PROD);

  //makeZero(M);
  //printMatrix(stdout,M);

  freeMatrix(&TB);
  freeMatrix(&PROD);
  freeMatrix(&SCAL);
  freeMatrix(&DIFF);
  freeMatrix(&two2);
  freeMatrix(&two);
  freeMatrix(&SUM);
  freeMatrix(&M2);
  freeMatrix(&M1);
  freeMatrix(&T);
  freeMatrix(&C);
  freeMatrix(&M);
  

  return 0;
}

