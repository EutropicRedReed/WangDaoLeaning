#include "func.h"

int main()
{
	pid_t pid=fork();
	if(!pid)
	{
		printf("I am child,pid=%d,ppid=%d\n",getpid(),getppid());
		sleep(5);
		return 5;
	}else{
		printf("I am parent\n");
		int status=0;
		int ret;
		ret=waitpid(pid,&status,WNOHANG);
		if(ret>0)
		{
			if(WIFEXITED(status))
			{
				printf("child exit code=%d\n",WEXITSTATUS(status));
			}else{
				printf("child crash\n");
			}
		}
		printf("ret=%d\n",ret);
		return 0;
	}
}
