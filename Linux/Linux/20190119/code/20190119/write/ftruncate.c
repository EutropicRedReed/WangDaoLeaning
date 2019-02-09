#include "func.h"

void change(int fd)
{
	ftruncate(fd,10);
}


int main(int argc,char *argv[])
{
	args_check(argc,2);
	int fd=open(argv[1],O_RDWR);
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
	change(fd);
	close(fd);
	return 0;
}
