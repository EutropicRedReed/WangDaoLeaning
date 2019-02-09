#include "func.h"

int main(int argc,char *argv[])
{
	args_check(argc,2);
	int fd=open(argv[1],O_RDWR);
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
	struct stat statbuf;
	fstat(fd,&statbuf);
	char *p=mmap(NULL,statbuf.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if((char*)-1==p)
	{
		perror("mmap");
		return -1;
	}
	lseek(fd,0,SEEK_SET);
	int ret=write(fd,"world",sizeof("world"));
	if(-1==ret)
	{
		perror("write");
		return -1;
	}
	ret=munmap(p,statbuf.st_size);
	if(-1==ret)
	{
		perror("munmap");
		return -1;
	}
	close(fd);
	return 0;
}
