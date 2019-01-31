#include "func.h"

int main()
{
	if(!fork())
	{
		printf("I am child,pid=%d,ppid=%d\n",getpid(),getppid());
		return 5;
	}else{
		printf("I am parent\n");
		pid_t pid;
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
}
