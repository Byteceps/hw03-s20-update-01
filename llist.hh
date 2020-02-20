// 
// llist.hh
//
// Type definitions and prototypes for an integer linked list data
// structure. 
//
// CSCI 221 Spring 2020
//
// Author: Jim Fix
//
// The code below gives the header information for a linked list data
// structure. It defines two types `llist::node` and `llist::llist`,
// the first forming the low-level struct type that's stitched together
// to store a sequence of integers, and the second providing a "housing"
// for the data structure, accepting a collection of operations on 
// that data structure.
//
// Those two types, along with the operations on `llist::llist*`, are 
// all defined under a namespace `llist`. The operations that this
// linked list supports are 
//
// * build, buildWith - construct a new linked list (on the heap)
// * insertAtFront, insertAtEnd - add an integer to the linked list
// * isEmpty, contains, length, toString - check/report the contents
// * deleteFront, deleteEnd, remove - remove an integer
// * destroy - give back the linked list's storage (to the heap)
//
// These operations are implemented in `llist.cc`.
//

#ifndef _LLIST_HH
#define _LLIST_HH

#include <string>

namespace llist {

  struct node {
    int data;          // Item stored at a node.
    struct node* next; // Links to the successive node, or `nullptr`
  };                   // if at the end.

  struct llist {
    node* first;       // Link to the first node.
  };

  // "constructors"
  llist* build(void);
  llist* buildWith(int* values, int length);

  // "mutators"
  void insertAtFront(llist* list, int value);
  void insertAtEnd(llist* list, int value);
  void deleteFront(llist* list);
  void deleteEnd(llist* list);
  void remove(llist* list, int value);

  // "accessors"
  bool isEmpty(llist* list);
  bool contains(llist* list, int value);
  std::string toString(llist* list);
  int length(llist* list); 

  // "destructor"
  void destroy(llist* list);

}

#endif
