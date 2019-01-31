#include "func.h"
//堆空间
int main()
{
	pid_t pid;
	char *p=(char*)malloc(20);
	strcpy(p,"hello");
	pid=fork();
	if(0==pid)
	{//这里是子进程的代码
		printf("I am child process,%s\n",p);
		strcpy(p,"world");
		printf("I am child process,%s,%p\n",p,p);
	}else{
	 //这里是父进程的代码
		printf("I am parent process,%s\n",p);
		sleep(1);
		printf("I am parent process,%s,%p\n",p,p);
		return 0;
	}
}
