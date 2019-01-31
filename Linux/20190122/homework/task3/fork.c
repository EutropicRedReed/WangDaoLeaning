#include "func.h"

int main()
{
	pid_t pid=fork();
	if(!pid)
	{
		printf("child pid=%d\n",getpid());
		exit(7);
	}
	printf("parent pid=%d\n",getpid());
	int status;
	pid=wait(&status);
	if(WIFEXITED(status))
	{
		printf("child exit code=%d\n",WEXITSTATUS(status));
	}else{
		printf("child crash\n");
	}
	return 0;
}
