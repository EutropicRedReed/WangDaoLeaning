#!/bin/bash

loopcount=0
result=0
while [ $loopcount -lt 100 ]
do
	loopcount=$(($loopcount+1))
	result=$(($loopcount+$result))
done
echo "This result of '1+2+3+...+100' is $result"
