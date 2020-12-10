// CMSC 341 - Fall 2019 - Project 5
// heap.h
// Templated, vector-based heap implementation

// To work with Heap, the template class T must provide the following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) overloaded insertion operator
// To work with Heap *and* HashTable, it also needs:
//  (d) key function (string key())

#ifndef _HEAP_H
#define _HEAP_H

#include <iostream>
#include <vector>
#include <exception>
#include <utility>   // swap

using std::vector;
using std::endl;
using std::cout;
using std::swap;
using std::range_error;

// To work with Heap and HashTable, class T must provide the
// following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) key function (string key())
//  (d) overloaded insertion operator

class Grader;

template <class T>
class Heap {

  friend Grader;
  
 public:
  // Constructor
  Heap();

  // Inline functions: size, empty, used 
  unsigned size() const { return _heap.size() - 1 ; }
  bool empty() const { return _heap.size() <= 1 ; }
  bool used() const { return _used ; }

  // Main heap operations: insert, read, remove
  void insert(const T& object);
  T readTop() const;
  void removeTop();

  // Dump the entire heap
  void dump() const;

  // Root node always has index 1
  static const unsigned ROOT = 1;
  
 private:
  vector<T> _heap;   // Vector-based heap
  bool _used;        // Has the heap ever been used?  Needed for
		     // linear probing.

  // *********************************************
  // Private helper function declarations go here!
  // *********************************************

  void downHeap(int size);
  void upHeap(int size);
};

// ***************************************
// Templated function definitions go here!
// ***************************************


template <class T>
Heap<T>::Heap(){

  _used = false;

  T dummyVariable;
  _heap.push_back(dummyVariable);
}



template <class T>
void Heap<T>::insert(const T& object){

  _heap.push_back(object);

  _used = true;

  upHeap(size());  

}

template <class T>
T Heap<T>::readTop() const{

  //_heap is empty
  if(empty()){

    throw std::domain_error("EMPTY in readTop");

  }
  
  return _heap[ROOT];
}

template <class T>
void Heap<T>::removeTop(){

  //_heap is empty
  if(empty()){

    throw std::domain_error("EMPTY in removeTop");
    
  }
  
  swap(_heap[ROOT],_heap[size()]);

  _heap.pop_back();

  //maintains max heap property
  downHeap(ROOT);

}


template <class T>
void Heap<T>::dump() const{

  for(unsigned int i = 1; i < _heap.size(); i++){
    
    cout << _heap[i] << endl;
    
  }

}

template <class T>
void Heap<T>::downHeap(int parent){

  unsigned int right = (parent *2) + 1;
  unsigned int left = parent*2;

  unsigned int bigger = parent;

  bool check = false;

  //right isn't out of bounds and the _heap[right] is greater than _heap[bigger]
  if(right <= size() && _heap[right].priority() > _heap[bigger].priority()){

    bigger = right;
    check = true;
  }

  //left isn't out of bounds and the _heap[left] is greater than _heap[bigger]
  if(left <= size() && _heap[left].priority() > _heap[bigger].priority()){

    bigger = left;
    check = true;
  }

  //found bigger value
  if(check == true){
    swap(_heap[parent], _heap[bigger]);

    //maintain max heap property
    downHeap(bigger);
  }
  
  return;
}
 


template <class T>
void Heap<T>::upHeap(int size){

  int parent = (size)/2;

  //parent is a root
  if(parent > 0){
    
    if(_heap[parent].priority() < _heap[size].priority()){
      
      swap(_heap[size], _heap[parent]);
      
      upHeap(parent);
      
    }
  }
    return;
}


#endif
