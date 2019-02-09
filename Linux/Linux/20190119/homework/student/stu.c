#include "func.h"

typedef struct {
	int num;
	char name[20];
	float score;
}student;

int main(int argc,char *argv[])
{
	args_check(argc,2);
	student stu[3];
	int i;
	for(i=0;i<3;i++)
	{
		scanf("%d%s%f",&stu[i].num,stu[i].name,&stu[i].score);
	}
	int fd=open(argv[1],O_RDWR|O_TRUNC,0755);
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
	int ret;
	for(i=0;i<3;i++)
	{
		ret=write(fd,&stu[i],sizeof(student));
		if(-1==ret)
		{
			perror("write");
			return -1;
		}
	}
	printf("---------------------------\n");
	lseek(fd,0,SEEK_SET);
	struct stat statbuf;
	fstat(fd,&statbuf);
	student buff;
	for(i=0;i<3;i++)
	{
		ret=read(fd,&buff,statbuf.st_size);
		if(-1==ret)
		{
			perror("read");
			return -1;
		}
		printf("%d %s %5.2f\n",buff.num,buff.name,buff.score);
	}
	close(fd);
	return 0;
}