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
	int fd1=dup(fd);
	printf("fd1=%d\n",fd1);
	close(fd);
	char buf[128]={0};
	int ret;
	ret=read(fd1,buf,sizeof(buf));
	if(-1==ret)
	{
		perror("read");
		return -1;
	}
	printf("ret=%d,buf=%s\n",ret,buf);
	return 0;
}
