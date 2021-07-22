#!/bin/sh
input_file="../data/red_box.png"
output_file="red_box.out.png"
goal_file="../data/red_box.out.png"
nthreads=4

./level2 "$input_file" "$output_file" "$nthreads"
diff "$output_file" "$goal_file"
