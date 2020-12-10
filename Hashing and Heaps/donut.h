// CMSC 341 - Fall 2019 - Project 5
// donut.h
// Simple class for use with Heap and HashTable classes

// To work with Heap and HashTable, a class must provide the
// following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) key function (string key())
//  (d) overloaded insertion operator

#ifndef _DONUT_H
#define _DONUT_H

#include <iostream>
#include <string>

using std::string;
using std::ostream;

// Donut is a silly class.  An object consists of a donut type (the
// key), an order priority, and a string to hold customer information.

class Donut {
 public:

  // Constructor.  Default is a "plain" donut, priority 0, and empty
  // customer string.
  Donut(string key = "plain", unsigned pri = 0, string customer = "") {
    _key = key;
    _pri = pri;
    _customer = customer;
  }

  // Required.  Returns priority of a donut order.
  unsigned priority() const {
    return _pri;
  }

  // Required.  Returns key (donut type) of a donut order.
  string key() const {
    return _key;
  }

  // Overloaded insertion operator
  friend ostream& operator<<(ostream& sout, const Donut &d );
  
 private:
  string _key;         // donut type
  unsigned _pri;       // order priority
  string _customer;    // customer information
};

// Overloaded insertion operator.  Prints donut type (key), priority,
// and customer information.
ostream& operator<<(ostream& sout, const Donut &d ) {
  sout << d._key << " (priority " << d._pri << ", "
       << d._customer << ")";
  return sout;
}

#endif
