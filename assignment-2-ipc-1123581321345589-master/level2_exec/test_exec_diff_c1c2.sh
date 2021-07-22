#!/bin/bash
################
# This will test if we pass identical files match for Part 2b

# Check if program exists
if [ ! -f exec_diff_main ]; then
    echo "exec_diff_main doesn't exist!"
    exit 1;
fi

attempt_file=output2b-c1c2_attempt.txt
output_file=output2b-c1c2.txt

# Run the program and save the output
rm -f "$attempt_file"
./exec_diff_main c1.txt c2.txt > "$attempt_file"

# Compare the output
diff -q "$output_file" "$attempt_file" > /dev/null
diff_status=$?

# Cleanup
rm -f "$attempt_file"

# Print the test results"
if [ "$diff_status" -ne 0 ]; then
    echo "ERROR: output des not match. It's supposed to be:"
    cat "$output_file"
    exit 1
fi

echo "OK: All tests passed"
