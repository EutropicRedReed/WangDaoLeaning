#include <func.h>

int main()
{
	printf("I am print pid=%d,ppid=%d,uid=%d,sid=%d\n",getpid(),getppid(),getuid(),getsid(0));
	sleep(20);
	return 0;
}
