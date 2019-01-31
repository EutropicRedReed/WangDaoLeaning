#include "func.h"

int main()
{
	if(!fork())
	{
		printf("I am child,pid=%d,ppid=%d\n",getpid(),getppid());
	}else{
		printf("I am parent\n");
		while(1);
		return 0;
	}
}
