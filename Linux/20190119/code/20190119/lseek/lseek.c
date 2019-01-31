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
	int ret=lseek(fd,1000,SEEK_SET);
	printf("ret=%d\n",ret);
	write(fd,"1",1);
	close(fd);
	return 0;
}
