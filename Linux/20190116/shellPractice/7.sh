#!/bin/bash
echo "please input the first number:"
read a
echo "please input the the second number:"
read b
echo "please input your operator:"
read c
case $c in
"+")
	echo "the result of $a + $b is $(($a + $b))"
	;;
"-")
	echo "the result of $a - $b is $(($a - $b))"
	;;
"*")
	echo "the result of $a * $b is $(($a * $b))"
	;;
"/")
	echo "the result of $a / $b is $(($a / $b))"
	;;
*)
	echo "no true operator!"
	;;
esac
