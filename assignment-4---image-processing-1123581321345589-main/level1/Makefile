# Compilers use flags to control what options are used to compile the C source code. Commonly called CFLAGS
#  - The compiler is pretty smart and can warn you of various things. Use "-Wall -Wextra" to enable them
#  - We'll be using the 2011 version of C with GCC specific extensions (needed later in the course). Use "-std=gnu11"
#  - We need to tell the C library we'll be using threads, so use "-pthread" to do so.
CFLAGS:= -Wall -Wextra -Wno-unused-parameter -std=gnu11 -I ../include -pthread
LDFLAGS=
# Linkers also use flags to control the options used. Commonly called LDFLAGS
LIBS:=-lm -pthread

# The list of programs this Makefile will build
PROGS:=level1

# This line tells what to do when we type "make":
all: $(PROGS)

# This line tells what to do when we type "make clean": removes all .o files, list of programs in PROGS and temporary
# files
clean:
	$(RM) *.o $(PROGS) *.out.png

# This is the line that will compile and build the main program for for Level 1
level1: level1.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)
