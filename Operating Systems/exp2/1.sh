#!/bin/bash

echo -n "Enter a number: "
read num

digits=($(echo "$num" | grep -o . | sort -n | uniq))

count=${#digits[@]}

if [ $count -lt 2 ]; then
  echo "Not enough unique digits to find second largest and second smallest."
  exit 1
fi

second_smallest=${digits[1]}
second_largest=${digits[$((count-2))]}

sum=$((second_smallest + second_largest))

echo "Second smallest digit: $second_smallest"
echo "Second largest digit: $second_largest"
echo "Sum: $sum"
