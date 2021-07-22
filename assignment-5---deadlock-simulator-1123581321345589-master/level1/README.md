# README

In this level, you will be implementing a lock manager that manages a single worker. This will allow you to get use to
the code base and guide you to start thinking about the eventual multi-worker assignment. Because there is only a single
worker, there is no possibility of a deadlock occurring. However, you will still implement lock request and release
behaviors.

A child process will request random locks, and the manager will either grant the request (GRANTED), or return the
request because the lock was already held by the sole worker (YOU_OWN_IT).

After the worker is holds more than `MAXCHILDLOCKS` locks, the worker submits a `RELEASE` request. The manager, upon
receiving this request, should release all locks held by the worker.

## Lock Manager

The lock manager waits for requests from each child processes by calling `read` on each child process' pipe for each
process (child 0 through child N and then loop back). When a child submits a request, the `read` operation returns with
a `msg_requestLock` message, and the parent process called the LockManager() function with the ID of the process, the
message, and the pipe to send a response back through.

- If the request was RELEASE, then the lock manager should release all locks currently held by the child process
- If the request was LOCK, then things become more interesting. one of the following can occur:
    * The lock is not held by anyone (NOTMARKED). In this case, the manager can just grant the request (GRANTED).
    * The lock held by yourself. In this case, the manager just sends it back with YOU_OWN_IT.

## Child Processes

The child processes will execute the child() function. The child function simply loops forever, requesting random locks
and processing the requests' responses. Because the requested lock is 

Once the number of locks exceeds the MAXCHILDLOCKS, the child process sends a `RELEASE` message to the lock manager to
release all locks.

The state machine of a child process looks like the following:

- RUNNING -> send(LOCK) -> receive(GRANTED) -> RUNNING
- RUNNING -> send(LOCK) -> receive(YOU_OWN_IT) -> RUNNING

## Printing Lock Status:

One TODO that you need to do in this level is print the status of each lock. One example might be:

    [   P0,FREE,  P0,FREE,FREE,...]

So print P0 if child process 0 is holding that lock, or FREE if the lock is free.

## Running the simulator

You can build the code using the `make` command, and run the simulator by using the `./level1` command:

    make
    ./level1

This will launch the simulator which will run indefinitely. Press Control+C to terminate it.
