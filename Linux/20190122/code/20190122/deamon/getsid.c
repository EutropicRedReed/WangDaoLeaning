#include "func.h"

int main()
{
	pid_t pid=fork();
	if(!pid)
	{
		printf("child pid=%d,ppid=%d,pgid=%d,sid=%d\n",getpid(),getppid(),getpgid(0),getsid(0));
		while(1);
		return 0;
	}else{
		printf("parent pid=%d,mychildpid=%d,pgid=%d,sid=%d\n",getpid(),pid,getpgid(0),getsid(0));
		while(1);
		return 0;
	}
}

