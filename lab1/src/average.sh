#!/bin/sh

sum=0 
for arg in $*; do
  sum=$(($sum+arg))
done

sum=$(($sum / $#))

echo $sum