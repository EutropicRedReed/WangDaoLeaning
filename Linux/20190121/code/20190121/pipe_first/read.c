#include "func.h"

int main(int argc,char** argv)
{
	args_check(argc,2);
	int fdr=open(argv[1],O_RDONLY);
	if(-1==fdr)
	{
		perror("open");
		return -1;
	}
	printf("I am reader\n");
	char buf[10]={0};
	int ret;
	ret=read(fdr,buf,sizeof(buf));
	printf("ret=%d,buf=%s\n",ret,buf);
	return 0;
}
