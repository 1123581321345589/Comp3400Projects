# README

In this level, you will be implementing a lock manager that manages more than two workers. Because there are multiple workers, this
time there IS a possibility of deadlock. 

THIS LEVEL IS OPTIONAL FOR EXTRA CREDIT.

## The Wait List

One important data structure used by this level is the wait list. The wait list indicates lock each process is waiting
for. Since we have multiple processes all waiting for multiple locks, it becomes a bit more challenging to figure out if
there is a deadlock.

First, you need to convert the wait list into a wait-for table.  Recall that a wait-for table is a table with one entry
per process, and indicates which other process each process is waiting for. One example might look like the following:

    [  P1, NA, P3, P2]

P0 is waiting for P1 (or, more accurately, a lock that P1 is holding). P2 is waiting for P3 and P3 for P2, which means
there is a deadlock, and we need to recover.
