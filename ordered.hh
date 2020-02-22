// 
// dict.hh
//
// Type definitions and prototypes for an integer linked list data
// structure. 
//
// CSCI 221 Spring 2020
//
// Author: Julian Prince
//
// The code below gives the header information for a ordered dict data
// structure. It defines two types `ordered::entry` and `ordered::dict`,
// the first forming the low-level struct type that's stitched together
// to store a string 'key' and int 'value', and the second providing a "housing"
// for the data structure, accepting a collection of operations on 
// that data structure.
//
// Those two types, along with the operations on `ordered::dict*`, are 
// all defined under a namespace `orderd`. The operations that this
// ordered dict supports are 
//
// * build, - construct a new dict (on the heap)
// * set - sets entry with key 'k' to value 'v' creates a new entry with key 'k' if none exists
// * get - returns value of entry with key 'k', or default value if that entry doesn't exist
// These operations are implemented in `dict.cc`.
//

#ifndef _dict_HH
#define _dict_HH

#include <string>

namespace ordered {

  struct entry {
    std::string key;          // Item stored at a node.
    int value;
    struct entry* next; // Links to the successive node, or `nullptr`
  };                    // if at the end.
  
  struct dict {
    entry* first;       //First entry in dictionary
    int defaultValue;   //Associated value of keys without an entry
  };


  // "Builds a dict with default value 'v'"
  dict* build(int v);

  // "sets entry with key 'k' to value 'v'
  // "Creates a new entry with key 'k' if none exists
  void set(dict* D, std::string k, int v);

  // "Returns the value of the entry with key 'k'"
  int get(dict* D, std::string k);

  // "Returns python representation of dict elements 
  // "{key:value, key:value, key:value...}"
  std::string toString(dict* D);
  

  // "destructor"
 // void destroy(dict* D, int v);

}

#endif
