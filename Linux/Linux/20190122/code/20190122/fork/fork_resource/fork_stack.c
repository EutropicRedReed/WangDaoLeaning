#include "func.h"

int main()
{
	pid_t pid;
	int iNum=10;
	pid=fork();
	if(0==pid)
	{//这里是子进程的代码
		printf("I am child process,iNum=%d\n",iNum);
		iNum=5;
		printf("I am child process,iNum=%d,iNum_addr=%p\n",iNum,&iNum);
	}else{
	 //这里是父进程的代码
		printf("I am parent process,iNum=%d\n",iNum);
		sleep(1);
		printf("I am parent process,iNum=%d,iNum_addr=%p\n",iNum,&iNum);
		return 0;
	}
}
