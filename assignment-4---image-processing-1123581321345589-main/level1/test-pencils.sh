#!/bin/sh
input_file="../data/pencils.png"
output_file="pencils.out.png"
goal_file="../data/pencils.out.png"

./level1 "$input_file" "$output_file"
diff "$output_file" "$goal_file"
