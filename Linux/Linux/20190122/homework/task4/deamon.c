#include "func.h"

int main()
{
	pid_t pid=fork();
	if(!pid)
	{
		printf("child pid=%d\n",getpid());
		setsid();
		chdir("/");
		umask(0);
		int i;
		for(i=0;i<3;i++)
		{
			close(i);
		}
	}else{
	printf("parent pid=%d\n",getpid());
	exit(0);
	}
	int fd=open("tmp/log",O_RDWR);
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
	lseek(fd,0,SEEK_SET);
	while(1)
	{
		sleep(1);
		int ret=write(fd,"I have sleep 1s\n",sizeof("I have sleep 1s"));
		if(-1==ret)
		{
			perror("write");
			return -1;
		}
	}
	return 0;
}
