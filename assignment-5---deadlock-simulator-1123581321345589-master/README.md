# README

In this assignment, you will be implementing a simulator that models a manager that parcels out locks (resources), and a
bunch of workers that requests locks to the manager. Each level will be progressively more difficult, with level2_plus being
optional for extra credit.

Each level has skeleton code provided for you to get started. It will set up the two processes and establish
communication between them: all you need to do is implement specific *parts of the manager's behavior*.

## Overall Behavior

There are two types of processes: the lock manager process, which is the parent process, and the child processes. The
two processes communicate through an anonymous pipe.


The model we are using deadlock detection and recovery with rollback. Child processes request random locks. If the lock
is not available, the child starts to wait for the lock, raising the possibility of a deadlock. We simply allow the
deadlock to occur, but then detect the deadlock and start a recovery process by rolling back the last lock request. The
child process that triggered the deadlock will have its request denied, and the child process goes back and requests
another (random) lock.

