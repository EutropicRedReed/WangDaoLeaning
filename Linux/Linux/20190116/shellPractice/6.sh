#!/bin/bash

if [ -f $1 -a -r $1 -a -w $1 ]
then
	cat $1
elif [ -d $1 ]
then
	cd $1
	if [ -e Ls.sh ]
	then 
		chmod 755 Ls.sh
		./Ls.sh
	eLse
		touch Ls.sh
		echo "#!/bin/bash">>Ls.sh
		echo "ls -li /etc |xargs >etc.list">>Ls.sh
		chmod 755 Ls.sh
		./Ls.sh
	fi
fi

