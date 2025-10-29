#!/bin/bash

echo -n "Enter the radius of the circle: "
read r

pi=3.14


area=$(echo "$pi * $r * $r" | bc -l)
circumference=$(echo "2 * $pi * $r" | bc -l)

echo "Area of circle = $area"
echo "Circumference of circle = $circumference"
