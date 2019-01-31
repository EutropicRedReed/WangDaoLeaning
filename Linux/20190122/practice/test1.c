#include "func.h"

int main()
{
	int fd=open("a.txt",O_RDWR);
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
	char *p;
	struct stat buf;
	fstat(fd,&buf);
	p=mmap(NULL,buf.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if((char*)-1==p)
	{
		perror("mmap");
		return -1;
	}
	lseek(fd,0,SEEK_SET);
	int ret=write(fd,"hello\n",sizeof("hello\n"));
	if(-1==ret)
	{
		perror("write");
		return -1;
	}
	ret=munmap(p,buf.st_size);
	if(-1==ret)
	{
		perror("munmap");
		return -1;
	}
	close(fd);
}
