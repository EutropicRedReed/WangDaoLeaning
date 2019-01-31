#include "func.h"

int main(int argc,char *argv[])
{
	//args_check(argc,2);
	DIR *pdir;
	if(1==argc)
		pdir=opendir(".");
	else
		pdir=opendir(argv[1]);
	if(NULL==pdir)
	{
		perror("opendir");
		return -1;
	}
	struct dirent *pdirinf=NULL;
	struct stat pdirstat; //如果定义为指针类型，则需要calloc一个空间。这种为使用栈空间的形式，不需要申请堆空间。
	int ret;
	chdir(argv[1]);  //改变目录，可以使stat更新所需要目录的信息。
	while((pdirinf=readdir(pdir))!=NULL)
	{
		ret=stat(pdirinf->d_name,&pdirstat);
		if(-1==ret)
		{
			perror("stat");
			return -1;
		}
		printf("%-15s %-8d\n",pdirinf->d_name,pdirstat.st_mode);
	}
	chdir("-");
	closedir(pdir);
	return 0;
}
