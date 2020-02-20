# Homework 03: linked lists

*Due 2/21 by 3pm*

---
 
This is the initial repository for the third homework assignment for
the Spring 2020 offering of Reed's CSCI 221.

This folder contains an implementation of a linked list *library*, as
implemented in the two source files `llist.hh` and `llist.cc`. Neither
of these files have a `main` in them. Instead, they can be compiled
with other program source code that needs to use a linked list to
structure its data. (This is often called the *client code* to the
`llist` library we've invented.) This folder also contains a sample
client program, the source file `test_llist.cc` that is simply a
"driver" program that can be used to test the linked list code.

This assignment has three parts. Part 1 asks you to complete the 
implementation of the `llist` library, adding the two methods
`length` and `delete`. You can test these by compiling and running
the driver program. Parts 2 and 3 each ask you to mimic this code
by inventing a linked list implementation of an *ordered dictionary*
data structure and also a linked list implementation of a *queue*
data structure.

Once you've completed the assignment, then, you will have edited
or created 7 files that you'll need to submit, namely

    llist.cc (Part 1)
    order.cc order.hh test_order.cc (Part 2)
    queue.cc queue.hh test_queue.cc (Part 3)

Please work to mimic the 
[coding style guidelines](https://jimfix.github.io/csci221/assigns/C_style_guide_hw02.html) 
and formatting I've
suggested so far. Include comments that describe the code, when
appropriate. Include some comments at the top of your source code,
including your name and other brief info describing the program. There
should also be a brief comment that precedes each struct, function, 
and procedure definition you write. Mimic the work I've produced for
the `llist*` files here.

You should work to complete each of these exercises so that they
compile and run correctly. Should you face problems in solving an
exercise, you can still submit broken code. In your top comment in
that file **PLEASE** *let us know in what way the code is broken* (why
it doesn't compile, or what tests failed, etc.). In many cases, we are
willing to give partial credit if you identify problems in the code.

### Running the starter code

You might find it useful to start by just compiling and running the
provided program. It can be compiled with the unix command line

    g++ --std=c++11 -g -o test_llist test_llist.c llist.cc

and then run with the unix command line

    ./test_llist <values>

where `<values>` is either nothing, or a space-separated list of
integers that get used as the contents of a linked list, first
built by the program.

Once running, the program asks for a series of commands, ones that
perform a suite of operations on that linked list. For example,
here is an interaction made possible by the program:

    $ ./test_llist 5 7 3
    Your list is [5, 7, 3].
    Enter a list command: insert end 42
    Done.
    Your list is [5, 7, 3, 42].
    Enter a list command: delete front
    Done.
    Your list is [7, 3, 42].
    Enter a list command: search 5
    Not found.
    Your list is [7, 3, 42].
    Enter a list command: quit
    Bye!
    $

The set of commands it accepts is reported by the `help` command and
is the following:
 
    insert front <number>
    insert end <number>
    delete front
    delete end
    remove <number>  
    search <number>
    length
    help
    quit
 
Two of these commands won't do anything. The `remove` and `length`
commands will be implemented in the Part 1 exercises.

### Debugging linked list code

There are several tricky things about writing C++ code that works
with pointers. The most frequent bug in your code that you'll encounter
is a `Segmentation fault.` This arises when you attempt to access the
`data` or `next` field of a `node*`, say for example, with expressions
like `list->first->data` or `current->next`.  In each (see the `llist`
code) the expressions `list->first` and `current` are each of type
`node*`, so they could each be pointing to a valid struct of type `node`.
Or it's possible that each could be a `nullptr`.

I've trained myself, when writing linked list code, to worry quite a
bit any time my code accesses one of these fields. When I type
`->data` or `->next` an alarm goes off in my coding mind, asking the
question "*Could this pointer be null??*" I then work hard to either
(a) convince myself that the line of code cannot face that situation,
that I've eliminated the `nullptr` scenario by handling such cases
with conditional statements (or, because the condition on my loop
prevents that scenario within its body). Or (b) I realize that a
`nullptr` is actually possible at that moment, and develop more
complex code that handles that case.

Nevertheless, I still make mistakes, and so there are a few strategies
I use for figuring out the cause of a segmentation fault. One useful
strategy is to add output lines before and after lines of code that
are suspect. You can, for example, output the value of a pointer using
`std::cout <<` just before a line that relies on a pointer being valid.
If the output is the `nullptr`, with hexadecimal address `0x0`, then
I've found my bug.

Alternatively, most of you will have installed C++ and command-line
console tools that provide a debugger. On most people's systems, the
debugger tool is called `gdb`. This is the debugger provided with the
Gnu compiler suite (which includes `g++`). On many Mac OSX systems,
the debugger is instead provided as part of the LLVM compiler tools,
and the command is named `lldb`.

I'll work to show these commands' use in lecture and in lab, and your
tutors are also familiar with them. But, at a minimum, you can use a
debugger in a limited way to at least identify the line of code where
your segmentation fault is occurring. Below shows an interaction that
results from me testing my `llist` library when it had a bug in my
`deleteEnd` procedure. (I had forgotten to check if the list only
had one item in it.)

Here is that interaction:

    $ lldb test_llist
    (lldb) target create "test_llist"
    Current executable set to 'test_llist' (x86_64).
    (lldb) run 5 7 3
    Process 4586 launched: '/Users/jimfix/git/ReedCS2-S20/Lec03-3-examples/test_llist' (x86_64)
    Your list is [5, 7, 3].
    Enter a list command: delete end
    Done.
    Your list is [5, 7].
    Enter a list command: delete end
    Done.
    Your list is [5].
    Enter a list command: delete end
    Process 4586 stopped
    * thread #1: tid = 0x23d84, 
    0x0000000100007ac8 test_llist`llist::deleteEnd(list=0x00000001003000b0) + 56 at llist.cc:76,
    queue = 'com.apple.main-thread', stop reason = EXC_BAD_ACCESS (code=1, address=0x8)
    frame #0: 0x0000000100007ac8
    test_llist`llist::deleteEnd(list=0x00000001003000b0) + 56 at llist.cc:76
       73
       74      node* follower = list->first;
       75      node* leader = list->first->next;
    -> 76      while (leader->next != nullptr) {
       77        follower = leader;
       78        leader = leader->next;
       79      }
    (lldb) print leader
    (llist::node *) $0 = 0x0000000000000000
    (lldb) quit
    Quitting LLDB will kill one or more processes. Do you really want to proceed: [Y/n] Y
    $
     
In the above, I loaded the program into the debugger and ran it with
`run 5 7 3`. This is equivalent to just running the program in the
console with this command line

    $ ./test_llist 5 7 3

except it gets watched over by the debugger. After a few `delete end`
commands, making the list have only one element, my code then crashed
in the middle of `deleteEnd` at line 76 in `llist.cc`. I next printed
the value of the pointer `leader` and discovered that it was a null
pointer.

You can do similar work while developing your solutions. The key thing
that we did to enable this debugging was to compile the code with the
debug flag `-g`. This produces a different executable, one that's
filled with extra code information that both `gdb` and `lldb` can use
to give better feedback on your running program.

---

### Separate compilation: "header files" versus source files

Take a careful look through the starter code in the three files
`llist.cc`, `llist.hh`, and `test_llist.cc`. What you are seeing is a
more elaborate, and more careful, modularization of a program that
interacts with its user, manipulating a linked list data
structure. Rather than have one large program source file, I've
instead broken up the C++ code into the two files `llist.cc` and
`test_llist.cc`. I've also then written a *header file* `llist.hh` which
defines the linked list data structure and its operations. 

This header file is needed for several reasons, but overall because of
the way the C++ compiler works. It compiles each `.cc` file *on its
own*, and then combines that separately compiled code (the combining
of the code is called *linking*) into a single executable. I'll 
describe more how the header file is used, but the short of it is that 
this header file contains information about the `llist` structs and 
functions that are needed during the compilation of both `llist.cc`
and `test_llist.cc`.

The idea here is that the `llist.hh` and `llist.cc` files could be
combined with any program that needs a linked list, not just the tester
code. They are not specially written just for `test_llist` and can be
seen as a *library* that the tester relies on.

You'll notice, further, that my library code in `llist.cc` and
`llist.hh` define a *namespace* named `llist` that serves as the
prefix for all the type and function names it defines. So that means
that the test program defines a variable like so:

    llist::llist* theList;

to talk about a pointer to a `llist` struct named `theList`. And it
calls functions like so

    llist::insertAtFront(theList,what);

to invoke the ones named and defined in `llist.cc`.

The `llist::llist` and `llist::node` structs are defined separately in
the *header file* named `llist.hh` and the test program and the
implementation code each need to use those definitions, the files
`test_llist.cc` and `llist.cc` each have a line on the top reading

    #include "llist.hh"

This has the effect of asking the compiler to load in those definitions
when it is compiling that C++ source code. That is, when the compiler
is looking through the code in `llist.cc`, it needs to know the definitions 
that are provided in `llist.hh`, and so they are `#include`-ed at the top.
And when the compiler is reading the code for `test_llist.cc`, it needs
those definitions from `llist.hh` as well, and so they get stitched in
by the `#include` directive at the top of its file.

Finally, you'll notice that the `llist.hh` file has the three special
`#ifndef`, `#define`, and `#endif` directives surrounding the struct
and function declarations. This are needed due to some technical
idiosyncracies of how C++ compilation works, inherited from C. They are
used to make sure that no compilation `#include`s this information more
than once.

We'll continue to write C++ source code in this modular fashion. You'll be
asked to mimic this style in Parts 2 and 3 of this homework.

---

### Part 1: complete `llist`

Modify the source code for the file `llist.cc` and complete the code
for the two linked list functions `length` and `remove`. These should
act as follows:

• `int length(llist* list)`: Return the number of nodes in a given
linked list. To do this, just initialize a count variable to 0,
and travers the list's nodes with a loop, starting with `list->first`.
For each node you touch during that traversal, increment that count.
When the loop is done, return that count.

Look at the code for several of the linked list functions, many of which
using some variant of a linked list traversal. You'll want to do the same,
or similar. This code should work for *any* length list, including lists
of length 0 and length 1. You'll want to test the code in all these cases.

• `void remove(llist* list, int value)`: Search through the nodes of
the given linked list, looking for the first occurrence of a node
whose `data` component matches `value`. When you find that node,
excise it from the list and call `delete` on its pointer. The code
can be written to assume that the list contains `value` in *some*
node.

For `remove`, you'll want to write code that is a hybrid of the
function `contains`, the function `deleteFront`, and the function
`deleteEnd`. This is because, as you'll discover you'll want 
to handle two cases: the case where `value` equals the integer
stored at `list->first->data`, and the case where its in one 
of the subsequent nodes. In the former case, you can just rely
on `deleteFront`. In the case where `value` sits in a node
beyond the first one, you'll want to traverse down the list
with `leader` and `follower` pointers, just like `deleteEnd`
does, and look for whether `leader->data` holds `value` (somewhat
similar to what needs to be done in `contains`). 

But then, unlike any code we've written so far, you'll want to change
`follower->next` so that it skips over the `leader` node, and links one
node beyond. You'll then want to call `delete` on the node where 
`value` was found.

---

### Part 2: write `ordered`

For this exercise, you're going to invent a different linked list data
structure that holds a sequence of *key-value* pairs, sorted by the
key. This is called an *ordered dictionary* data structure. We'll make
the keys of type `std::string` and we'll have each key's associated
value be of type `int`. The resulting code will mimic many aspects of
Python's `dict` type, except entries won't be removed, and missing
entries will have a default associated value of 0.

Probably the best way to get started with this assignment is to make
copies of the `llist` code. You could type these three commands:

    cp llist.hh ordered.hh
    cp llist.cc ordered.cc
    cp test_llist.cc test_ordered.cc

In those files, you'll want to change every line that has

    #include "llist.hh"

so that `ordered.hh` is included instead. And we'll also instead
use a new namespace called `ordered` and invent a new struct type
called `dict` (rather than `llist` and `llist` in Part 1). Your
`main`, then, will ultimately test the use of a value of type
`ordered::dict*` rather than `llist::llist*`. We'll also 
use `entry` as the type name for its linked list nodes, rather
than the type name `node`. So in `ordered.cc` we'll have pointers
of type `entry*` rather than `node*`.

In `ordered.hh` define a `struct entry` that contains three components:

• `key`: a `std::string` value stored for a dictionary entry,  
• `value`: an `int` stored for each entry, associated with its key string, and  
• `next`: a `struct entry*` pointer to the next entry in the dictionary.

Also in `ordered.hh` define a `dict` struct that contains two components:

• `first`: an `entry*` that points to the first entry in the dictionary, or is `nullptr`, and  
• `defaultValue`: an `int` that represents the associated values of keys that don't yet have an entry.

You are to define these functions in `ordered.cc`:

• `dict* build(int v)`: returns a pointer to an empty dictionary.  Missing entries have a default associated value of `v`.
• `int get(dict* D, std::string k)`: returns the value associated with the entry with key `k`, or
the default value if that key has no entry yet in `D`.  
• `void set(dict* D, std::string k, int v)`: updates `D` so that value `v` is associated with key `k`.
This could either add an entry into the linked list if `k` doesn't yet have one, or update 
an existing entry if `k` has one.
• `std::string toString(dict* D)`: give back a Python representation of the dictionary's 
existing entries, and in increasing alphabetical order by their keys.

For all of these functions, the linked list that you maintain should be in *alphabetical order of
the entry's keys*.  This means that your `set` operation will have to find the place where it needs
to place an entry, when it discovers that the entry `k` doesn't yet exist. This also means that
your code for `get` can exit the traversal loop early. It won't need to traverse *all* the nodes
to discover that a key has no entry.

You'll want to modify the testing code's `main` so that it tests the `set` and `get` operations.
It should start by building an empty `order::dict*`, accept a series of those commands to
modify that ordered dictionary, and it should output the `order::toString` of the dictionary
that results from each change. Include `help` and `quit` commands, too.

Note that you can get rid of the `main` code that processes `argc` and `argv`, instead
having it declared as type `int main(void)`. You'll want to keep the `parseCommand` code to
figure out the user's inputs for the commands `get <key>` and `set <key> <value>`.

Here is a transcription of the `test_ordered` code working:

    $ ./test_ordered
    Your dictionary is {}.
    Enter a dictionary command: get bob
    That key has value 0.
    Your dictionary is {}.
    Enter a dictionary command: set bob 42
    Your dictionary is {'bob': 42}.
    Enter a dictionary command: get bob
    That key has value 42.
    Your dictionary is {'bob': 42}.
    Enter a dictionary command: set alice 101
    Your dictionary is {'alice': 101, 'bob': 42}.
    Enter a dictionary command: set carlos -6
    Your dictionary is {'alice': 101, 'bob': 42, 'carlos': -6}.
    Enter a dictionary command: set bob 1234
    Your dictionary is {'alice': 101, 'bob': 1234, 'carlos': -6}.
    Enter a dictionary command: get carlos
    That key has value -6.
    Your dictionary is {'alice': 101, 'bob': 1234, 'carlos': -6}.
    Enter a dictionary command: quit
    Bye!
    $
    
Note that `main` creates a dictionary whose default value is 0. 

You *do not* need to write a destructor `destroy`, but you are welcome
to as a BONUS exercise.

**RECOMMENDATION**: I recommend getting this code working first
without it putting the keys in sorted order. Once you've got it
working in that way, change `set` so that it inserts the keys in the
right order. There are several cases you'll need to consider in that
code to get it to work correctly. It's tricky.

---

### Part 3: write `queue`

A *queue* is a container data structure that holds a set of items, and
keeps track of the order that they were added to the queue. The item
at the front, called the *head* of the queue, was the item that was
first added.  The item at the end is the item that was last added. The
items in between are ordered from the earliest added after the head,
to the latest added, working from front to back. The operation for
adding an item to the back of the queue is normally called *enqueue*.

An item can be removed from the queue using the operation called
*dequeue*. With queues, however, you can't just remove any of the
items it stores.  Rather, instead, the next item removed with a
dequeue is the one at the front of the queue, the head item. 
It gets removed from the front, and so the next item in line
becomes the new head, unless of course that dequeued item was
the only item in the queue.

We'll see how queues are used in search and graph algorithms later,
but for now we simply want to practice writing more linked list code.
This exercise asks you to complete the code in `queue.cc` for a linked
list data structure `queue::queue` defined in `queue.hh` and tested
in `test_queue.cc`. Once all your code is working, this is the
kind of interaction I'd expect:

    $ ./test_queue
    Your queue contains []
    Enter a command: head
    Your queue is empty and has no head.
    Your queue contains []
    Enter a command: enqueue 1
    Your queue contains [(1)]
    Enter a command: enqueue 2
    Your queue contains [(1) 2]
    Enter a command: enqueue 3
    Your queue contains [(1) 2 3]
    Enter a command: head
    1 is at the head of your queue.
    Enter a command: dequeue
    1 was removed from the head of your queue.
    Your queue contains [(2) 3]
    Bye!
    $

The code currently compiles and runs, but several of the queue functions
aren't properly written. Finish the code in `queue.cc`. These two
are already written:

• `build`: constructs, initializes, and returns an empty queue.  
• `isEmpty`: returns whether or not the queue is empty.  

The others, listed just below, need to be written by you.

To implement a queue as a linked list, we use two node pointers
`first` and `last`, so each is of type `node*`. An empty queue has
both of these attributes set to `nullptr`. A queue with only one item
has `first` and `last` pointing to the same `node` struct. A queue
with more items has `first` pointing to the head item's node, that
node points to the next item in line, and so on, and the queue has
`last` pointing to the node whose `next` attribute is a `nullptr`.

Here are the other operations you need to complete:

• `enqueue`: taked an integer and places it, in a `new` linked list
node, at the end of the queue. When the queue isn't empty, you can
use `last` to append to the end.

• `dequeue`: this should remove and return the value stored at the front
node of the queue. **NOTE:** you should also deallocate its linked list 
node removed by calling `delete` on its pointer. **ALSO NOTE:** you
should make sure that both `first` and `last` are made null should
this removed head be the only item that was in the queue.

• `head`: this should return the value stored at the front node of the
queue.

• `toString`: this should create and return a string that represents the
contents of the queue. Mimic the sample output above.

• a destructor that dequeues each of the items in the queue (and thus, as
a side effect) gives back each of their linked list node's storage to the
heap. It should then `delete` the pointer of the `queue` itself.


---
