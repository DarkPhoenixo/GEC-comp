#!/bin/bash

count=0
year=2000

echo "First 10 leap years from 2000 are:"

while [ $count -lt 10 ]
do
    if [ $((year % 400)) -eq 0 ] || { [ $((year % 4)) -eq 0 ] && [ $((year % 100)) -ne 0 ]; }
    then
        echo $year
        count=$((count + 1))
    fi
    year=$((year + 1))
done
