//
// test_ordered
//
// Homework 03 for CSCI 221 Spring 2020
//
// Author: Julian Prince
//
// This program is the *driver* for a series of tests of an ordered dict
// data structure implemented in the files `ordered.hh` and `ordered.cc`.
// The code can be compiled with the unix command line
//
//   g++ --std=c++11 -g -o test_ordered test_ordered.cc ordered.cc
//
// and then run with the unix command line
//
//   ./test_ordered
//
//
// Once running, the program asks for a series of commands, ones that
// perform a suite of operations on that ordered dict. For example,
// here is an interaction made possible by the program:
//
//     $ ./test_ordered
//    Your dictionary is {}.
//    Enter a dictionary command: get bob
//    That key has value 0.
//    Your dictionary is {}.
//    Enter a dictionary command: set bob 42
//    Your dictionary is {'bob': 42}.
//    Enter a dictionary command: get bob
//    That key has value 42.
//    Your dictionary is {'bob': 42}.
//    Enter a dictionary command: set alice 101
//    Your dictionary is {'alice': 101, 'bob': 42}.
//    Enter a dictionary command: set carlos -6
//    Your dictionary is {'alice': 101, 'bob': 42, 'carlos': -6}.
//   Enter a dictionary command: set bob 1234
//    Your dictionary is {'alice': 101, 'bob': 1234, 'carlos': -6}.
//    Enter a dictionary command: get carlos
//    That key has value -6.
//    Your dictionary is {'alice': 101, 'bob': 1234, 'carlos': -6}.
//    Enter a dictionary command: quit
//    Bye!
//    $
//
// The set of commands it accepts is reported by the `help` command
// and is the following:
//
//  get <key>
//  set <key> <value>
//

#include "ordered.hh"
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
// This program tests our ordered dict code, looping
// by receiving test commands. The commands are 
// listed at the top of this page.
//
int main(void) {

  ordered::dict* theDict;
  //Build a new empty ordered dict on the heap, with default value '0'
  theDict = ordered::build(0);

  // 
  // Each command line is processed as a C++ `vector` of strings.
  std::string command;
  std::cout << "Your dict is ";
  std::cout << ordered::toString(theDict);
  std::cout << "." << std::endl;

// Loop, processing commands.
  do {
    //
    // Get a command line from the user.
    std::cout << "Enter a list command: ";
    getline(std::cin,command);
    std::vector<std::string> commandWords = parseCommand(command);

    // 
    // Process that command and perform it.
    std::string keyword = commandWords[0];

    //
    //get <key>
    if (keyword == "get"){
      std::string key = commandWords[1];
      int value = ordered::get(theDict, key);
      std::cout << "That key has a value of: " << value << std::endl;
      std::cout << "Your dict is ";
      std::cout << ordered::toString(theDict) << std::endl;
    }
    //
    //set <key> <value>
    else if (keyword == "set"){
      std::string key = commandWords[1];
      int value = std::stoi(commandWords[2]);

      ordered::set(theDict, key, value);
      std::string s = ordered::toString(theDict);
      
      std::cout << "Your dictionary is " << s << std::endl;
    } 
    //
    //help
    else if (keyword == "help") {
      std::cout << "Here are the list commands I know:" << std::endl;
      std::cout << "\tget <key>" << std::endl;
      std::cout << "\tset <key> <value>" << std::endl;
      std::cout << "\thelp" << std::endl;
      std::cout << "\tquit" << std::endl;
    }
    //
    //quit
    else if (keyword == "quit") {
      std::cout << "Quitting"<< std::endl;
    }

  } while (command != "quit");

  // 
  // Say goodbye
  std::cout << "Bye!" << std::endl;
}


  
  
