//-----------------------------------------------------------------------------
//Colton Jeffrey
//cwjeffre
//pa6
//
//Arithmetic.cpp
//
//BigInteger ADT client file
// takes in BigIntegers A and B from file and outputs various 
//arithmetic operations on the BigIntegers and sends result to output file
//---------------------------------------------------------------------------


#include <iostream>
#include <fstream>
#include <string>
#include "List.h"
#include "BigInteger.h"
using std::cout;
using std::endl;
//using std::getline;
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

   std::string line;
   std::string Anum;
   std::string Bnum;
   bool first = true;
   while(std::getline(in, line)){
     if(first){
       Anum = line;
       first = false;
     }
     else{ Bnum = line;}
   
   }//while


  BigInteger A(Anum);
  BigInteger B(Bnum);
  
  BigInteger three("3");
  BigInteger two("2");
  BigInteger nine("9");
  BigInteger sixteen("16");
  
  out << A << endl << endl
      << B << endl << endl
  
      << A+B << endl << endl
  
      << A-B << endl << endl
  
      << A-A << endl << endl
      
      << three * A - two * B << endl << endl
      << A * B << endl << endl
      <<  A * A << endl << endl
      << B * B << endl << endl
      << (nine * A * A * A * A) + sixteen * (B * B * B * B * B) << endl << endl;

  
  
  
  in.close();
  out.close();

  return 0;
}







