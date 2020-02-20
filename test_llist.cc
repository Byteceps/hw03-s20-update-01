//
// test_llist
//
// Homework 03 for CSCI 221 Spring 2020
//
// Author: Jim Fix
//
// This program is the *driver* for a series of tests of a linked list
// data structure implemented in the files `llist.hh` and `llist.cc`.
// The code can be compiled with the unix command line
//
//   g++ --std=c++11 -g -o test_llist test_llist.c llist.cc
//
// and then run with the unix command line
//
//   ./test_llist <values>
//
// where `<values>` is either nothing, or a space-separated list of
// integers that get used as the contents of a linked list, first
// built by the program.
//
// Once running, the program asks for a series of commands, ones that
// perform a suite of operations on that linked list. For example,
// here is an interaction made possible by the program:
//
//   $ ./test_llist 5 7 3
//   Your list is [5, 7, 3].
//   Enter a list command: insert end 42
//   Done.
//   Your list is [5, 7, 3, 42].
//   Enter a list command: delete front
//   Done.
//   Your list is [7, 3, 42].
//   Enter a list command: search 5
//   Not found.
//   Your list is [7, 3, 42].
//   Enter a list command: quit
//   Bye!
//   $
//
// The set of commands it accepts is reported by the `help` command
// and is the following:
//
//   insert front <number>
//   insert end <number>
//   delete front
//   delete end
//   remove <number>   -- UNIMPLEMENTED
//   search <number>
//   length            -- UNIMPLEMENTED
//   help
//   quit
//
// The commands `remove` and `search` don't work yet because their
// functions are unimplemented in `llist.cc`. Homework 03 Part 1 asks
// you to write these two.
//

#include "llist.hh"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

// parseCommand(command):
//
// Takes a string `command` and gives back a vector of strings,
// split into words according to spaces within `command`.
//
std::vector<std::string> parseCommand(std::string command) {
  std::istringstream iss(command);
  std::vector<std::string> words(std::istream_iterator<std::string>{iss},
				 std::istream_iterator<std::string>());  
  return words;
}

// main():
//
// This program tests our linked list code, looping
// by receiving test commands. The commands are 
// listed at the top of this page.
//
int main(int argc, char** argv) {

  llist::llist* theList;

  //
  // Build a new linked list on the heap from the integer items
  // provided on the unix command line.
  if (argc > 1) {

    //
    // If any provided, build a linked list of them, in order.
    int numArgs = argc - 1;
    int* args = new int[numArgs];
    for (int i=0; i<numArgs; i++) {
      args[i] = std::stoi(argv[i+1]);
    }
    theList = llist::buildWith(args,numArgs);
    delete [] args;

  } else {

    // 
    // If none provided, build an empty list.
    theList = llist::build();
  }

  //
  // Loop, processing commands.
  // 
  // Each command line is processed as a C++ `vector` of strings.
  std::string command;
  do {
    //
    // Get a command line from the user.
    std::cout << "Your list is ";
    std::cout << llist::toString(theList);
    std::cout << "." << std::endl;
    std::cout << "Enter a list command: ";
    getline(std::cin,command);
    std::vector<std::string> commandWords = parseCommand(command);

    // 
    // Process that command and perform it.
    std::string keyword = commandWords[0];
    
    //
    // insert <front/end> <value>
    if (keyword == "insert") {

      std::string where = commandWords[1];
      int what = std::stoi(commandWords[2]);
      if (where == "front") {
	llist::insertAtFront(theList,what);
      } else {
	llist::insertAtEnd(theList,what);
      }
      std::cout << "Done." << std::endl;

    //
    // delete <front/end>
    } else if (keyword == "delete") {

      if (llist::isEmpty(theList)) {
	std::cout << "There is nothing to delete." << std::endl;
      } else {
	std::string where = commandWords[1];
	if (where == "front") {
	  llist::deleteFront(theList);
	} else {
	  llist::deleteEnd(theList);
	}
	std::cout << "Done." << std::endl;
      }

    } else if (keyword == "search") {

      //
      // search <value>
      int what = std::stoi(commandWords[1]);
      if (llist::contains(theList,what)) {
	std::cout << "Found." << std::endl;
      } else {
	std::cout << "Not found." << std::endl;
      }

    } else if (keyword == "remove") {

      //
      // remove <value>
      int what = std::stoi(commandWords[1]);
      if (llist::contains(theList,what)) {
	llist::remove(theList,what);
	std::cout << "Done." << std::endl;
      } else {
	std::cout << "Not found." << std::endl;
      }

    } else if (keyword == "length") {

      //
      // remove
      std::cout << "The length is " << llist::length(theList) << "." << std::endl;

    } else if (keyword == "help") {

      //
      // help
      std::cout << "Here are the list commands I know:" << std::endl;
      std::cout << "\tinsert front <number>" << std::endl;
      std::cout << "\tinsert end <number>" << std::endl;
      std::cout << "\tdelete front" << std::endl;
      std::cout << "\tdelete end" << std::endl;
      std::cout << "\tsearch <number>" << std::endl;
      std::cout << "\tremove <number>" << std::endl;
      std::cout << "\tlength" << std::endl;
      std::cout << "\thelp" << std::endl;
      std::cout << "\tquit" << std::endl;

    } else if (keyword != "quit") {

      // 
      // Bad command.
      std::cout << "I don't know that command." << std::endl;
      std::cout << "Enter \"help\" to see the commands I know." << std::endl;

    }

  } while (command != "quit");

  // 
  // Say goodbye and give the linked list back to the heap.
  std::cout << "Bye!" << std::endl;
  llist::destroy(theList);
}


  
  
