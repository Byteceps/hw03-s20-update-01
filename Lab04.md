# Lab 04: Some useful tools

Today I'll give you time to complete the work on Homework 03, due before
lecture tomorrow. I'll also use our lab time to show you a few tools,
namely

1. Using `git` commands to obtain updates to an assignment repository.
2. The `make` facility with samples of a `Makefile`.
3. The `-fsanitize=` compiler option for diagnosing memory `leak` problems and
bad `address` accesses.
4. Using a compiler-supported debugging tool (either `gdb` or `lldb`).

The last of these is described a bit in the `README.md` that came with
your initial `hw03-` repository built by Git Classroom. The first of
these I'll take you through below here, where we'll use `git` updates to
reconfigure your Homework 03 repository so that we can play with #2 and
#3.

---

### Getting updates

It's typical, especially for larger assignments, that I find errors in
the code I provide or need to give clarification in the descriptions I
give. So far I've provided that information by email, and then have to
communicate changes to the files within the text of that email.
Sometimes I also have to distribute entirely new source code with an
attachment. If you've already started working on the code, made good
progress, then you'll maybe have to work a bit harder to incorporate
my changes into your work.

It turns out that this is a typical activity that happens in the
engineering of shared code of a software project, and so `git` has
tools that help developers incorporate these kinds of updates to,
say, a branch that they've checked out to contribute their work.
Using Git lingo, a code developer may need to `fetch` changes and
updates from an `upstream` repository, and then work to `merge`
those changes into the source code they've been editing.

Let's work to perform these steps. I've cloned my *template repository*
for Homework 03, the one Git Classroom uses to stamp out each of your
`hw03-your-Git-name` folders, and I've made it public. It's called/linked
at [ReedCS2-S20/hw03-s20-update-01](https://github.com/ReedCS2-S20/hw03-s20-update-01/]. It has a few updates and fixes within it namely:

* A fix to my `test_queue.cc` that replaces a `queue::dequeue` call
with a `queue::head` call, in the command loop condition for `head`.

* A longer write-up above Part 1 in the `README.md` that includes some
information about using the `make` tool, just after the write-up about
`gdb`/`lldb`.

* Two extra files named `Makefile` and `bad_queue.cc`.

To obtain these using Git's "*fetch/merge from an upstream*" facility
follow these steps:

* Make sure you are in your `hw03-` local repo folder (or get there with
`cd` commands).

* Make sure you are working on your work branch (or switch with the
`git checkout work` command).

* Configure your repo so that it can "*pull from an upstream* repo", namely
the one I've created with the updates. Type:

    git remote add upstream https://github.com/ReedCS2-S20/hw03-s20-update-01.git
* Attempt to "fetch and merge" my updates into your local repository
using the `git pull` command, like so:

    git pull upstream master --allow-unrelated-histories

This ends up fetching the files that have been changed in the `master`
branch of my updated repo and then, comparing them to your own versions,
attempting to merge those changes individually with each file. If you
hadn't started working on Homework 03, you'd get something like the
following:

    From https://github.com/ReedCS2-S20/hw03-s20-update-01
     * branch            master     -> FETCH_HEAD
    Auto-merging test_queue.cc
    CONFLICT (add/add): Merge conflict in test_queue.cc
    Auto-merging README.md
    CONFLICT (add/add): Merge conflict in README.md
    Automatic merge failed; fix conflicts and then commit the result.

These are all fine report lines, though may appear otherwise. In my
report above I'm learning that two of the files differed enough to
for `git` to warn you about the merge activity. In fact, it actually
edited those two files, `README.md` and `test_queue.cc`, in a way
that highlights the changes that my update provides.

We'll look at these together, go through them, so that you can
incorporate the changes should you choose to do so.

The remainder of today's lab will work from the `README.md` and those
other newly provided files.

The take-away from the `pull` exercise above is that I'll probably use
Git to communicate fixes and clarifications in future assignments for
this course.










