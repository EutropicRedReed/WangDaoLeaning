#include <func.h>

int main()
{
	FILE *fp;
	fp=popen("./add","w");
	if(NULL==fp)
	{
		perror("fopen");
		return -1;
	}
	char buf[128]="3 4";
	fputs(buf,fp);
	pclose(fp);
	return 0;
}
