// 
// queue.cc
//
// Implementation of the operations for an integer queue, structured as
// a linked list.
//
// Homework 03 CSCI 221 Spring 2020
//
// Author: ??        
//

#include <string>
#include <iostream>
#include "queue.hh"

namespace queue {

  // queue::build():
  // 
  // Constructs a new empty `queue::queue` object returning a pointer
  // to it from the heap.
  //
  queue* build(void) {
    queue* newQ = new queue;
    newQ->first = nullptr; 
    newQ->last  = nullptr; 
    return newQ;
  }

  // queue::isEmpty(Q):
  // 
  // Returns true/false depending on whether `Q` is empty or not.
  //
  bool isEmpty(queue* Q) {
    return (Q->first == nullptr && Q->last == nullptr);
  }

  // queue::toString(Q):
  // 
  // Returns a string representation of the queue.  An empty queue is
  // "[]", a queue with only a head item is like "[(42)]", and a
  // longer queue looks like "[(105) 37 83]".
  //
  std::string toString(queue* Q) {
    return "[]"; // Returns a bogus value. Fix this!
  }

  // queue::enqueue(Q,item):
  //
  // Adds `item` to the end of the given `Q`.
  //
  void enqueue(queue* Q, int item) {
    // UNIMPLEMENTED
    // Write for Homework 03, Part 3.
    return;  // Does nothing. Fix this!
  }

  // queue::dequeue(Q):
  //
  // Assumes `Q` is not empty. Removes and returns the item
  // at the head (the first node) of the queue.
  //
  int dequeue(queue* Q) {
    // UNIMPLEMENTED
    // Write for Homework 03, Part 3.

    // NOTE: remember to set `Q->last` to `nullptr` when the queue
    // becomes empty!!

    return 0;  // Does nothing. Returns a bogus value. Fix this!
  }

  // queue::head(Q):
  //
  // Returns the item stored in the first node of the queue.
  //
  int head(queue* Q) {
    // UNIMPLEMENTED
    // Write for Homework 03, Part 3.
    return 0; // Returns a bogus value. Fix this!
  }

  // queue::destroy(Q):
  // 
  // Returns the storage of the nodes and the top-level `queue` struct
  // back to the heap.
  //
  // This is a "destructor", using C++'s object-oriented terminology.
  //
  void destroy(queue* Q) {
    // UNIMPLEMENTED
    // Write for Homework 03, Part 3.
    return; // Does nothing. Fix this!

  }

} // end namespace queue
