# Level 2

For the second level, we'll be practicing using command-line arguments, and the exec() system call.

## Part A

For this part, you'll practice using command-line arguments.

As a reminder, command line arguments are arguments to the entire program (as opposed to functions). For example, if you
use the `cp` command, you can give it two arguments: the original name, and the copy's name, like so: `cp README.md
README-copy.md`. From `cp`'s point of view, the main program gets the following arguments:

- argc is 3, because there are 3 arguments (including the name of the program)
- argv is an array of 4 elements
    * argv[0] is a c-string of the name of the program
    * argv[1] is the first real argument, README.md
    * argv[2] is the second real argument, README-copy.md
    * argv[3] is the last element, and contains NULL (which acts as a terminator).

Write a program that will read the command line arguments and print them one by one, in the following fashion:

    argc: 3
    argv[0]: ./args_main
    argv[1]: README.md
    argv[2]: README-copy.md

## Part B

For this part, you'll be prahe program first gets 2 command line arguments.
We'll then use these arguments and call the `/usr/bin/diff` program to compare the two. If the two are identical, the diff
program exits with status 0, if not, the exit status is NOT 0. For example, you can call the program

    /usr/bin/diff -q c1.txt c3.txt

which will print the output:

    Files c1.txt and c3.txt differ

and the exit status will be non-zero.

Note that we need to correctly check for 

### Notes on using exec()

The exec() system can be a bit tricky to use. There are *multiple* (!) different versions of this system call, and the
version we'll be using is execv (notice the "v" at the end).

For example, to run the "ls -l" command, this is what you need to do: first create an array of arguments, and then do
the execv() system call:

    char* args[] = { "ls", "-l", NULL };
    int ret = execv("/usr/bin/ls", args);
    if(ret == -1) {
        perror("Problem with exec");
    }

What the first line does is create an array of arguments. The array is the same as argv. In other words, the 0th element
is the name of the program ("ls"), the second element is are the argument to the program, "-l", last, the array is
terminated with NULL.

The second line does the actual system call. The first argument is the program path and name. It is important to provide
the full path to the program (i.e. /usr/bin/ls instead of ls), because otherwise exec will not be able to find the
program. We also keep a copy of the return value in a variable called `ret`.

Next, we check if the return value was -1. If it is, there was an error, so we use a special version of puts called
perror which will also print the reason for the system call failing. It is important that you check for the return
value since it is critial for debugging issues with exec().

