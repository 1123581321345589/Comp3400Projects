# README

In this level, you will be implementing a lock manager that manages two worker. Because there are multiple workers, this
time there IS a possibility of deadlock. 

A child process will request random locks, and the manager will either grant the request (GRANTED), or return the
request because the lock was already held by the same worker (YOU_OWN_IT) or tell the worker to wait (NOT_GRANTED).

Once a child is told to wait, the child process should be added to a per-lock wait list. Once the lock has been released,
one of those processes are granted the lock and released from waiting. The lock manager sends back a GRANTED status to
the waiting process.

Unfortunately because the child is waiting, this can lead to a deadlock situation. If a deadlock has been detected
(which you will implement), the request is canceled and the lock manager sends back a PREVENT status.

## Lock Manager

The lock manager waits for requests from each child processes by calling `read` on each child process' pipe for each
process (child 0 through child N and then loop back). When a child submits a request, the `read` operation returns with
a `msg_requestLock` message, and the parent process called the LockManager() function with the ID of the process, the
message, and the pipe to send a response back through.

- If the request was RELEASE, then the lock manager should release all locks currently held by the child process
- If the request was LOCK, then things become more interesting. one of the following can occur:
    * The lock is not held by anyone (NOTMARKED). In this case, the manager can just grant the request (GRANTED).
    * The lock held by yourself. In this case, the manager just sends it back with YOU_OWN_IT.
    * The lock is held by someone else. In this case, the manager sends back a NOT_GRANTED, and the child starts
        waiting.

## Child Processes

The child processes will execute the child() function. The child function simply loops forever, requesting random locks
and processing the requests' responses. Because the requested lock is 

Once the number of locks exceeds the MAXCHILDLOCKS, the child process sends a `RELEASE` message to the lock manager to
release all locks.

The state machine of a child process looks like the following:

- RUNNING -> send(LOCK) -> receive(GRANTED) -> RUNNING
- RUNNING -> send(LOCK) -> receive(YOU_OWN_IT) -> RUNNING
- RUNNING -> send(LOCK) -> receive(NOT_GRANTED) -> WAITING -> GRANTED -> RUNNING
- RUNNING -> send(LOCK) -> receive(NOT_GRANTED) -> WAITING -> PREVENT -> RUNNING
- RUNNING -> send(RELEASE) -> RUNNING

As you can see, once a process starts waiting, it gets either a GRANTED status or a PREVENT status.

## The Wait List

One important data structure used by this level is the wait list. The wait list indicates lock each process is waiting
for. So, for this level, there are 4 possiblities:

1. -1, -1: No one is waiting
2. La, -1: Process 0 is waiting for lock A, but 1 is not waiting
3. -1, Lb: Process 1 is waiting for lock B, but 0 is not waiting
4. La, Lb: Process 0 is waiting for lock A and process 1 is waiting for lock B

Of the 4 possibilities, the last case will be most interesting, because this indicates a possible deadlock. In this
level, you can assume that each process is probably waiting for each other, call deadlock and start the recovery
process. This means the last request should be canceled by the LockManager (who sends a `NOT_GRANTED` message). You also
need to make sure the wait list reflects this change as well.

## Printing Wait Status:

One TODO that you need to do in this level is print the status of each process' wait situation. One example might be:

    [   L3,  NA]

So process 0 is waiting for lock 3 to become free, and process 1 is NOT waiting for any lock


