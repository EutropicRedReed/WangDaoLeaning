#include "func.h"

int main(int argc,char *argv[])
{
	args_check(argc,3);
	char buff[]="helloworld";
	int fd1=open(argv[1],O_RDWR,0755);
	if(-1==fd1)
	{
		perror("open file1");
		return -1;
	}
	int fdout=dup2(fd1,STDOUT_FILENO); //stdout
	int ret=write(fdout,buff,5*sizeof(char));
	if(-1==ret)
	{
		perror("write stdout");
		return -1;
	}
	close(fd1);
	int fd2=open(argv[2],O_RDWR,0755);
	if(-1==fd2)
	{
		perror("open file2");
		return -1;
	}
	int fderr=dup2(fd2,STDERR_FILENO); //stderr
	ret=write(fderr,&buff[5],5*sizeof(char));
	if(-1==ret)
	{
		perror("write stderror");
		return -1;
	}
    perror("world\n");
	close(fdout);
	close(fderr);
	return 0;
}
