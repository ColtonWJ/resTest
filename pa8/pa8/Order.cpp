//-----------------------------------------------------------------------------
//Colton Jeffrey
//cwjeffre
//pa8
//
//Order.cpp
//
//Dictionary ADT client file
// takes in a Dictionary for a file and outputs in order and pre order
//
//---------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include "Dictionary.h"
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::cerr;


int main(int argc, char * argv[]){

  ifstream in;
  ofstream out;

   // check command line for correct number of arguments
   if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }

   // open files for reading and writing 
   in.open(argv[1]);
   if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }

   out.open(argv[2]);
   if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }
   
   
  Dictionary A;
  int counter = 1;  
  std::string line;

  while(std::getline(in, line)){
    A.setValue(line, counter);
    counter++;
  }
   
  out << A << endl;
  
  out << A.pre_string() << endl;
   
  out.close();
  in.close(); 
   
  return 0;
}











