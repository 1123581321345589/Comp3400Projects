#!/bin/sh
input_file="../data/red_box.png"
output_file="red_box.out.png"
goal_file="../data/red_box.out.png"

./level1 "$input_file" "$output_file"
diff "$output_file" "$goal_file"
