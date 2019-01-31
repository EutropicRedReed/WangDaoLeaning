#include "func.h"

int main(int argc,char** argv)
{
	args_check(argc,2);
	int fdw=open(argv[1],O_WRONLY);
	if(-1==fdw)
	{
		perror("open");
		return -1;
	}
	printf("I am writer\n");
	char buf[10]="hello";
	write(fdw,buf,strlen(buf));
	return 0;
}
