#include "func.h"

int main()
{
	pid_t pid;
	pid=fork();
	if(0==pid)
	{
		printf("child\n");
	}
	else{
		printf("parent\n");
		sleep(20);
	}
	return 0;
}
