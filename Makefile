#
# CSCI 221 Spring 2020
#
# This is a sample Makefile that can be used for Homework 03.  It is
# described more carefully in the updated `README` in its repo.  The
# entries for the Part 3 targets rely on some special `$` "macros"
# that `make` understands. I've also defined a few other
# macros/variables, in a standard way, at the top of this file, just
# below.
#
# You'll want to read my alternate entries for `test_queue` in the
# `README` before teasing apart what I did just below. They are
# equivalent.
#

CXX=g++
CXX_FLAGS=-g -std=c++11 -fsanitize=address -fsanitize=leak
.PHONY: all clean
TARGETS=test_llist test_queue test_ordered

all: $(TARGETS)

test_llist: test_llist.cc llist.hh llist.cc
	$(CXX) $(CXX_FLAGS) -o test_llist test_llist.cc llist.cc

test_ordered: test_ordered.cc ordered.hh ordered.cc
	$(CXX) $(CXX_FLAGS) -c ordered.cc
	$(CXX) $(CXX_FLAGS) -c test_ordered.cc
	$(CXX) $(CXX_FLAGS) -o test_ordered test_ordered.o ordered.o
	rm -f test_ordered.o
	rm -f ordered.o

queue.o: queue.hh
queue.o: queue.cc
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

test_queue.o: queue.hh
test_queue.o: test_queue.cc
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

test_queue: test_queue.o queue.o
	$(CXX) $(CXX_FLAGS) -o $@ $^

clean:
	rm -f *.o *~ a.out core $(TARGETS)
