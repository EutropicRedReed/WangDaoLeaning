#include "func.h"

int main()
{
	printf("uis=%d,gid=%d\n",getuid(),getgid());
	printf("euid=%d,egid=%d\n",geteuid(),getegid());
	FILE *fp=fopen("test.txt","ab+");
	if(NULL==fp)
	{
		perror("fopen");
		return -1;
	}
	char buf[128]={0};
	scanf("%s",buf);
	fputs(buf,fp);
	fclose(fp);
	return 0;
}
