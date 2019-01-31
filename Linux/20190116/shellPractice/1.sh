#!/bin/bash

#this is my first shell project
dir = "/etc/profile"
#cp -rf /etc/*.conf ${dir}
ls -l /etc/* |grep ^d |wc -l >ectdir.txt

