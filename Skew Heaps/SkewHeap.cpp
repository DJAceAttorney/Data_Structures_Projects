using namespace std;

#include "SkewHeap.h"

SkewHeap::SkewHeap(pri_fn pri){
  
  m_heap = nullptr;
  
  priority = pri;

}

SkewHeap::~SkewHeap(){

  //if(m_heap != nullptr){

    //delete m_heap; //post order traversal to delete entire heap
    // m_heap = nullptr;
    
    //  }

  recursiveDestroy(m_heap);
  
  
}

SkewHeap::SkewHeap(const SkewHeap& rhs){

  //sets priority
  priority = rhs.priority;
  
  if(rhs.empty()){

    return;
  }
  
  m_heap = skewCopy(rhs.m_heap);
}

const SkewHeap& SkewHeap::operator=(const SkewHeap& rhs){

  //sets priority
  priority = rhs.priority;
    
  if(rhs.empty()){

    return nullptr;
  }

  
  //prevents self assignment
  if(this != &rhs){
    
    if(m_heap != nullptr){

      //delete this;
      recursiveDestroy(m_heap);
      //m_heap = nullptr;
      // delete *this;
      
    }
    //m_heap = skewCopy(rhs.m_heap);
    
  }

  m_heap = skewCopy(rhs.m_heap);
  
  return *this;
  
}

//gets priority
pri_fn SkewHeap::getPriFn() const{
  
  return priority;
  
}

void SkewHeap::setPriFn(pri_fn pri){

  priority = pri;

  // SkewHeap *temp = new SkewHeap(pri);

  SkewHeap *temp = new SkewHeap(priority);
  //SkewHeap temp(priority);
  
  while(!empty()){
  //while(m_heap != nullptr){

    if(m_heap-> tagged_union == ISINT){

      // temp.insert(m_heap -> data_int);
      temp -> insert(m_heap -> data_int);

     }

    else if(m_heap -> tagged_union == ISSTRING){

      // temp.insert(m_heap -> data_string);
      temp -> insert(m_heap -> data_string);
    }
    
    removeTop();
    
  }


  //*this = temp;

  *this = *temp;
  
  delete temp;
  temp = nullptr;
}

bool SkewHeap::empty() const{

  return m_heap == nullptr;
  
}

void SkewHeap::insert(string data){
  
  Node *temp = new Node(data);

  m_heap = skewMerge(m_heap ,temp);

  // delete temp;
  //temp = nullptr;
}

void SkewHeap::insert(int data){

  Node *temp = new Node(data);

  m_heap = skewMerge(m_heap ,temp);

  //delete temp;
  //temp = nullptr;
  
}

//gets highest priority element of skew heap
Node* SkewHeap::front() const{

  if(empty()){

    return nullptr;
  }

  return m_heap;  
  
}

//removes highest priority element from skew heap
void SkewHeap::removeTop(){
 
  Node *tempLeft = m_heap -> left;
  Node *tempRight = m_heap -> right;

  //Node *temp = m_heap;

  delete m_heap;

  //m_heap = nullptr;
  
  m_heap = skewMerge(tempLeft,tempRight);
}

void SkewHeap::skewHeapMerge(SkewHeap& sh){

  //throw exception when priorities don't match
  if(priority != sh.priority){

    throw domain_error("Attempt to merge two skews with different priorities");
    
  }
  
  m_heap = skewMerge(m_heap,sh.m_heap);

  sh.m_heap = nullptr;
  
}

void SkewHeap::inorder() const{

  if ( empty() ) return ;

  inOrderHelper(m_heap);
 
  return ;
  
}

void SkewHeap::dump() const{

  SkewHeap copyHeap (*this);
 
  while(copyHeap.empty() == false){ 
    cout << "Data is:      ";

    if(copyHeap.front() -> tagged_union == ISINT){
      
      cout << copyHeap.front() -> data_int;
     }
    
    // else if(copyHeap.front() -> tagged_union == ISSTRING){
    else{
    
      cout << copyHeap.front() -> data_string;
      
    }
    
    cout << "              ";
    cout << "Priority is:     " << priority(copyHeap.front()) << endl;
    
    copyHeap.removeTop();
    
  }
  
}


//SkewHeap* SkewHeap::skewCopy(const SkewHeap &other){
Node* SkewHeap::skewCopy(const Node *other){

  Node *skew;

  if(other == nullptr){

    return nullptr;

  }
  
  //other is a string
  if(other -> tagged_union == ISSTRING){
    
    skew = new Node(other -> data_string);      
  }

  //other is an int
  else if(other -> tagged_union == ISINT){
      
    skew = new Node(other -> data_int);
  }
  
  //if(other -> left != nullptr){

  skew -> left = skewCopy(other -> left);
    //}

  //else{

  //skew -> left = nullptr;
  //}
  
  //if(other -> right != nullptr){
    
  skew -> right = skewCopy(other -> right);
  //}

  //else{

  //skew -> right = nullptr;
  // }

  // m_heap = skew;
  
  return skew;
  
}

Node* SkewHeap::skewMerge(Node *p1, Node *p2){
  
  if(p1 == nullptr){
    
    return p2;

  }


  else if(p2 == nullptr){  
    
    return p1;
  }

  //priority for p1 less than priority for p2
  if(priority(p1) < priority(p2)){

    swap(p1,p2);
    
  }

  swap(p1 -> left, p1 -> right);

  p1 -> left = skewMerge(p1 -> left, p2);

  return p1;

}

void SkewHeap::inOrderHelper(Node* temp) const{
  
  if(temp == nullptr){

    return;
  }

  cout <<"(";
  
  inOrderHelper(temp -> left);
  
  //node is a string
  if(temp -> tagged_union == ISSTRING){
    
    cout << temp -> data_string;
  }

  //node is an int
  else if(temp -> tagged_union == ISINT){

    cout << temp -> data_int;
  }

  inOrderHelper(temp -> right);

  cout << ")";
}

void SkewHeap::recursiveDestroy(Node* temp){

  if(temp != nullptr){

    recursiveDestroy(temp -> left);
          
    recursiveDestroy(temp -> right);
    
    delete temp;
    temp = nullptr;
  }
  

}
