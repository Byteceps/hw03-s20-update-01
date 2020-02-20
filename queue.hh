// 
// queue.hh
//
// Type definitions and prototypes for an integer queue, implemented as a
// linked list.
//
// CSCI 221 Spring 2020
//
// Author: Jim Fix
//
// The code below gives the header information for a queue data structure.
// It defines two types `queue::node` and `queue::queue`,
// the first forming the low-level struct type that's stitched together
// to store a sequence of integers, and the second providing a "housing"
// for the queue data structure, accepting a collection of operations.
//
// Those two types, along with the operations on `queue::queue*`, are 
// all defined under a namespace `queue`. The operations that this
// linked list supports are 
//
// * build - construct a new empty queue (on the heap)
// * enqueue - add an integer to the end of the queue
// * dequeue - remove and return the item at the front of the queue
// * isEmpty - return whether the queue is empty
// * head - return the item sitting at the front of the queue
// * destroy - give back the queue's storage (to the heap)
//
// These operations are implemented in `queue.cc`.
//

#ifndef _QUEUE_HH
#define _QUEUE_HH

#include <string>

namespace queue {

  struct node {
    int data;          // Item stored at a node.
    struct node* next; // Links to the successive node, or `nullptr`
  };                   // if at the end.

  struct queue {
    node* first;       // Link to the first node.
    node* last;        // Link to the last node.
  };                   // Both are `nullptr` when empty.

  // "constructors"
  queue* build(void);

  // "mutators"
  void enqueue(queue* Q, int item);
  int dequeue(queue* Q);

  // "accessors"
  bool isEmpty(queue* Q);
  int head(queue* Q);
  std::string toString(queue* Q);

  // "destructor"
  void destroy(queue* Q);

}

#endif
