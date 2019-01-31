#include "func.h"

int main()
{
	pid_t pid;
	int fd=open("file",O_RDWR);
	pid=fork();
	if(0==pid)
	{//这里是子进程的代码
		printf("I am child process\n");
		lseek(fd,5,SEEK_SET);
	}else{
	 //这里是父进程的代码
		printf("I am parent process\n");
		sleep(1);
		char buf[128]={0};
		read(fd,buf,sizeof(buf));
		printf("I am parent process,%s\n",buf);
		return 0;
	}
}
