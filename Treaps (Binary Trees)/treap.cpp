// CMSC 341 - Fall 2019 - Project 3
// File: treap.cpp

using namespace std ;

#include "treap.h"

Treap::Treap() {
  _nptr = nullptr ;
}

Treap::Treap(const Treap& other) {
  //
  // Implement copy constructor
  //
  
  _nptr = treeCopy(other);
  
}

Treap::~Treap() {
  //
  // Implement destructor
  //


  //checks if there is data to delete
  if(_nptr != nullptr){
    
    delete _nptr;
    _nptr = nullptr;
    
  }
}

const Treap& Treap::operator=(const Treap& rhs) {
  //
  // Implement assignment operator
  //

  //prevent self assignment
  if(this != &rhs){

    if(_nptr != nullptr){

      delete _nptr; 
      _nptr = nullptr;
    }

    _nptr = treeCopy(rhs);

  }

  return *this;
  
}

// Return -1 if the treap is empty; otherwise, return value in _height.
int Treap::height() const {
  return _nptr ? _nptr->_height : -1 ;
}

// Return the priority of the root node of a Treap.
// Note: numeric_limits<priority_t>::min() returns the minimum value
// of the priority type.  We will only use int priorities, so this is
// the minimum integer value.
priority_t Treap::priority() const {
  return _nptr ? _nptr->_pri : numeric_limits<priority_t>::min() ;
}

const data_t* Treap::find(const data_t& x) {
  //
  // Implement find function
  //

  //value not found
  if( empty()){

    return nullptr;
  }
  
  //if the root node is equal to x
  if(_nptr ->_data == x){
    return &(_nptr -> _data);
  }

  //value is less than current data
  if(x < _nptr -> _data){
    _nptr -> _left.find(x);
  }

  //value is greater than current data
  if(x > _nptr -> _data){
    _nptr -> _right.find(x);
  }

  return nullptr;
  
  
}

// Inorder traversal.  Recommend you NOT change this!!!
void Treap::inorder() {

  if ( empty() ) return ;

  cout << "(" ;
  _nptr->_left.inorder() ;

  cout << _nptr->_data << ":" << priority() << ":" << height() ;

  _nptr->_right.inorder() ;
  cout << ")" ;

  return  ;
}

// Used for debugging and grading.  Interprets the characters in
// position[] as directions in the tree.  E.g., "RLR" means, "starting
// from root, go right, then left, then right."  If position[] is an
// empty string, then it just locats the value a the root.
// See project description for details.
bool Treap::locate (const char position[], data_t& x, priority_t& p, int& h, int offset) {

  if (_nptr == nullptr) return false ;

  if (position[offset] == '\0') {
    x = _nptr->_data ;
    p = _nptr->_pri ;
    h = _nptr->_height ;
    return true ;
  }

  if (position[offset] == 'L') {
    return _nptr->_left.locate(position, x, p, h, offset+1) ;
  }

  if (position[offset] == 'R') {
    return _nptr->_right.locate(position, x, p, h, offset+1) ;
  }

  cerr << "Bad position character!\n" ;
  exit(17) ;

  return false ; 
}


// Basic BST insertion.  Does not allow duplicate values.
//
// Complete this function to do Treap insertion.
//
void Treap::insert(const data_t& x, const priority_t& p) {

  //data is already inserted
  if(find(x) != nullptr){

    return;
  }

  if ( empty() ) {
    _nptr = new TreapNode(x, p) ;
  }

  if (_nptr->_data < x) { 
    _nptr->_right.insert(x, p) ;
    
  } else if (x < _nptr->_data ) {
    _nptr->_left.insert(x, p) ;

  }

  
  //if left priority is greater than right priority
  if(_nptr -> _left.priority() > _nptr -> _right.priority()){

    //left priority is greater than curr node priority
    if(_nptr -> _left.priority() > priority()){
      
      rightRotate();
    }
  }

  //if right priority is greater than left priority
  else{

    //right node priority is greater than curr node priority
    if(_nptr ->_right.priority() > priority()){
      
      leftRotate();
    }
  }
 

  heightFix(_nptr);
}

bool Treap::remove(const data_t& x) {
  //
  // Implement treap element removal
  //

  //doesn't find value to remove
  if(empty()){

    return false;
  }

  //if this is the node to delete
  if(_nptr -> _data == x){

    //node is a leaf
    if(_nptr -> _height == 0){
    
      delete _nptr;
      _nptr = nullptr;

      return true;
    }

    if(_nptr -> _right.priority() > _nptr -> _left.priority()){

      leftRotate();

    }

    else{

      rightRotate();
      
    } 

  }    

  //data to remove is greater than current data
  if (_nptr->_data < x) {
    
    _nptr->_right.remove(x) ;

    //data to remove is less than current data
  } else if (x < _nptr->_data ) {
    
    _nptr->_left.remove(x) ;
    
  }

  heightFix(_nptr);
  

  return true;
  
}

// Treap::dump() just calls TreapNode::dump()
void Treap::dump() {
  if ( !empty() ) _nptr->dump() ;
}

ostream& operator<< (ostream& os, const Treap& T) {
  os << T._nptr ; 
  return os ;
}


TreapNode::TreapNode() : _height(0) {
  // Empty constructor body
}

TreapNode::TreapNode(const data_t& x, const priority_t& p) 
  : _data(x), _pri(p), _height(0) { 
  // Empty constructor body
}

TreapNode::~TreapNode() {
  // Empty destructor
  // Retained for debugging
}

// Dump the contents of a node
void TreapNode::dump() {
  cout << "===== TreapNode::dump()\n" ;
  cout << "      this = " << this << endl ; 
  cout << "      left = " << _left << endl ; 
  cout << "      right= " << _right << endl ; 
  cout << "      data = " << _data << endl ;
  cout << "      height = " << _height << endl ;
  _left.dump() ;
  _right.dump() ;
}

void Treap::leftRotate(){

  TreapNode *currNode = _nptr;

  //_nptr right child
  TreapNode *temp = _nptr -> _right._nptr;

  //_nptr right left grandchild
  TreapNode *leftTemp = temp -> _left._nptr;
  
  temp -> _left._nptr = currNode;
  _nptr = temp;
  
  currNode -> _right._nptr = leftTemp;

  //adjusts children's height
  heightFix(temp);
  heightFix(currNode);
}

void Treap::rightRotate(){
  
  TreapNode *currNode = _nptr;

  //_nptr left child
  TreapNode *temp = _nptr -> _left._nptr;

  //_nptr left right grandchild
  TreapNode *rightTemp = temp -> _right._nptr;
  
  temp -> _right._nptr = currNode;
  _nptr = temp;
  
  currNode -> _left._nptr = rightTemp;

  //adjusts children's height
  heightFix(temp);
  heightFix(currNode);
  
}

TreapNode* Treap::treeCopy(const Treap &other){
  
  //if node is null
  if(other.empty()){

    return nullptr;
  }
  else{

    TreapNode *nptr = new TreapNode(other._nptr -> _data, other._nptr -> _pri);

    //copies height
    nptr -> _height = other._nptr -> _height; 
    
    //if left child isn't null
    if(other._nptr -> _left.empty() == false){
      
      nptr -> _left._nptr = treeCopy(other._nptr -> _left); 
   
    }

    //if right child isn't null
    if(other._nptr -> _right.empty() == false){
      
      nptr -> _right._nptr = treeCopy(other._nptr -> _right);
	
    }

    _nptr = nptr;
    
    return nptr;

       
  }

  return nullptr;
}


void Treap::heightFix(TreapNode* fixTree){

  int leftHeight = fixTree ->_left.height();
  int rightHeight = fixTree ->_right.height();
  fixTree -> _height = 1 + ( leftHeight > rightHeight ? leftHeight : rightHeight );
 
}
