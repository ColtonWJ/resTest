//-----------------------------------------------------------------------------
//Colton Jeffrey
//cwjeffre
//pa2
//
//GraphTest.c
// GraphTest file for testing graph ADT
// 
//-----------------------------------------------------------------------------




#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"




int main(int argc, char* argv[]){
  //  Graph P = newGraph(3);


  //  addEdge(P, 1,2);

  // printGraph(stdout,P);  

  // freeGraph(&P);  
  
  Graph G = newGraph(6);
 
  addEdge(G, 1,2);
  addEdge(G,1,3);
  addEdge(G, 3,4);
  addEdge(G, 2,4);
  addEdge(G, 4,5);
  addEdge(G, 2, 5);
  addEdge(G, 5,6);
  addEdge(G, 6,2);

  printGraph(stdout, G);


  List L = newList();
  List E = newList();

  int i=0;  
  int d=0;
  int n=6;
  int max=0;
  

  // Calculate the eccentricity of each vertex 
  for(int s=1; s<=n; s++){
    BFS(G, s);
    max = getDist(G, 1);
    for(i=2; i<=n; i++){
      d = getDist(G, i);
      max = ( max<d ? d : max );
    }
    append(E, max);
  }


  printf("list of maxes: ");
  printList(stdout,E);

  //  BFS(G,3);  
  // getPath(L, G, 5);

  // for(int i=0; i < length(L); i++) {

  //  printList(stdout,L);
 

  freeList(&L);
  freeList(&E);  

  freeGraph(&G);
  

  return 0;
}




