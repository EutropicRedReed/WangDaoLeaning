#include "func.h"

int main()
{
	pid_t pid=fork();
	if(!pid)
	{
		printf("child pid=%d\n",getpid());
		exit(5);
	}
	printf("parent pid=%d\n",getpid());
	sleep(15);
	return 0;
}
