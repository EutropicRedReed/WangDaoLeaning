#include "func.h"

int main(int argc,char** argv)
{
	args_check(argc,2);
	int fd=open(argv[1],O_RDWR);
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
	printf("\n");
	int fd1=dup2(fd,1);
	printf("fd1=%d\n",fd1);//到文件里了
	close(fd);
	printf("you can't see me\n");
	return 0;
}
