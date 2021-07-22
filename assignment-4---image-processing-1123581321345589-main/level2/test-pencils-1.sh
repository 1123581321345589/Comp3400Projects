#!/bin/sh
input_file="../data/pencils.png"
output_file="pencils.out.png"
goal_file="../data/pencils.out.png"
nthreads="1"

./level2 "$input_file" "$output_file" "$nthreads"
diff "$output_file" "$goal_file"
