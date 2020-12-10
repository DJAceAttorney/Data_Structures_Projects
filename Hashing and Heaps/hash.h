// CMSC 341 - Fall 2019 - Project 5
// hash.h

// Templated, hash table implementation.  Each buckets is a heap.  A
// bucket contains objects with the same key values stored as a
// max-heap based on priority.  Collisions are resolved by linear
// probing.

// To work with Heap and HashTable, the template class T must provide
// the following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) key function (string key())
//  (d) overloaded insertion operator

#ifndef _HASH_H
#define _HASH_H

#include <string>
#include "heap.h"

using std::string;

// Hash function typedef.  The hash function must return an 'unsigned
// int' value.  Reduction mod N is the responsiblity of the caller,
// not the hash function.
typedef unsigned (*hash_fn)(string);

class Grader;

template <class T>
class HashTable {

  friend Grader;
  
 public:
  // Constructor.  Requires table size and hash function.
  HashTable(unsigned size, hash_fn hash);

  // Destructor, copy, and assignment
  ~HashTable();
  HashTable(const HashTable<T>& ht);
  const HashTable<T>& operator=(const HashTable<T>& ht);

  // In-line functions
  
  // Table size; set by constructor
  unsigned tableSize() const { return _N; }
  // Number of entries in the table
  unsigned numEntries() const { return _n; }
  // Load factor
  float lambda() const { return ((float) _n) / _N; }

  // Main hash table functions
  
  // insert returns 'true' if successful; 'false' otherwise
  bool insert(const T& object);
  // getNext retrieves **and removes** the highest priority order of
  // type indicated by key.  It returns 'true' if successful; 'false'
  // otherwise.
  bool getNext(string key, T& obj);

  // Dump the entire hash table
  void dump() const;
  
 private:
  unsigned _N;       // hash table size
  unsigned _n;       // current number of entries
  hash_fn _hash;     // hash function
  Heap<T> *_table;   // array of heaps

  // ***********************************************
  // Private helper function declarations go here! *
  // ***********************************************
  
};

// *****************************************
// Templated function definitions go here! *
// *****************************************


template <class T>
HashTable<T>::HashTable(unsigned size, hash_fn hash){

  _N = size;
  _hash = hash;
  _n = 0;
  
  _table = new Heap<T>[_N];
}


template <class T>
HashTable<T>::~HashTable(){

  delete[] _table;
  _table = nullptr;

}


template <class T>
HashTable<T>::HashTable(const HashTable<T>& ht){
  
  _N = ht._N;
  _n = ht._n;
  _hash = ht._hash;
  
  _table = new Heap<T>[_N];
  
  //copies all values from ht
  for(unsigned int i =0; i < _N; i++){
    
    _table[i] = ht._table[i];
    
  }
}


template <class T>
const HashTable<T>& HashTable<T>::operator=(const HashTable<T>& ht){
 
  //self assignment
  if(this == &ht){

    return *this;
  }
  
  delete[] _table;
  _table = nullptr;
    
    
  
  _N = ht._N;
  _n = ht._n;
  _hash = ht._hash;
  
  _table = new Heap<T>[_N];
  
  //copies all values from ht
  for(int i =0; i < _N; i++){
    
    _table[i] = ht._table[i];
    
  }
  
  return *this;
  
}


template <class T>
bool HashTable<T>::insert(const T& object){

  unsigned int functionHash = _hash(object.key()) % _N;
  
  int count = _N;
  
  int temp = 0;

  int counter = 0;

  bool check = false;
  
  //while we haven't looped all the way around
  while(temp < count){
      
    //table index is empty and it hasn't been used
    if(_table[functionHash].empty() == true && _table[functionHash].used() == false){

      //we found an empty and used index
      if(check == true){
	
	_table[counter].insert(object);
	_n++;
      
	return true;

      }

      _table[functionHash].insert(object);
      _n++;
      
      return true;
      
    }
    
    //same heap key type and not empty
    if(_table[functionHash].empty() == false &&_table[functionHash].readTop().key() == object.key()){
      
      _table[functionHash].insert(object);
      _n++;
      
      return true;
      
    }

    //first instance of index is empty and used
    if(_table[functionHash].empty() == true && _table[functionHash].used() == true && check == false){

      counter = functionHash;
      check = true;
    }

    
    temp++;
    functionHash++;
    
    //move to beginning of table
    if(functionHash == _N){
      
      functionHash = 0;
    }    
  }

  
  
  cout << "Table is full" << endl;
  return false;
}

template <class T>
bool HashTable<T>::getNext(string key, T& obj){

  unsigned int functionHash = _hash(key) % _N;
  
  int count = _N;
  
  int temp = 0; 
  
  //while we haven't looped all the way around
  while(temp < count){

    //if the index is never used
    if(_table[functionHash].used() == false){

      cout << "Key not found" << endl;
      return false;
    }
    
    //index is not empty and key has been found
    else if(_table[functionHash].empty() == false && _table[functionHash].readTop().key() == key){
      
      obj = _table[functionHash].readTop();
    
      _table[functionHash].removeTop();
      
      return true;
    }
    
  
    temp++;
    functionHash++;
    
    //move to beginning of table
    if(functionHash == _N){
      
      functionHash = 0;
    }
  }

  cout << "Key not found" << endl;
  return false;
  
}

template <class T>
void HashTable<T>::dump() const{

  for(unsigned int i =0; i < _N; i++){
    
    cout << "[" << i << "]" << ":" << endl;
    _table[i].dump();
    
  }
}

#endif
