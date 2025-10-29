#!/bin/bash

echo -n "Enter a number: "
read num

sum=0
temp=$num

while [ $temp -gt 0 ]
do
    digit=$((temp % 10))   
    if (( digit % 2 == 0 )); then
        sum=$((sum + digit))
    fi
    temp=$((temp / 10))
done

echo "Sum of even digits of $num = $sum"
