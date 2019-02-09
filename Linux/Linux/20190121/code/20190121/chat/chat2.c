#include "func.h"

int main(int argc,char** argv)
{
	args_check(argc,3);
	int fdw=open(argv[1],O_WRONLY);//以写的方式打开一号管道
	if(-1==fdw)
	{
		perror("open");
		return -1;
	}
	int fdr=open(argv[2],O_RDONLY);
	if(-1==fdr)
	{
		perror("open1");
		return -1;
	}
	printf("I am chat2\n");
	char buf[128]={0};
	int ret;
	fd_set rdset;//描述符监控的读集合
	while(1)
	{
		FD_ZERO(&rdset);
		FD_SET(0,&rdset);
		FD_SET(fdr,&rdset);
		ret=select(fdr+1,&rdset,NULL,NULL,NULL);
		if(ret>0)
		{
			if(FD_ISSET(STDIN_FILENO,&rdset))
			{
				memset(buf,0,sizeof(buf));
				ret=read(STDIN_FILENO,buf,sizeof(buf));//读取标准输入
				if(0==ret)
				{
					printf("this is end\n");
					break;
				}
				write(fdw,buf,strlen(buf)-1);//写端管道内
			}
			if(FD_ISSET(fdr,&rdset))
			{
				memset(buf,0,sizeof(buf));
				ret=read(fdr,buf,sizeof(buf));
				if(0==ret)//写端断开，读端read返回，得到0
				{
					printf("byebye\n");
					break;
				}
				printf("%s\n",buf);
			}
		}
	}
	close(fdr);
	close(fdw);
	return 0;
}
