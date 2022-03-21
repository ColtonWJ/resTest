//-----------------------------------------------------------------------------
//Colton Jeffrey
//cwjeffre
//pa8
//
//Dictionary ADT implementation file
//
//---------------------------------------------------------------------------

//now just gotta do the delete stuff


#include "Dictionary.h"
using std::cout;
using std::endl;
using std::string;

const int RED = 1;
const int BLACK = 0;

//node constructor
Dictionary::Node::Node(keyType k, valType v){
  key = k;
  val = v;
  parent = nullptr;
  left = nullptr;
  right = nullptr;
  color = BLACK;     //or maybe this is black we shall see
}

//dictionary constructor
//creates dictionary object in the empty state
Dictionary::Dictionary(){
   Node* newNode = new Node("\000", -666666);
   nil = newNode;
   root = nil;
   current = nil;
   num_pairs = 0;
}


// Copy constructor.
Dictionary::Dictionary(const Dictionary& D){
   Node* newNode = new Node("\000", -666666);
   nil = newNode;
   root = nil;
   current = nil;
   num_pairs = 0;

  //need to get last el in preOrder
  preOrderCopy(D.root, D.nil);
}

Dictionary::~Dictionary(){

  postOrderDelete(root);
  delete nil; nil = nullptr;
}


//private helpers -----------------------------------------------------------


// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){
  if(R != N){
    
    setValue(R->key, R->val);
    preOrderCopy(R->left, N);
    preOrderCopy(R->right, N);    
  }

}


   // inOrderString()
   // Appends a string representation of the tree rooted at R to string s. The
   // string appended consists of: "key : value \n" for each key-value pair in
   // tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const{
  if(R == nullptr){return;}
  if (R != nil){
    inOrderString(s,R->left);
    s += (R->key + " : " +std::to_string(R->val) + '\n');
    inOrderString(s, R->right);
  }
  


}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const{
if(R == nullptr){  return;}
  
  if (R != nil){
    s += (R->key + '\n');  
    preOrderString(s,R->left);
    preOrderString(s, R->right);

  }
  
}


// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R){
  Node* temp;
  
  if(R!= nil){
    postOrderDelete(R->left);
    postOrderDelete(R->right);
    temp = R;
    temp->right = temp->left = nullptr;
    delete temp; temp =nullptr;
  }
  R = nil;


}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
  if(R == nil || k == R->key){
    return R;
  }
  else if (k.compare(R->key) < 0){
    return search(R->left, k);
  }
  else {
    return search(R->right, k);
  }
}


// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R){
  while(R->left != nil){
    R = R->left;
  }
  return R;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){
  while(R->right != nil){
    R = R->right;
  }
  return R;
}


// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N){

 if(N->right != nil){ //case 1: if there is a right child
   return findMin(N->right); //find the min of the nodes that are larger than n
 }
 
 //else there is no right child
 //this means that the successor is the last node that is a parent of N and
 //N is not a right child of that ansestor node
 //(if N is a right child then it is larger)
 Node* y = N->parent;        //node y is the parent of R
 //while y has right children move up the tree (to the parent of y)
 while( y != nil && N == y->right){
   N = y;
   y = y->parent;
 }
 return y;
 
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N){ //this one is messed

  //case 1 N has a left child
  //in this case take the max of the left subtree of N
  if(N->left != nil){
    return findMax(N->left);
  }

  //case 2 N has no left child
  //in this case the predicessor will be the first ansestor node of N where
  //N not the left child of of that ansestor
  Node* y = N->parent;
  
  while( y != nil && N== y->left){
    N = y;
    y = y->parent;
  }
  return y;
}



// RBT Helper Functions -----------------------------------------
   
// LeftRotate()
//pre: N->left != nil
void Dictionary::LeftRotate(Node* N){

  if(N->right == nil){
    throw std::logic_error("Dictionary: LeftRotate: N->right is nil");
    //cout << "left was nil throw sum\n"; return;
  }

   Node* y = N->right;
   
   N->right = y->left;
   y->left->parent = N;
   
   y->parent = N->parent;
   if(N->parent == nil){ root = y;}
   else if(N == N->parent->left){
     N->parent->left = y;
   }
   else{
     N->parent->right = y;
   }

   y->left = N;
   N->parent= y;

}

// RightRotate()
void Dictionary::RightRotate(Node* N){
  if(N->left == nil){
    throw std::logic_error("Dictionary: LeftRotate: N->left is nil");
  }

   Node* y = N->left;
   
   N->left = y->right;
   y->right->parent = N;
   
   y->parent = N->parent;
   if(N->parent == nil){ root = y;}
   else if(N->parent->right == N){
     N->parent->right = y;
   }
   else{
     N->parent->left = y;
   }

   y->right = N;
   N->parent= y;
}



// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* N){

  Node* y = nil;

  while(N->parent->color == RED){
    //case 1-3 the parent of N is a left child
    
    if(N->parent == N->parent->parent->left){
      y = N->parent->parent->right; //y is the right child of N grandparent  
      
      //case 1 (the right child of grandparent is RED)
      if(y->color == RED){
        //chage colors to make tree work
        N->parent->color = BLACK;
        y->color = BLACK;
        N->parent->parent->color = RED;
        
        //now make N the grandparent of z and check again weither there 
        // is a double red that would make the RBT invalid
        N = N->parent->parent;      
      }
      
      //case 2-3 (y is black)
      else{
        
        if(N == N->parent->right){
          N = N->parent;             //case 2
          LeftRotate(N);             //case 2 (make N a left child)
        }
        N->parent->color = BLACK;         //case 3 (N is left child)
        N->parent->parent->color = RED;   //case 3
        RightRotate(N->parent->parent);   //case 3
      
      }
  
    }//cases 1-3

    //cases 4-6 (parent of N is a right child)
    else{
      y = N->parent->parent->left;
    
      //case 4 (y is red)
      if(y->color == RED){
      
        //change colors to fit RBT rules
        N->parent->color = BLACK;
        N->parent->parent->color = RED;
        y->color = BLACK;
        //now set N to N's grandparent to check RBT props again
        N = N->parent->parent;
      }
    
      else{
        if(N == N->parent->left){ //case 5(N is left child)
          N = N->parent;
          RightRotate(N);        //make N a right child
        }
        //case 6 N is a right child

        N->parent->color = BLACK;  //change colors
        N->parent->parent->color = RED;
        LeftRotate(N->parent->parent);  //move parent of N up 
    
      }
    
    
    }//cases 4-6

  }//main while loop while parent of node is not RED

  root->color = BLACK;

}

// RB_Transplant()
//replaces the subtree rooted at u with the subtree rooted at v
//
//doubly links v to the parent of u
//
//if v is the root then v is made the root
void Dictionary::RB_Transplant(Node* u, Node* v){

  //if v is the root
  if(u->parent == nil){   
    root = v;  //the root now points to v
  }
  

  //if u is a left child
  else if(u == u->parent->left){
    u->parent->left = v; //make the left child of parent of u point to v
  } 

  //else u is a right child
  else{
    u->parent->right = v; //make v right child of parent of u
    
  }
  
    v->parent = u->parent;
    
}


//problem in delete
// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N){
  

  Node * x = N;
  Node * w = nil;
  
  
  //when do I check for a nil at x and can an x be passed thorough
  // maybe it can work for this

  while (x != root && x->color == BLACK) {

      //if x is a left child
      if (x == x->parent->left){
         w = x->parent->right;   //w becomes sibling

         
         //if sibling color is red
         //color sib black
         //color parent red
         //left rotate on parent of x
         //again make w the sibling of x
         if (w->color == RED) {

            w->color = BLACK;                       // case 1
            x->parent->color = RED;                   // case 1
            LeftRotate(x->parent);                // case 1
            w = x->parent->right;                     // case 1
         }                 
         
         //this one seems fishy what if you are on nil?
         //if both children of w are black    
         if( w->left->color == BLACK && w->right->color == BLACK) {
            w->color = RED;                          // case 2
            x = x->parent;                           // case 2
         }
         else { 
            //if just the right is black
            if (w->right->color == BLACK){
               w->left->color = BLACK;                // case 3
               w->color = RED ;                      // case 3
               RightRotate(w);                       // case 3
               w = x->parent->right;                  // case 3
           }
            w->color = x->parent->color;               // case 4
            x->parent->color = BLACK;                 // case 4
            w->right->color = BLACK;                  // case 4
            LeftRotate(x->parent);                // case 4
            x = root;                             // case 4
        }
            
     }//if x is a left child
            
      else{ //x is a rigth child
         w = x->parent->left;
         
         if (w->color == RED){ //if the sibling is red
            w->color = BLACK;                        // case 5
            x->parent->color = RED;                   // case 5
            RightRotate(x->parent);               // case 5
            w = x->parent->left;                      // case 5
         }
         //if children of the siblings are both black
         if (w->right->color == BLACK && w->left->color == BLACK){
            w->color = RED;                          // case 6
            x = x->parent;                           // case 6
         }
         else {
            //if only the left child of the sibling is black
            if (w->left->color == BLACK) {
               w->right->color = BLACK;               // case 7
               w->color = RED;                       // case 7
               LeftRotate(w);                    // case 7
               w = x->parent->left;                   // case 7
           }
            w->color = x->parent->color;               // case 8
            x->parent->color = BLACK;                 // case 8
            w->left->color = BLACK;                   // case 8
            RightRotate(x->parent);               // case 8
            x = root;                             // case 8
        }
     }       
  }
   x->color = BLACK;

}

//could make remove faster look at precondition and search
// RB_Delete()
//look at one of these and make the parent of x the parent even if it is nil

void Dictionary::RB_Delete(Node* N){
 
  Node * z = N;
  Node * x = nil;
  Node * y = z;
  
  //y starts as N or z but node that delete was called on
  int y_original_color = y->color;

  //if z points to same place as current then dereference current
  if(z == current){
    current = nil;
  }

  //if left child is nil
  if(z->left == nil){
    x = z->right;   //x becomes right child of z (stil could be nil here)
    x->parent = z;
    RB_Transplant(z, z->right); //swap z with the right child of z (can you swapp with nil)
  }  

  //if right child is nil
  else if(z->right == nil){
    x = z->left;   //x becomes the left child of z
    x->parent = z;
    RB_Transplant(z, z->left);  //swap z with its left child (effecively removing z)
  }
  
  //x can be nil here if one of conditionals is met
  
  //if both are non nil then x is still undefined
  
  //z has two children
  else{

     y = findMin(z->right);      //set y to the min of the right subree (successor)
     y_original_color = y->color;  //set the y original color to successor color
     x = y->right;                //x is the right child of the successor (could be nil I guess)
     x->parent = y;
   
     //if the parent of the successor is the node to delete
     if(y->parent == z){  
       x->parent = y;  //set the parent of x to be the successor
     }
     else { //if the parent of the successor is not the node to del
       RB_Transplant(y, y->right);   //put right child of successor where successor is
       y->right = z->right;         //connect y right child to z right child
       y->right->parent = y;        //connect that back to y
     }
     RB_Transplant(z,y);           //put y where z was
     y->left = z->left;            //connect lef child of y to z left
     y->left->parent = y;          //connect left child up to y
     y->color = z->color;          //set the color to whatever the color of deleted node was
   }//else z has two children (if this then x can not be nil)
   
   delete z; z = nullptr;
   num_pairs--;
   
   //if x is nil here what is the protocol?
   //it seems like this is just dealt with in th next function
   
   if(y_original_color == BLACK){
     RB_DeleteFixUp(x);
   }
   
}








// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const{
  return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const{
  Node* temp = search(root, k);
  if(temp == nil){ return false;}
  return true;
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{
  Node * temp = search(root, k);
  if(temp == nil){
    throw std::logic_error("Dictionary: getValue(): key \"blah\" does not exist");
  }
  return temp->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const{
  if(current == nil){ return false;}
  return true;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const{
  if(!hasCurrent()){
    throw std::logic_error("Dictionary: currentKey(): current undefined");
  }
  return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const{
  if(!hasCurrent()){
    throw std::logic_error("Dictionary: currentVal(): current undefined");
  }
  return current->val;
}





// manipulation functions --------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
  postOrderDelete(root);
  current = nil;
  root = nil;
  num_pairs = 0;
}


///$$$$$$$$$$$$$$$$ alter this
// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v){

  Node* newNode = new Node(k,v); //new node with data as param
   
  Node* y = nil;
  Node* x = root;  //iterates through tree to find correct location to insert

  while(x != nil){
     y = x;
     
     //if k equals x->key then the el already exists and you 
     //just gotta change the value of the node
     if(k.compare(x->key) == 0){
       x->val = v;
       delete newNode; newNode = nullptr;
       return;
     }

     if(k.compare(x->key) < 0){  //if k comes before x->key
       x = x->left;
     }
     else {
       x = x->right;
     }
     //y is at node above where newNode should be placed
     
  } //while
     
  newNode->parent = y;
     
  if(y == nil){     //this means that the tree was initialy empty
    root = newNode;
    root->left = nil;
    root->right = nil;
    root->parent = nil;
  }
     
  else if(k.compare(y->key) < 0) {
    y->left = newNode;
  }
  //maybe put something in here if it is equal
  else{
    y->right = newNode;
  }
     
  newNode->left = nil;
  newNode->right = nil;
  
  num_pairs++;
  
  newNode->color = RED;  
  RB_InsertFixUp(newNode);
}




// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k){
  if(!contains(k)){
    throw std::logic_error("Dictionary: remove(): key \"blah\" does not exist");
  }
  
  Node * temp = search(root,k);
  RB_Delete(temp);
  
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin(){
  if(num_pairs <= 0){ return;}
  Node* temp = root;
  while(temp->left != nil){
    temp = temp->left;
  }
  current = temp;
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end(){
  if(num_pairs <= 0) {return;}
  
  Node* temp = root;
  while(temp->right != nil){
    temp = temp->right;
  }
  current = temp;
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next(){
  if(!hasCurrent()){
    throw std::logic_error("Dictionary: next(): current undefined");
  }
  Node* temp = findNext(current);
  current = temp;
  
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev(){
  if(!hasCurrent()){
    throw std::logic_error("Dictionary: prev(): current undefined");
  }
  Node* temp = findPrev(current);
  current = temp;
  
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const{
  string s;
  inOrderString(s, root);
  return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const{
  string s;
  preOrderString(s, root);
  return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
//make a preOrder with keys and value pairs 
//or do inOrder string comp and a preOrder tree walk string
bool Dictionary::equals(const Dictionary& D) const{
  if(num_pairs != D.size()) return false;

  //string thisStr;
  //inOrderString(thisStr, root);
  
  string DpreStr = D.pre_string();
  
  string Dstr = D.to_string();
  
  if(Dstr == to_string() && DpreStr == pre_string()) return true;
  return false;
  

}

// Overloaded Operators ----------------------------------------------------
   
// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
  return stream << D.Dictionary::to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ){
  return A.Dictionary::equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ){
  if(this != &D){
  
    Dictionary temp = D;
  
    clear();
    preOrderCopy(temp.root, temp.nil);
    std::swap(current, temp.current);
  }
  
  return *this;

}















