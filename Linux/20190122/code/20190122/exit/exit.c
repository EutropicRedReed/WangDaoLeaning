#include "func.h"

int print()
{
	printf("I am print");
	exit(3);
}

int main()
{
	if(!fork())
	{
		printf("I am child process\n");
		print();
		return 0;
	}else{
		pid_t pid;
		int status;
		pid=wait(&status);
		if(WIFEXITED(status))
		{
			printf("exit code=%d\n",WEXITSTATUS(status));
		}
		return 0;
	}
}
