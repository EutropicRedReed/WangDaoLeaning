#include <func.h>

int main()
{
	int pfd[2]={0};
	pipe(pfd);
	char buf[128]={0};
	if(!fork())
	{
		close(pfd[0]);
		write(pfd[1],"Hello",6);
		close(pfd[1]);
		exit(0);
	}
	else{
		close(pfd[1]);
		wait(NULL);
		int ret=read(pfd[0],buf,sizeof(buf));
		if(0==ret)
		{
			return 0;
		}
		puts(buf);
		close(pfd[0]);
		exit(0);
	}
	return 0;
}
