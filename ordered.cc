// 
// dict.cc
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
// structure. It defines operations on a `dict::dict*` that references
// a sequence of integers. These are all packaged within the namespace
// `dict` and are as follows:
//
// * build, buildWith - construct a new linked list (on the heap)
// * insertAtFront, insertAtEnd - add an integer to the linked list
// * isEmpty, contains, length, toString - check/report the contents
// * deleteFront, deleteEnd, remove - remove an integer
// * destroy - give back the linked list's storage (to the heap)
//
// Homework 03 Part 1 asks that you complete the code for
//
//     int length(dict* list) { ... }
//
// which should traverse the linked list starting at `list->first`
// and count how many nodes are in that linked list. It then asks
// you to write the code for
//
//     int remove(dict* list, int value) { ... }
//
// which searches through the list, looking for a node with its `data`
// field equal to `value`, and excises that node from the linked list.
// (See the `deleteFront` and `deleteEnd` code to see how those cases
// are handled.) If more than one node contains that same value, then
// it only removes the first node with that value.
//

#include <string>
#include <iostream>
#include "ordered.hh"

namespace ordered {

  // Returns a pointer to an empty dictionary
  // Missing entires have a default associated value of 'v
  dict* build(int v) {
    dict* newDict = new dict;
    newDict->first = nullptr;
    newDict->defaultValue = v;
    return newDict;
  }

  //Returns the value associated with the entry with key 'k':
  int get(dict* D, std::string k) {
    //Check if dict is empty
    if (D->first == nullptr){
      return D->defaultValue; //Returns default value if first value is nullptr
    }
    //Search for k with dict transversal
    entry* current = D->first;
    while (current != nullptr){
      //If given k matches the key for that entry, return that entrys value
      if(current->key == k){
        return current->value;
      }
      current = current->next;
    }
    return D->defaultValue; //Return default value if k is not found
  }

  //Returns number of entries in a dictionary
  int length(dict* D){
    int count = 0;
    entry* current = D->first;
    if (current == nullptr){
      return 0;
    }
    //Transverse entries of the dictionary, incrementing count each time
    while (current != nullptr){
      count ++;
      current = current->next;
    }
    return count;
  }

  //Returns true/flase depending on whether the given dict contains an entry with key 'k'
  bool contains(dict* D, std::string k){
    //Search for it with a dict traversal 
    entry* current = D->first;
    while (current != nullptr) {
      //Key found, return true.
      if (k.compare(current->key)) {
        return true;
      }
      current = current->next;
    }
    //Didnt find key, return false
    return false;
  }
  
  //Update dictionary so that value 'v' is associated with 'k'
  void set(dict* D, std::string k, int v){
    int length = ordered::length(D);
    //If dict is not empty
    if (D->first != nullptr){
      //Search for k with dict transversal
      entry* current = D->first;

      //Check for dict of length 1 with same key as 'k'
      if (length == 1 && k.compare(current->key) == 0){
        current->value = v;
        exit(0);
      }
      else {
        while (current->next != nullptr){
          //If k is found, update the value of that entry with v
          if (k.compare(current->key) == 0){
            current->value = v;
            exit(0);
          }
          current = current->next;
        }// write a contains function
      }

      //If k is not found, add an entry to the end with key 'k' and value 'v'
      entry* newEntry = new entry;
      newEntry->key = k;
      newEntry->value = v;
      newEntry->next = nullptr; //New end
      //Link old end entry to new end entry 
      current->next = newEntry;
    }
    else {    
      //If dict is empty, make the first entry with key 'k' and value 'v'
      entry* newEntry = new entry;
      newEntry->key = k;
      newEntry->value = v;
      newEntry->next = nullptr;
      D->first = newEntry; 
    }
  }//End set

  //Give back a python representation of the dictionary 
  std::string toString(dict* D){
    //If dict is empty
    if (D->first == nullptr) {
      //Return empty list
      return "{}";
    }
    else {
      std::string s = "{";
      entry* current = D->first;
      // Traverse up to the end, placing commas after each `entry`.
      while (current->next != nullptr) {
	      s += current->key + ":" + std::to_string(current->value) + ",";
	      current = current->next;
      } 

      // Add the last `entry` (which could happen to be the `first`).
      s += current->key + ":" + std::to_string(current->value) + "}";
      return s;
    }
  }
  //void destroy(dict* list) {
    // Delete each node, which performs the `delete` on each.
   // while (!isEmpty(list)) {
     // deleteFront(list);
   // }
    // `delete` the housing struct.
   // delete list;
 // }

} // end namespace ordered
