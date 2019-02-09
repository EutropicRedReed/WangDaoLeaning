#include <func.h>

int main()
{
	int fds[2];//用来存放无名管道的读端和写端
	pipe(fds);
	if(!fork())
	{
		close(fds[1]);//关闭写端
		char buf[128]={0};
		read(fds[0],buf,sizeof(buf));
		printf("%s\n",buf);
	}else{
		close(fds[0]);//关闭读端
		write(fds[1],"hello",5);
		wait(NULL);
		return 0;
	}
}

