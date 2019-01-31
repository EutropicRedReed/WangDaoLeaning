#include "func.h"

int main(int argc,char *argv[])
{
	DIR *p;
	if(1==argc)
	{
		p=opendir(".");
	}
	else
	{
		p=opendir(argv[1]);
		chdir(argv[1]);
	}
	if(NULL==p)
	{
		perror("opendir");
		return -1;
	}
	struct stat statbuf;
	struct dirent *pdir;
	while((pdir=readdir(p))!=NULL)
	{
		int ret;
		ret=stat(pdir->d_name,&statbuf);
		if(-1==ret)
		{
			perror("stat");
			return -1;
		}
		int i=0,tmp=statbuf.st_mode;
		char typebuf[11]={"-rwxrwxrwx"};
		for(i=0;i<9;i++)
		{
			if(tmp & 1)
			{
				tmp>>=1;
			}
			else
			{
				typebuf[9-i]='-';
				tmp>>=1;
			}
		}
		if(S_ISLNK(statbuf.st_mode))
			typebuf[0]='l';
		if(S_ISBLK(statbuf.st_mode))
			typebuf[0]='b';
		if(S_ISCHR(statbuf.st_mode))
			typebuf[0]='c';
		if(S_ISDIR(statbuf.st_mode))
			typebuf[0]='d';
		if(S_ISSOCK(statbuf.st_mode))
			typebuf[0]='s';
		if(S_ISFIFO(statbuf.st_mode))
			typebuf[0]='p';
		char timebuf[30]={0};
		strncat(timebuf,ctime(&statbuf.st_mtime)+4,12);
		printf("%s %2ld %s %s %5ld %s %-s\n",typebuf, \
				statbuf.st_nlink, \
				getpwuid(statbuf.st_uid)->pw_name, \
				getgrgid(statbuf.st_gid)->gr_name, \
				statbuf.st_size,timebuf,pdir->d_name);
	}
	chdir("-");
	closedir(p);
	return 0;
}
