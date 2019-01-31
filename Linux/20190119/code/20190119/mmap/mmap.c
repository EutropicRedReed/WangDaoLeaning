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
	char *p;
	struct stat buf;
	fstat(fd,&buf);
	p=mmap(NULL,buf.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if((char*)-1==p)
	{
		perror("mmap");
		return -1;
	}
	strcpy(p,"HELLOWORLD");
	munmap(p,buf.st_size);
	close(fd);
	return 0;
}
