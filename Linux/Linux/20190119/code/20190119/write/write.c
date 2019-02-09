#include "func.h"

int main(int argc,char *argv[])
{
	args_check(argc,2);
	FILE *fp=fopen(argv[1],"rb+");
	if(NULL==fp)
	{
		perror("fopen");
		return -1;
	}
	int fd=fileno(fp);
	printf("fd=%d\n",fd);
	int arr[3]={1,2,3};
	write(fd,arr,sizeof(arr));
	return 0;
}
