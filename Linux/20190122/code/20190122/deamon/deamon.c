#include "func.h"

void Deamon()
{
	if(fork())
	{
		exit(0);
	}
	setsid();
	chdir("/");//为了磁盘挂载
	umask(0);
	int i=0;
	for(i=0;i<3;i++)
	{
		close(i);
	}
}
int main()
{
	Deamon();
	while(1);
}
