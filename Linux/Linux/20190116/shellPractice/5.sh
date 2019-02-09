#!/bin/bash

a=(2 5 7 10)
	echo ${a[2]}
	echo ${#a[*]}
	echo ${a[@]:2}
	echo ${a[@]:1:2}

a=(3 10 6 5 9 2 8 1 4 7)
x=0
#while [ $x -lt ${#a[*]} ]
#do 
#	echo ${a[$x]}
#	x=$(($x + 1))
#done

while (( i<10 ))
do 
	echo ${a[i]}
	i=$(($i +1))
done
