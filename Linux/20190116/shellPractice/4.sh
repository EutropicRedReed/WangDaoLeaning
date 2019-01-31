#!/bin/bash

#test $(($iYear % 400)) -eq 0 -o $(($iYear % 4)) -eq 0 -a $(($iYear % 100)) -ne 0
a="abc"
test $a=="abc"
echo $?
test $a == "afd"
echo $?
	
test $a=="afd"
echo $?

echo '-----'
a=5
b=6
result=$[a+b]
echo "result: $result"
