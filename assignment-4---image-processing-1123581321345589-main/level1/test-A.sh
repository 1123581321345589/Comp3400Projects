#!/bin/sh
input_file="../data/A.png"
output_file="A.out.png"
goal_file="../data/A.out.png"

./level1 "$input_file" "$output_file"
diff "$output_file" "$goal_file"
