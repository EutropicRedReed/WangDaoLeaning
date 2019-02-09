#!/bin/bash


mkdir ~/Linux/"+%Y%m%d"
scp -r $1 test@192.168.2.100:/wangao/C_C++方向/短期班/Linux/"+%Y%m%d"/code ~/Linux/"+%Y%m%d"/


myname=`date -d "0 week" +%Y%m%d`
if [ -f $myname ];then
	echo "dir has exist!"
	exit 1
else
	mkdir $myname
fi
cd $myname
