//-----------------------------------------------------------------------------
//Colton Jeffrey
//cwjeffre
//pa6
//
//BigIntegerTest.cpp
//
//Test file for BigInteger ADT
//---------------------------------------------------------------------------


#include "BigInteger.h"
using std::cout;
using std::endl;


int main() {

  //testing constructors
  
  cout << "testing constructors ----------------------\n";

  BigInteger big("76865455346790087665432245678865445768777754534222244545465");
  cout << "big = " <<big << endl;

  BigInteger start("987654321");
  cout << "start easy = " << start << endl;
  
  BigInteger z("0");
  BigInteger negStart("-987654321");
  cout << "negative start easy = " << negStart.to_string() << endl;


  cout << "\ntesting compair --------------------------\n";
  //testing comp

  BigInteger A("504030204");  cout << "A = "<<A.to_string() << endl;
  BigInteger C("504030256");  cout << "C = "<< C.to_string() << endl;


  std::cout << "A comp C (-1) " << A.compare(C) << std::endl;
  std::cout << "C comp A (1) " << C.compare(A) << std::endl;

  BigInteger B(A);
BigInteger pos("+253324616");
BigInteger neg("-4");

  cout << "A comp A (0) " << A.compare(B) << std::endl;
  
  std::cout << "signage comp pos comp neg (1) " << pos.compare(neg) << std::endl;
  std::cout << "signage comp neg comp pos (-1)) " << neg.compare(pos) << std::endl;  

  
  cout <<"\n testing to_string() -------------------\n";
  
    cout << "pos = " << pos.to_string() << endl;
    cout << "neg = " << neg.to_string() << endl;
  

  BigInteger moreELs("77777777"); cout << "moreEls = " << moreELs.to_string() << endl;
  BigInteger lessEls("34534");  cout << "lessEls = " << lessEls.to_string() << endl;
  
  cout << "MoreELs comp Less els positive (1) " << moreELs.compare(lessEls) << endl;
  cout << "LessEls comp moreELs positive (-1) " << lessEls.compare(moreELs) << endl; 

 BigInteger zero("10000000000000000000420000");
 cout << "BigInt w lots of zeros = " << zero.to_string() << endl;
 
 
 //testing make zero 
 
 cout <<"\ntesting make_zero ---------------------------\n";
 
 zero.makeZero(); cout << "zero make zero should be zero = "<< zero << endl;
 neg.makeZero(); cout << "neg make zero = " << neg << endl;
 
 //test negate
 cout << "\n testing negate (sign change) ---------------------------\n";
 
 negStart.negate(); cout << "negStart sign should be + = " <<negStart.sign() << endl;
 start.negate(); cout <<  "start should now be - = " << start.sign() << endl;
 zero.negate(); cout << "sign should stay 0 = " << zero.sign() << endl;
 
 //testing add
 cout << endl << "\ntesting add function ----------" << endl; 
 
   BigInteger sum1("355797"); 
   cout << "sum1 = " << sum1 << endl;
   BigInteger sum2("149082");
   cout << "sum2 = " << sum2 << endl;
   //sum1.add(sum2);
  // cout << "sum1 +sum2 = "; 
   cout << "sum1 + sum2 (504879) =" << sum1.add(sum2) << endl;
   //List sumT(sum1.add(sum2));
   //cout << "sum1 + sum2 = " << sumT << endl;
   
   //this one has a carry
   BigInteger s3("882133"); cout << "s3 = " << s3 << endl;
   BigInteger s4("659179"); cout << "s4 = " << s4 << endl;
   
   cout << "s3 + s4 (1541312) = " << s3.add(s4) << endl;
   
 
  BigInteger s5("862936961074610698154951864041036478");
  cout << "s5 + s3 (862936961074610698154951864041918611) = " << s5.add(s3) << endl;
  BigInteger s5c("862936961074610698154951864041918611"); 
  cout << "should be zero if pass = " << s5c.compare(s5.add(s3)) << endl;
  
  
  BigInteger s6("123"); cout << "s6 = " << s6 << endl;
  cout << "s6 + s3 (882256) = " << s6.add(s3) << endl;
  
  
 cout << "add some negative numbers\nnegative s4 + s3 " << endl;
 BigInteger negs4("-659179");
 cout << s3.add(negs4) << endl; 
 BigInteger gg("222954");
 if(s3.add(negs4).compare(gg) == 0){
   cout << "pass\n";
 }else cout << "failed\n";
 
 BigInteger negs3("-882133");
 BigInteger ggg("-222954");
 cout << s4.add(negs3) << endl;
 if(s4.add(negs3).compare(ggg) == 0){
   cout << "pass\n";
 }else cout << "failed\n";
 
 cout << "\n two pretty big numbers\n";
 BigInteger gggg("-91663005341394007696205856211480207");
 BigInteger a1("987163419692578320651604657160601");
 BigInteger a2("-92650168761086586016857460868640808");
 cout << a2.add(a1) << endl;
 if(a1.add(a2).compare(gggg) == 0){
   cout << "pass\n";
 }else cout << "failed\n";
 
 
 cout << a2.add(negs4) <<endl;


 BigInteger a3("-8640");
 BigInteger a4("-956");
 cout << a3.add(a4) << endl;

BigInteger a5("-97669989889899000088987793977189889889");
BigInteger a6("-899887799679000999790008798779880900900000988878");
BigInteger nega6("899887799679000999790008798779880900900000988878");
cout << a5.add(a6) << endl;
BigInteger tt("-899887799776670989679907798868868694877190878767");

 if(a6.add(a5).compare(tt) == 0){
   cout << "pass\n";
 }else cout << "failed\n";

BigInteger a7("7189889889");
BigInteger a8("0988878");
BigInteger bp("7190878767");

cout << a7.add(a8) << endl;
 if(a7.add(a8).compare(bp) == 0){
   cout << "pass\n";
 }else cout << "failed\n";

//now on to sub breh

cout << "\nnow testing sub------------------ \n \n";

BigInteger no("7188901011");
cout << a7.sub(a8) << endl;
 if(a7.sub(a8).compare(no) == 0){
   cout << "pass\n";
 }else cout << "failed\n";

cout << a8.sub(a7) << endl;



BigInteger ttt("899887799581331009900109798690893106922811098989");
cout << a5.sub(a6) << endl;
 if(a5.sub(a6).compare(ttt) == 0){
   cout << "pass\n";
 }else cout << "failed\n";

BigInteger zp("0000000000000000");
cout << endl << zp << endl;


BigInteger boof;


  cout << "\ntesting multiplication --------------------------\n";
  
  BigInteger m1("123");
  BigInteger m2("456");
  
  cout << m1 << " * " << m2 << " = " << m1.mult(m2) << endl; 

  BigInteger m3( "999" );
  BigInteger m4("999");
  cout << m3 << " * " << m4 << " = " << m3.mult(m4) << endl;
  
  
  BigInteger b1("9163574346363325007361058");

  BigInteger b2("+4597814412658653960738664");
  BigInteger b2c(b2);
  BigInteger b2sqr("21139897373251643090844048049647865537964504504896");
  
  //cout << b2 << " * " << b2c << " = " << b2 * b2c << endl;
  //if(b2sqr == (b2 * b2c)) cout << "passed above\n";
  //else cout << "failed above\n";
 
  BigInteger b3("8977726345662");
  BigInteger b4("87996246263");
  BigInteger b34("790006218394696413761106");
  BigInteger b343 = b3 * b4;
  cout << b343 << endl;
  cout << b34 << endl;
  if(b34 == b343) cout << "suggseess \n";
  else {cout << "no work\n";}
  
  /*
  //cout << "b3 = " << b3 << endl << "b4 = " << b4 << endl;
  BigInteger b3("89734562");
  BigInteger b4("879263");
  BigInteger b34("78900280187806");
  BigInteger b343 = b3 * b4;
  cout << b343 << endl;
  cout << b34 << endl;
  if(b34 == b343) cout << "suggseess \n";
  else {cout << "no work\n";}  
  */
  //do some mult test on big bases and big numbers baby
  //then overload everything 
 
  cout << "\ntesting overloads ----------------------\n";
  
  if(m1 == m2) cout << "equal \n";
  else  cout << "unequal \n";
  
  if(m3 == m3) cout << "equal \n";
  else{cout <<  "unequal \n";}
  
  if(m1 > m2) cout << "m1 greater m2\n";
  else cout << "m1 less than m2 should be this one\n";
  
  if(m1 < m2) cout << "m1 less than m2 \n";
  else cout << "m1 greater than m2\n";
  
  if(m3.mult(m4) == (m3 * m4)){
    cout << "* overload worked\n";
  }
  else cout << "* overload didnt work\n";
  
  if(m3.add(m2) == (m3 + m2)) {cout << "+ op overload worked\n";}
  else{cout << "plus op overload no work\n";}
  
  if(m3.sub(m2) == (m3 - m2)) cout << "- op overload worked\n";
  
  
  //string s1 = "9128734667000004389234563456345619187236478";
  //string s3 = "9876545439000000000000000200000000000006543654365346534";
  
  //BigInteger A = BigInteger(s1);
  //BigInteger B = BigInteger(s3);

  
  BigInteger lik;
  BigInteger bik;
  lik = BigInteger("+13378008135");
  cout << lik << endl;
  lik.makeZero();
cout << lik.sign() << endl;
  bik = BigInteger();
  cout << bik.sign() << endl;
  
  if(bik == lik){ cout << "yas queen" << endl;}



cout << "\n\n\n\n";


   BigInteger AA;
   BigInteger BB;
   BigInteger CC;
   BigInteger DD;

    AA = BigInteger("111122223333");
    BB = BigInteger("111122223333");
    CC = BigInteger();
    DD = BigInteger("12348148518469129628889");

    // pos * pos = pos
    CC = AA * BB;
    //cout << "before compare \n";
    if (CC.sign() != 1){
      cout << "failed first\n;";
    } else cout << "success \n";
    if (!(CC == DD)) cout << "failed second\n";
    else cout << "sucess \n";

    // pos * neg = neg
    BB.negate();
    DD.negate();
    CC = AA * BB;
    if (CC.sign() != -1) cout << "failed third\n";
    else cout << "success 3\n";
      
    if (!(CC == DD)) cout << "failed fourth\n";
    else cout << "success 4\n";

    BB.makeZero();
    cout << "made zero \n";
    CC = AA * BB;
    cout << "after mult \n";
        if (CC.sign() != 0)  cout << "failed fith\n";
    else cout << "success 5\n";
      


  BigInteger cool;
  
  
  
  BigInteger j1("98");
  BigInteger j2("996");
  cout << j1 -j2 << endl;
  
  
  

  return 0;
}