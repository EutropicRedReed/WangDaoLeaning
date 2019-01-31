#include "func.h"

int main()
{
	pid_t pid;
	pid=fork();
	if(0==pid)
	{//这里是子进程的代码
		printf("I am child process\n");
	}else{
	 //这里是父进程的代码
		printf("I am parent process\n");
		sleep(1);
		return 0;
	}
}
