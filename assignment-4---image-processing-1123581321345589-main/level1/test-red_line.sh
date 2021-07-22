#!/bin/sh
input_file="../data/red_line.png"
output_file="red_line.out.png"
goal_file="../data/red_line.out.png"

./level1 "$input_file" "$output_file"
diff "$output_file" "$goal_file"
