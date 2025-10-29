#!/bin/bash

echo -n "Enter number of terms: "
read n

num=1
echo -n "$num "

for ((i=1; i<=n; i++))
do
    if (( i % 2 == 0 )); then
        num=$((num - 1))
    else
        num=$((num + 2))
    fi
    echo -n "$num "
done

echo
