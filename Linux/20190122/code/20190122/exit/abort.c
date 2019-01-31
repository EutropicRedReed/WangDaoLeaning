#include "func.h"

int print()
{
	printf("I am print\n");
}

int main()
{
	if(!fork())
	{
		printf("I am child process\n");
		print();
		abort();
		return 0;
	}else{
		pid_t pid;
		int status;
		pid=wait(&status);
		if(WIFEXITED(status))
		{
			printf("exit code=%d\n",WEXITSTATUS(status));
		}else{
			printf("child crash\n");
		}
		return 0;
	}
}
