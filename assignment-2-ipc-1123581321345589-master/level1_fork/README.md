# Level 1

For the first level, we'll be practicing using the following system calls

- fork
- wait
- getpid

## Part A

For this part, we'll be writing a program that prints the current process' PID and exits with a status code. 

The getpid() system call does what is says on the tin, it'll return the current process's pid. To study how to use this
system call, read the manpage by typing "man getpid" in the terminal (hit "q" on the keyboard to exit).

 skeleton
of the code you need to write is provided in the getpid_main.c, along with the Makefile needed to build the program. To
get started, run:

    make
    ./test_getpid_exit.sh

And there should be a single line that gets printed:

    -------------
    My pid is 0
    -------------
    ERROR: pid is still 0.

Change getpid_main.c so that the PID printed in the `printf` function, and exit with status 42.  Note that the PID will
change everytime you run the program (since every time you do so you create a new process).

## Part B

For this part, we'll be writing a program that creates a new process and have the child process print its PID, and the
parent process print the child's PID (not it's own!).

First, create a new process using the fork() system call. Then, have the parent process use the wait() system call to
retrieve the exit status of the child. Recall that to get the actual exit status, you need to use `WEXITSTATUS(status)`,
not `status`.

A successful implementation should look like the following:

	Child process PID is 47798
	I'm the parent. Their PID is 47798
	Child's status is 42

The child PID and parent PID should be the same, and the child exit status should be 42.

The fork() system call can be a bit tricky to understand. Refer to the slides for help.

### Notes on wait()

The wait() system call will have the parent process wait for the child process to complete, and the retrieve its exit
status. The system call has the following signature:

    int wait(char* p_status);

A pointer to an integer argument is passed to the system call for the kernel to fill in. The system call returns the pid
of the child process that just terminated, or -1 for error.

One thing to note is that the integer is actually the exit status PLUS other status about the child process (did it exit
or did it get a signal, etc.), so you need to wrap the argument with the WEXITSTATUS() function to get the actual value
(i.e. use `WEXITSTATUS(status)` to get the actual child's exit status.

