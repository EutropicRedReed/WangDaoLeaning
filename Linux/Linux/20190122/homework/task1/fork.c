#include "func.h"

int main()
{
	pid_t pid=fork();
	if(!pid)
	{
		printf("child pid=%d\n",getpid());
		while(1);
		return 0;
	}
	printf("parent pid=%d\n",getpid());
	while(1);
	return 0;
}
