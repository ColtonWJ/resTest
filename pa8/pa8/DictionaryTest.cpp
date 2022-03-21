//-----------------------------------------------------------------------------
//Colton Jeffrey
//cwjeffre
//pa8
//
//Dictionary ADT test file
//
//---------------------------------------------------------------------------



#include "Dictionary.h"
using std::cout;
using std::endl;




int main() {

  Dictionary A;
  
  A.setValue("a", 76);
  A.setValue("b", 60);
  A.setValue("c", 67);
  A.setValue("d", 89);
  A.setValue("e",78);
  
  A.setValue("f", 57);
  A.setValue("g", 79);
  A.setValue("h", 78);
  A.setValue("i",7);
  A.setValue("j",8);
  A.setValue("k",9);
  A.setValue("ja", 8);
  A.setValue("jab", 9);
  A.setValue("jbd", 10);
  A.setValue("jaab", 67);
  A.setValue("jaaa", 100);
  A.setValue("jaaaab", 78);
  A.setValue("jbd", 69);
 
  cout << A.pre_string() << endl;
  
  A.remove("f");
  
  
  A.remove("k");
  A.remove("jaaa");
  A.remove("d");
  cout << A.pre_string() << endl;
  
  A.begin();
  for(int i = 0; i < A.size(); i++){
    cout << A.currentKey() << " : " << A.currentVal() << endl;
    A.next();
  }
  
  if(A.contains("jaab")) cout << "a contains jabb\n";
  
  A.end();
  A.remove(A.currentKey());
  if(A.hasCurrent()) cout << "shouldnt have current\n";
  
  A.clear();
  
  cout << "A after clear() :\n" << A << endl;

  Dictionary B;
  
  B.setValue("k", 60);
  B.setValue("j", 67);
  B.setValue("i", 89);
  B.setValue("h",78);
  B.setValue("g", 57);
  B.setValue("f", 79);
  B.setValue("e", 78);
  B.setValue("d",7);
  B.setValue("c",8);
  B.setValue("b",9);
  B.setValue("ea",6);
  B.setValue("eaa", 7);
  B.setValue("eab", 6);

  cout << B.pre_string() << endl;



  return 0;
}


