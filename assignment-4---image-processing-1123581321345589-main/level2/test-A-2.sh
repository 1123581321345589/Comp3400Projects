#!/bin/sh
input_file="../data/A.png"
output_file="A.out.png"
goal_file="../data/A.out.png"
nthreads="2"

./level2 "$input_file" "$output_file" "$nthreads"
diff "$output_file" "$goal_file"
