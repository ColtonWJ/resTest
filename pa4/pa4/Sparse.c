




#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"Matrix.h"


#define MAX_LEN 20

void matrixOps(FILE* in, FILE* out);

int main(int argc, char * argv[]){
  FILE *in, *out;

  // check command line for correct number of arguments
  if( argc != 3 ){
    printf("Usage: %s <input file> <output file>\n", argv[0]);
    exit(1);
  }

  // open files for reading and writing 
  in = fopen(argv[1], "r");
  if( in==NULL ){
    printf("Unable to open file %s for reading\n", argv[1]);
    exit(1);
  }

  out = fopen(argv[2], "w");
  if( out==NULL ){
    printf("Unable to open file %s for writing\n", argv[2]);
    exit(1);
  }

  matrixOps(in, out);

  fclose(in);
  fclose(out);


  return 0;
}

void matrixOps(FILE* in, FILE* out){
   
  char line[MAX_LEN];
  char* token;

  Matrix A = NULL;
  Matrix B = NULL;
  
  int row=0;
  int col=0;
  double value =0;
  
  int tokenCount =0;
  int sectionNumber =1;
  
  
   
    
    while( fgets(line, MAX_LEN, in) != NULL)  {
    
    token = strtok(line, " \n");
    
    if( line[0] == '\n'){ sectionNumber++;}
    else{ //if the line is blank then just go back to the top of the while loop
      tokenCount =1;
      while(token != NULL) {
    
        if(tokenCount ==1) {
          row = strtol(token, NULL, 10);
        }
      
        if(tokenCount ==2){
          col = strtol(token, NULL, 10);
        }
        if(tokenCount ==3){

          char* pEnd;
	  // double d2;
          value = strtod(token, &pEnd);
	  // d2 = strtod (pEnd, NULL);

	  //   value = (double)strtol(token, NULL, 10);
          // printf(" should be double: %.1f \n", value);

        }
        tokenCount++;
      

        token = strtok(NULL, " \n"); 
      }//while through tokens    


      if(sectionNumber == 1) {
        A = newMatrix(row);
        B = newMatrix(row);

      }
      if (sectionNumber ==2 ){
        changeEntry(A,row, col, value);
      }
      if(sectionNumber ==3){
        changeEntry(B, row, col, value); 
      }
    }//else for it not being a blank line

    
  }//file while loop


    fprintf(out,"A has %d non-zero entries:\n", NNZ(A));
    printMatrix(out, A);
    fprintf(out, "\n");

    fprintf(out, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(out,B);
    fprintf(out, "\n");


    fprintf(out, "(1.5)*A =\n");
    Matrix scalMult = scalarMult(1.5,A);
    printMatrix(out, scalMult);
    fprintf(out, "\n");

    fprintf(out, "A+B =\n");
    Matrix ABsum = sum(A,B);
    printMatrix(out, ABsum);
    fprintf(out,"\n");

    fprintf(out, "A+A =\n");  
    Matrix AAsum = sum(A,A);
    printMatrix(out, AAsum);
    fprintf(out,"\n");

    fprintf(out, "B-A =\n");
    Matrix BAdiff = diff(B,A);
    printMatrix(out, BAdiff);
    fprintf(out,"\n");


    fprintf(out, "A-A =\n");
    Matrix AAdiff = diff(A,A);
    printMatrix(out, AAdiff);
    fprintf(out,"\n");

    fprintf(out, "Transpose(A) =\n");
    Matrix TA = transpose(A);
    printMatrix(out, TA);
    fprintf(out,"\n");

    fprintf(out, "A*B =\n");
    Matrix ABprod = product(A,B);
    printMatrix(out, ABprod);
    fprintf(out,"\n");

    fprintf(out, "B*B =\n");
    Matrix BBprod = product(B,B);
    printMatrix(out, BBprod);
    fprintf(out,"\n");

    freeMatrix(&TA);
    freeMatrix(&B);
    freeMatrix(&A);
    freeMatrix(&BBprod);
    freeMatrix(&ABprod);
    freeMatrix(&AAdiff);
    freeMatrix(&BAdiff);
    freeMatrix(&AAsum);
    freeMatrix(&ABsum);
    freeMatrix(&scalMult);


}





