#include "func.h"

int main(int argc,char *argv[])
{
	args_check(argc,3);
	char buf[128]={0};
	int ret;
	int fd1=open(argv[1],O_RDONLY);
	int fd2=open(argv[2],O_RDONLY);
	int fd3=open(argv[1],O_WRONLY);
	int fd4=open(argv[2],O_WRONLY);
	if((-1==fd1)||(-1==fd2)||(-1==fd3)||(-1==fd4))
	{
		perror("open");
		return -1;
	}

	fd_set fdrd,fdwr;

	int max1=fd1>fd2?fd1:fd2;
	int max2=fd3>fd4?fd3:fd4;
	int max=max1>max2?max1:max2;

	//struct timeval tv;

	while(1)
	{
		FD_ZERO(&fdrd);
		FD_ZERO(&fdwr);

		FD_SET(fd1,&fdrd);
		FD_SET(fd2,&fdrd);
		FD_SET(fd3,&fdwr);
		FD_SET(fd4,&fdwr);

		//tv.tv_sec=2;
		//tv.tv_usec=0;


		ret=select(max+1,&fdrd,&fdwr,NULL,NULL);
			if(ret>0)	
			{
				if(FD_ISSET(fd1,&fdrd))
				{
					memset(buf,0,sizeof(buf));
					ret=read(fd1,buf,sizeof(buf)-1);
					if(0==ret)
					{
						puts("over");
						break;
					}
					puts(buf);
					//sleep(1);
				}
				if(FD_ISSET(fd2,&fdrd))
				{
					memset(buf,0,sizeof(buf));
					ret=read(fd2,buf,sizeof(buf)-1);
					if(0==ret)
					{
						puts("over");
						break;
					}
					puts(buf);
					//sleep(1);
				}
				if(FD_ISSET(fd3,&fdwr))
				{
					memset(buf,0,sizeof(buf));
					ret=scanf("%s",buf);
					if(0==ret)
					{
						perror("scanf");
						return -1;
					}
					write(fd3,buf,sizeof(buf)-1);
					//sleep(2);
				}
				if(FD_ISSET(fd4,&fdwr))
				{
					memset(buf,0,sizeof(buf));
					ret=scanf("%s",buf);
					if(0==ret)
					{
						perror("scanf");
						return -1;
					}
					write(fd4,buf,sizeof(buf)-1);
					//sleep(2);
				}
			}
	}
	close(fd1);
	close(fd2);
	close(fd3);
	close(fd4);
	return 0;
}
