#include <func.h>

int main()
{
	FILE *fp;
	fp=popen("./print","r");
	if(NULL==fp)
	{
		perror("fopen");
		return -1;
	}
	char buf[128]={0};
	fgets(buf,sizeof(buf),fp);
	printf("%s,pid=%d,ppid=%d,uid=%d,sid=%d\n",buf,getpid(),getppid(),getuid(),getsid(0));
	pclose(fp);
	return 0;
}
