#!/bin/bash

function add()
{
	if [ $(($1+$2)) -ge 255 ]
		then
			echo $(($1+$2))
		else
			echo $(($1+$2))
#return $(($1+$2))
	fi		
}
read a 
read b
add a b
#if [ $? -eq 0 ]
#then 
#	echo 
#else
#	echo $?
#fi

#function add()
#{
#	return $(($1+$2))
#}
#read a
#read b
#add a b
#echo $?
