// 
// llist.cc
//
// Implementation of the operations for an integer linked list data
// structure.
//
// Homework 03 CSCI 221 Spring 2020
//
// Author: ??        (`length` and `remove`) 
// Author: Jim Fix   (the others)
//
// The code below gives the implementation code for a linked list data
// structure. It defines operations on a `llist::llist*` that references
// a sequence of integers. These are all packaged within the namespace
// `llist` and are as follows:
//
// * build, buildWith - construct a new linked list (on the heap)
// * insertAtFront, insertAtEnd - add an integer to the linked list
// * isEmpty, contains, length, toString - check/report the contents
// * deleteFront, deleteEnd, remove - remove an integer
// * destroy - give back the linked list's storage (to the heap)
//
// Homework 03 Part 1 asks that you complete the code for
//
//     int length(llist* list) { ... }
//
// which should traverse the linked list starting at `list->first`
// and count how many nodes are in that linked list. It then asks
// you to write the code for
//
//     int remove(llist* list, int value) { ... }
//
// which searches through the list, looking for a node with its `data`
// field equal to `value`, and excises that node from the linked list.
// (See the `deleteFront` and `deleteEnd` code to see how those cases
// are handled.) If more than one node contains that same value, then
// it only removes the first node with that value.
//

#include <string>
#include <iostream>
#include "llist.hh"

namespace llist {

  // llist::build():
  // 
  // Constructs a new empty `llist::llist` object returning a pointer
  // to it from the heap.
  //
  llist* build(void) {
    llist* newList = new llist;
    newList->first = nullptr; // Initialize it as an empty list.
    return newList;
  }

  // llist::buildWith(values, length):
  // 
  // Constructs a new `llist::llist` object, filling its nodes with
  // the integer sequence given by the array `values`, returning a
  // pointer to it from the heap.
  //
  llist* buildWith(int* values, int length) {
    //
    // Build an empty list.
    llist* newList = build();
    //
    // Insert them in reverse order onto the front.
    for (int i=0; i<length; i++) {
      insertAtFront(newList,values[length-i-1]);
    }
    return newList;
  }

  // llist::insertAtFront(list, value):
  // 
  // Adds a newly allocated node onto the front of the linked
  // `list`, one housing the given `value`.
  //
  void insertAtFront(llist* list, int value) {
    node* newNode = new node;
    newNode->data = value;
    newNode->next = list->first; // Next node is the old front.
    list->first = newNode;       // It becomes the new front.
  }

  // llist::insertAtFront(list, value):
  // 
  // Adds a newly allocated node onto the end of the linked
  // `list`, one housing the given `value`.
  //
  void insertAtEnd(llist* list, int value) {
    node* newNode = new node;
    newNode->data = value;
    newNode->next = nullptr; // It'll be the new end.

    if (list->first == nullptr) {

      list->first = newNode; // When empty, it also becomes the new front.
    } else {

      // When not empty, we traverse to find the last node, the one with null `next`.
      node* current = list->first;
      while (current->next != nullptr) { // We know `current` is valid here.
	current = current->next;
      }
      // Link the old end node to this new end node.
      current->next = newNode;

    }
  }

  // llist::isEmpty(list):
  // 
  // Returns true/false depending on whether the given linked `list` is
  // empty or not.
  //
  bool isEmpty(llist* list) {
    // A list is empty when its `first` reference is null.
    return (list->first == nullptr);
  }

  // llist::contains(list,value):
  // 
  // Returns true/false depending on whether the given linked `list` is
  // contains a node with `data` of `value`.
  //
  bool contains(llist* list, int value) {
    // Search for it with a list traversal.
    node* current = list->first;
    while (current != nullptr) {
      // Found it, return true.
      if (current->data == value) {
	return true;
      }
      current = current->next;
    }
    // Didn't find it, return false.
    return false;
  }

  // llist::deleteFront(list):
  // 
  // Modifies the given linked `list`, removing the node at the
  // front. That node's storage is returned to the heap using
  // `delete`.
  //
  void deleteFront(llist* list) {
    if (list->first != nullptr) {
      node* toDelete = list->first;
      list->first = list->first->next;
      delete toDelete;
    }
  }

  // llist::deleteEnd(list):
  // 
  // Modifies the given linked `list`, removing the node at the
  // end. That node's storage is returned to the heap using
  // `delete`.
  //
  void deleteEnd(llist* list) {
    if (list->first != nullptr) {
      // The list is not empty...
      //

      if (list->first->next == nullptr) {

	// The first node is also the end. Delete it.
	deleteFront(list);

      } else {

	// Otherwise, we find the end node and unlink it.
	//
	// We traverse the list with two consecutive pointers.
	// When the `leader` hits the node at the end, the 
	// `follower` is modified to no longer refere to it,
	// becoming the new end.
	//
	node* follower = list->first;
	node* leader = list->first->next;
	while (leader->next != nullptr) {
	  follower = leader;
	  leader = leader->next;
	}

	// Unlink the end `leader` and give it back to the heap.
	node* toDelete = follower->next;
	follower->next = nullptr;
	delete toDelete;
      }
    }
  }

  // llist::toString(list):
  // 
  // Devises a string for the linked `list`, similar to Python's
  // reperesentation. An empty list string is "[]", a singleton list
  // is like "[42]", and a longer list is like "[5, 7, 3]".
  //
  std::string toString(llist* list) {
    if (list->first == nullptr) {

      return "[]";

    } else {

      std::string s = "[";
      node* current = list->first;
      // Traverse up to the end, placing commas after each `data`.
      while (current->next != nullptr) {
	s += std::to_string(current->data) + ", ";
	current = current->next;
      } 
      // Add the last `data` (which could happen to be the `first`).
      s += std::to_string(current->data) + "]";
      return s;

    }
  }

  // llist::destroy(list):
  // 
  // Returns the storage of the nodes and the top-level `llist` struct
  // back to the heap, calling `delete` on the pointer for each.
  //
  // This is a "destructor", using C++'s object-oriented terminology.
  //
  void destroy(llist* list) {
    // Delete each node, which performs the `delete` on each.
    while (!isEmpty(list)) {
      deleteFront(list);
    }
    // `delete` the housing struct.
    delete list;
  }

  // llist::length(list):
  //
  // Returns the number of nodes in the given linked `list`.
  //
  int length(llist* list) {
    // UNIMPLEMENTED
    // Write for Homework 03, Part 1.
    return 0; // Returns a bogus value. Fix this!
  }

  // llist::remove(list,value):
  //
  // Searches for the first node in the given `list` that contains the
  // `value`. Excises it from the linked list.
  //
  void remove(llist* list, int value) {
    // UNIMPLEMENTED
    // Write for Homework 03, Part 1.
    return;  // Does nothing. Fix this!
  }

} // end namespace llist
