//-----------------------------------------------------------------------------      
//Colton Jeffrey                                                                     
//cwjeffre                                                                           
//pa2                                                                                
//                                                                                   
// FindPath.c                                                                           
// this file takes specifically formatted input and outputs the adj list rep 
// of the graph as well as shortest paths as instucted by input file
//                                         
//-----------------------------------------------------------------------------      


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"

//manipulates infile and writes correct output to outfile
void adjAndPath(FILE* in, FILE* out);

//prints paths in correct fromat from source to dest
void printPath(FILE* out,List L, int source, int dest);

#define MAX_LEN 20

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

  adjAndPath(in,out);


  fclose(in);
  fclose(out);

  return 0;
}

void adjAndPath(FILE* in, FILE* out) {
  bool first = true;
  // FILE *in, *out;
  char line[MAX_LEN];
  char* token;
  int v1=0;
  int v2=0;   
  Graph G = NULL;  
  bool firstInt = true;
  bool search = false;
  // read each line of input file, then count and print tokens
  while( fgets(line, MAX_LEN, in) != NULL)  {

    // get first token
    token = strtok(line, " \n");
      
    first = true;  
    while( token!=NULL ){ // we have a token


      if(first) {
        v1 = strtol(token, NULL, 10);
        
        first=false;
     }
      else{
         v2 = strtol(token, NULL, 10);
	 // printf("%d\n ",v2);
       }
      // get next token
      token = strtok(NULL, " \n");
    }//while going through lines and getting tokens
    
    //should have the line tokensized into one or two strings

    if(firstInt) {
      G = newGraph(v1);
      firstInt = false;
    }
    else{  
      if( (v1==0 && v2==0) && !search){
        search = true;
        printGraph(out,G); //something like this to print adjList of g
      }
      if(!search) { 
        addEdge(G, v1, v2);
      } //might have to make a g here first
      else if(v1 !=0 && v2 !=0){
        List L = newList();
       
        BFS(G,v1);            //run bfs on source vertex
        getPath(L,G,v2);     //run findpath on the destination vertex
        printPath(out,L,v1,v2); 

        freeList(&L);
      }
    }
    token = strtok(NULL," \n");


  }//main while loop to go through in file
   
  freeGraph(&G);

}


void printPath(FILE* out,List L, int source, int dest){
  fprintf(out,"\n"); 

  bool destFound = false;

  if(!isEmpty(L)){  moveFront(L);}
  for(int i=0; i<length(L); i++){
    if(get(L) == dest) destFound =  true;
    moveNext(L);
  }


  if(destFound){
    fprintf(out, "The distance from %d to %d is %d\n", source, dest, length(L)-1);
    fprintf(out, "A shortest %d-%d path is: ",source,dest);
    printList(out,L);
    fprintf(out,"\n");
    //add an endline here
  }

  else{
    fprintf(out, "The distance from %d to %d is infinity\n", source, dest);
    fprintf(out, "No %d-%d path exists\n",source, dest);
  }
  //fprintf(out, "\n");
}









