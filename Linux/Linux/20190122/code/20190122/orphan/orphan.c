#include "func.h"

int main()
{
	if(!fork())
	{
		printf("I am child,pid=%d,ppid=%d\n",getpid(),getppid());
		while(1);
	}else{
		printf("I am parent\n");
		return 0;
	}
}
