#include "func.h"

int main(int argc,char *argv[])
{
	args_check(argc,3);
	int fdw=open(argv[1],O_WRONLY);
	if(-1==fdw)
	{
		perror("fdw open");
		return -1;
	}
	int fdr=open(argv[2],O_RDONLY);
	if(-1==fdr)
	{
		perror("fdr open");
		return -1;
	}
	printf("i am chat2\n");
	fd_set rdset;
	int ret;
	char buf[128]={0};
	struct timeval tv;
	while(1)
	{
		FD_ZERO(&rdset);
		FD_SET(0,&rdset);
		FD_SET(fdr,&rdset);
		tv.tv_sec=2;
		ret=select(fdr+1,&rdset,NULL,NULL,&tv);
		if(ret>0)
		{
			if(FD_ISSET(STDIN_FILENO,&rdset))
			{
				memset(buf,0,sizeof(buf));
				read(STDIN_FILENO,buf,sizeof(buf)-1);
				write(fdw,buf,strlen(buf)-1);
			}
			if(FD_ISSET(fdr,&rdset))
			{
				memset(buf,0,sizeof(buf));
				ret=read(fdr,buf,sizeof(buf));
				if(0==ret)
				{
					puts("over");
					break;
				}
				strcat(buf,"\t---from chat1.");
				printf("%s\n",buf);
			}
		}
	}
	close(fdr);
	close(fdw);
	return 0;
}
