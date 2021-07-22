# Compilers use flags to control what options are used to compile the C source code. Commonly called CFLAGS
#  - The compiler is pretty smart and can warn you of various things. Use "-Wall -Wextra" to enable them
#  - We'll be using the 2011 version of C with GCC specific extensions (needed later in the course). Use "-std=gnu11"
CFLAGS:= -Wall -Wextra -std=gnu11

# Linkers also use flags to control the options used. Commonly called LDFLAGS
LDFLAGS:= -Wall -Wextra -std=gnu11

# The list of programs this Makefile will build
PROGS:= pipe_main

# This line tells what to do when we type "make":
all: $(PROGS)

# This line tells what to do when we type "make clean": removes all .o files and the list of programs in PROGS
clean:
	$(RM) *.o $(PROGS)

# This is the line that will compile and build the main program for for Level 3
pipe_main: pipe_main.o
	$(CC) ${LDFLAGS} $^ -o $@

