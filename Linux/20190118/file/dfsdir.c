#include "func.h"

void printdir(char *pathname,char *dirname)
{
	char path[512]={0};
	DIR *pdir=opendir(pathname);
	if(NULL==pdir)
	{
		perror("opendir");
		return;
	}
	struct dirent *p;
	while((p=readdir(pdir))!=NULL)
	{
		if(!strcmp(p->d_name,".")||!strcmp(p->d_name,".."))
		{
			continue;
		}
		if(!strcmp(p->d_name,dirname))
		{
			printf("%s %s\n",pathname,p->d_name);
			return;
		}
		else if(p->d_type==4)
		{
			sprintf(path,"%s%s%s",pathname,"/",p->d_name);
			printdir(path,dirname);
		}
	}
	closedir(pdir);
}

int main(int argc,char *argv[])
{
	args_check(argc,3);
	printdir(argv[1],argv[2]);
	return 0;
}
