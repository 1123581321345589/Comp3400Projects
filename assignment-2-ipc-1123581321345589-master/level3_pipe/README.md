# Level 3

For the third level, we'll be practicing using the pipe() system call.

Use the pipe() system call and the fork() system call to create a pipe that the child will write to, and the parent will
read from. Using this pipe, the child process should return a struct containing a pair of variables:

| Type | Name    | Value |
|------|---------|-------|
| int  | seconds | 10    |
| int  | milli   | 500   |

which should be read by the parent. The parent should then print the results using the following format:

    Child results
    10 seconds 500 milli-seconds

The pipe system call has a number of pitfalls that can make it tricky to use. Refer to the slides for help.

## Review of read() and write()

The read() and write() system calls can be used to read data from and write data to a pipe. The first argument to these
functions should be the appropriate descriptor: either the read descriptor returned from the pipe, or the write
descriptor.

The second and third arguments to these system calls are pointers to the variables that we wish the send/receive, and
the size of those variables. For example, if you have the time struct from PA1:

    struct time {
        int seconds;
        int milli;
    };

You can send data using the following code:

    struct time t1 = { .seconds = 1, .milli = 0 };
    write(fd, &t1, sizeof(t1));

and read the same data using the following code:

    struct time t0;
    read(fd, &t0, sizeof(t0));

