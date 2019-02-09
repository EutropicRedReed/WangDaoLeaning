#include "func.h"
int g_iNum=10;
int main()
{
	pid_t pid;
	pid=fork();
	if(0==pid)
	{//这里是子进程的代码
		printf("I am child process,g_iNum=%d\n",g_iNum);
		g_iNum=5;
		printf("I am child process,g_iNum=%d,g_iNum_addr=%p\n",g_iNum,&g_iNum);
	}else{
	 //这里是父进程的代码
		printf("I am parent process,g_iNum=%d\n",g_iNum);
		sleep(1);
		printf("I am parent process,g_iNum=%d,g_iNum_addr=%p\n",g_iNum,&g_iNum);
		return 0;
	}
}
