// CMSC 341 - Fall 2019 - Project 4

#ifndef SKEWHEAP_H
#define SKEWHEAP_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <iomanip>

using namespace std;

class Grader;

// ENUM of valid data types
enum type_t {ISSTRING, ISINT};

struct Node{
  enum type_t tagged_union;   // Type of data in node
  union {
    string data_string;       // Store string or int; but
    int data_int;             // not both
  };
  Node *right;                // Right child
  Node *left;                 // Left child

  // Constructor for int data
  Node(int data){  
    data_int = data;
    right = nullptr;
    left = nullptr;
    tagged_union = ISINT;
  }

  // Constructor for string data
  Node(string data) : data_string(data) {
    right = nullptr;
    left = nullptr;
    tagged_union = ISSTRING;
  }

  // Need a destructor because the union includes string
  ~Node() {
    if ( tagged_union == ISSTRING ) {
      data_string.~string();
    }
  }
};

// Defines pri_fn as a function pointer
typedef int (*pri_fn)(Node *);

class SkewHeap {
public:

  friend Grader;

  // Constructor.  Must specify priority function.
  SkewHeap(pri_fn pri);

  // Destructor, copy constructor, assignment operator
  ~SkewHeap(); 
  SkewHeap(const SkewHeap& rhs);
  const SkewHeap& operator=(const SkewHeap& rhs);

  // Priority function get and set
  pri_fn getPriFn() const;
  void setPriFn (pri_fn pri);

  // Return true if the skew heap is empty
  bool empty() const;

  // Overloaded insertion operators.  One for string data, one for
  // integer data.
  void insert(string data);
  void insert(int data);

  // Access highest priority element in the skew heap.
  Node* front() const;

  // Remove the highest priority element from the skew heap.
  void removeTop();

  // Merge two heaps.  Merged heap in *this; sh is empty afterwards.
  void skewHeapMerge(SkewHeap& sh);

  // Print inorder traversal.
  void inorder() const;
  
  // Dump the contents of the heap in decreasing priority order.
  void dump() const;

private:
  Node *m_heap;          // Root pointer
  pri_fn priority;       // Current priority function

  //************************************
  //
  // PRIVATE HELPER FUNCTIONS GO HERE!
  //
  //************************************

  // SkewHeap* skewCopy(const SkewHeap &other);

  Node* skewCopy(const Node *other);
  
  Node* skewMerge(Node *p1, Node *p2);    

  void inOrderHelper(Node* temp) const;

  void recursiveDestroy(Node* temp);
};

#endif
