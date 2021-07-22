#!/bin/bash

# Check if program exists
if [ ! -f getpid_exit_main ]; then
    echo "getpid_exit_main doesn't exist!"
    exit 1;
fi

# Run the program and save the exit status
out=$(./getpid_exit_main)

# Get the exit status first
exit_status=$?

# Check if the output is correct (i.e. PID is not 0)
echo "$out" | grep "My PID is 0" > /dev/null
grep_status=$?

# Print the program outut"
echo "-------------"
echo "$out"
echo "-------------"

# Print the test results"
if [ "$grep_status" -eq 0 ]; then
    echo "ERROR: pid is still 0."
    exit 1
fi

if [ "$exit_status" -ne 42 ]; then
    echo "ERROR: Exit status not 42!"
    exit 2
fi

echo "OK: All tests passed"
