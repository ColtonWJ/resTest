//-----------------------------------------------------------------------------
//Colton Jeffrey
//cwjeffre
//pa6
//
//BigInteger.cpp
//
//Big Integer ADT implementation file
//---------------------------------------------------------------------------


#include <stdexcept>
#include "BigInteger.h"
using std::cout;
using std::endl;

const long base = 1000000000;
const int power = 9;



//default constructor makes number 0
BigInteger::BigInteger(){
  signum =0;
  digits = List();
}


// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){

  signum =1;   //by default

  if(s.size() == 0){
    throw std::invalid_argument ("BigInteger: Constructor: empty string");
  }
  
  
  
  int strIndex = s.length() -1;
  
  int endHere =0;
  if(s[0] == '-'){
    signum = -1;
    endHere = 1;
  }
  if(s[0] == '+'){
    endHere = 1;
    if(s.size() == 1) {
      throw std::invalid_argument ("BigInteger: Constructor: non-numeric string");
    }
  }


  //start at end of string go though to begening of string
  while(strIndex >= endHere){
    std::string el;
    int indexStart = strIndex - power +1;
    if(indexStart < endHere) indexStart =endHere;
    
    int indexEnd = strIndex;
    
  
  //for loop go through strIndex - pow back to strIndex to form an List el
    for(int i = indexStart; i <= indexEnd; i++){
      el += s[i];
       if(s[i] < '0' || s[i] > '9'){
          throw std::invalid_argument ("BigInteger: Constructor: non-numeric string");
        }
        strIndex--;
    }//for
    
    digits.insertAfter(stol(el));
    
  
  
  } 

  digits.moveFront();
  while(digits.front() == 0 && digits.length() > 1){
      digits.eraseAfter();
  }
  digits.moveFront();
  if(digits.front() == 0) {digits.eraseAfter();}
  if(digits.length() == 0) signum =0;

}




// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N) {

 signum = N.signum;
 digits = List(N.digits);

}

// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const {
  return signum;
}




// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{
  if(signum > N.sign()){ return 1;}
  if(signum < N.sign()){return -1;}
  
  if(digits.length() > N.digits.length()){
    if(signum == -1)return -1;
    return 1;
  }
  if(digits.length() < N.digits.length()){
    if(signum == -1) return 1;
    return -1;
  } 
  
  //at this point the signs are the same and the sizes are the same
  //go through each digit list and compair the individual elements
  //start at front of each list and go through each simaltaniously
  
  List thisList = digits;
  List nList = N.digits;
  
  thisList.moveFront();
  nList.moveFront();
  for(int i =0; i < thisList.length(); i++){
  
    if(thisList.peekNext() > nList.peekNext() ){
      if(signum == 1) {return 1;}
      return -1;
    }
    if(thisList.peekNext() < nList.peekNext()){
      if(signum == 1) return -1;
      return 1;
    }
  
    thisList.moveNext();
    nList.moveNext();
  }

  return 0;

}


// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
  signum =0;
  digits.clear();
  //digits.insertAfter(0);
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate(){
  if(signum == -1) {
    signum =1;
    return;
  }
  if(signum == 1) {
    signum = -1;
    return;
   }
}



// helpers -------------------------------------------------


// shiftList()
// appends p zero digits to L, multiplying
void shiftList(List& L, int p){

  L.moveBack();
  for(int i =0; i < p; i++){
    L.insertBefore(0);
  }

}



// scalarMultList()
// Multiplies L (considered as a vector) by
void scalarMultList(List& L, ListElement m){


  L.moveBack();
  for(int i=0; i< L.length(); i++){
    
    long temp = L.peekPrev();
    L.setBefore(temp * m);
    
    L.movePrev();
  }



}





// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L){

  L.moveFront();
  for(int i=0; i < L.length(); i++){
    long temp = L.peekNext();
    temp = temp * -1;
    L.setAfter(temp);
  
    L.moveNext();
  }

}


// normalizeList()
// Performs carries from right to left (least to most significant 
// digits), then returns the sign of the resulting integer. Used 
// by add(), sub() and mult().
int normalizeList(List& L){

  //go through the list from the lest sig element
  //if the value is >= base then you have to carry 
  //subtract by the base to get value within range 
  int toReturn = 1;
  


  if(L.length() > 0){
  if(L.front() < 0){
    toReturn =-1;
    negateList(L);
  }
  }else return 0;

  
  
  int initLength = L.length();
  
  int carry = 0;
  L.moveBack();
  for(int i=0; i < L.length(); i++){
    double keep =0;
    long temp = L.peekPrev() + carry;
    carry =0;
    
    L.setBefore(temp);
    

    
    //if out of range above
    if(temp >= base){
    
    keep = temp % base; 
    carry = (temp - keep) / base;
    L.setBefore(keep);
    
    }
    else {carry =0;}
    
    //if out of range below
    if(temp <0){
      //cout << "i = " << i << endl;
      if(temp < -1* base || i < (initLength -1)){
      
      keep = (temp % base); 
      if(keep < 0){
        keep += base;
        carry =-1;
      } 
      carry += (temp - (temp % base)) / base;
      L.setBefore(keep);
      
      
      }//if temp if less than -base or you are before the last value of o list
    
    }
   
    
    
    L.movePrev();
  }//main for loop
  
  if(carry > 0){
    L.insertBefore(carry);
  }
  L.moveFront();
  
  if(L.peekNext() == 0){
    L.eraseAfter();
  }
  
  
  
  //if the front of the list is 0 then delete it
  L.moveFront();
  if(L.length() > 0){
    while(L.front() == 0){
      L.eraseAfter();
      if(L.length() == 0) {return 0;}
    }
    if(L.length() == 0) toReturn = 0;
  }
  
  //if the front element is negative
  if(L.length() > 0){
    if(L.front() < 0){
      negateList(L);
      normalizeList(L);
      toReturn = -1;
    } 
  }
  
  return toReturn; 

}





// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors). // Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn){

  if(sgn == -1){
    negateList(B);
  }
  
  
  
  S.clear();
  
  //start at least significant element for both bigInts and add through like
  //a vector
  bool Blonger=false;
  
  int ll2;
  int loopLength;
  if(A.length() >= B.length()){
    loopLength = B.length();
    ll2 = A.length();
  }
  else {
    loopLength = A.length();
    ll2 = B.length();
    Blonger = true;
  }
  
  
  long vsum=0;

  
  A.moveBack();
  B.moveBack();
  for(int i=0; i < loopLength; i++){
    vsum = A.peekPrev() + B.peekPrev();
    
    S.insertAfter(vsum);
    
    
    A.movePrev();
    B.movePrev();
  }
  
  for(int i = loopLength; i < ll2; i++ ){
   if(Blonger){
     S.insertAfter(B.peekPrev());
     B.movePrev();
   }
   else{
     S.insertAfter(A.peekPrev());
     A.movePrev();
   }
  
  }


}




// BigInteger Arithmetic operations ----------------------------------------




// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{
  BigInteger S; 
  
  List copyThis = digits;
  List copyN = N.digits;
  
  if(signum == -1) negateList(copyThis);
  if(N.sign() == -1) negateList(copyN);
  
  sumList(S.digits, copyThis, copyN, 1);
  S.signum = normalizeList(S.digits);

  return S;

}


// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
  BigInteger S;
  
  List copyThis = digits;
  List copyN = N.digits;
  
  if(signum == -1) negateList(copyThis);
  if(N.sign() == -1) negateList(copyN);
  
  sumList(S.digits, copyThis, copyN, -1);
  S.signum = normalizeList(S.digits);
  
  return S;

}



// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const{


  
  BigInteger S;
  S.digits.clear();
  
  List copyThis = digits;
  
  
  //List prod;
  List temp;
  long scalMult =0;
  
  if(copyThis.length() != 0) copyThis.moveBack();
  for(int i=0; i< copyThis.length(); i++){
    
    //scalar mult
    scalMult = copyThis.peekPrev();    
    temp = N.digits;
    scalarMultList(temp, scalMult);
    
    
    //shift scalar multiplied list
    shiftList(temp, i);
    
    
    //sum shifted list (temp) with prod and set prod equal to that sum
    List prodHolder;
     sumList(prodHolder, temp, S.digits, 1);
     S.digits = prodHolder;

    normalizeList(S.digits);
    
  
    copyThis.movePrev();
  }
  

  S.signum = signum * N.sign();
  
  return S; 
  
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string(){


//print 0 if empty

  std::string numRep;
  
  if(signum == -1 ) numRep = '-';
  
  List temp = digits;
  
  temp.moveFront();
  
  bool first = true;
  for(int i=0; i < temp.length(); i++){
    std::string block = std::to_string(temp.peekNext());
    while(block.length() < power && !first){
      block = '0' + block;
    }
    first = false;
    
    numRep += block;
    temp.moveNext();
  }
  
  if(digits.length() == 0){
    numRep = '0';
  }
  
  return numRep;
}

 // Overriden Operators -----------------------------------------------------
   
  // operator<<()
  // Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
  return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
  if(A.compare(B) == 0){
    return true;
  }
  return false;
}

  // operator<()
  // Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
  if(A.compare(B) == -1){
    return true;
  }
  return false;
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
  if(A.compare(B) == 0 || A.compare(B) == -1){
    return true;
  }
  return false;
}

  // operator>()
  // Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
  if(A.compare(B) == 1){
    return true;
  }
  return false;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
  if(A.compare(B) == 0 || A.compare(B) == 1){
    return true;
  }
  return false;
}


// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
    return A.add(B);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
  //BigInteger temp = A.add(B);
  A = A.add(B);
  return (A);

}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
  return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
  //BigInteger temp = A.sub(B);
  //temp = A - temp;
  A = A.sub(B);
  return (A);
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
   return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
  A = A.mult(B);
  return A;
  
}


