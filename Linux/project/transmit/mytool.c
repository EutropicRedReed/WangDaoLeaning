#include "head.h"
#include "tranfile.h"
#define MAX_BUF_SIZE 4096
int my_chdir(const char *addr,int fd)
{
    if(-1==chdir(addr))
    {
        perror("chdir");
        return -1;
    }
    int datalen;
    char buf[MAX_BUF_SIZE]={0};
	sprintf(buf,"currnt directory: %s\n",getcwd(NULL,0));
    datalen=strlen(buf);
    send_n(fd,&datalen,sizeof(int));
    send_n(fd,buf,datalen);
    return 0;
}

void my_pwd(int fd)
{
    int datalen;
    char buf[MAX_BUF_SIZE]={0};
    sprintf(buf,"currnt directory: %s\n",getcwd(NULL,0));
    datalen=strlen(buf);
    send_n(fd,&datalen,sizeof(int));
    send_n(fd,buf,datalen);
}

int my_ls(const char *addr,int fd)
{
    DIR *p;
    int datalen;
    char buf[MAX_BUF_SIZE]={0};
    char temp[MAX_BUF_SIZE]={0};
    p=opendir(addr);
    chdir(addr);
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
        //printf hide catalog
        if(!strncmp(pdir->d_name,".",1))
            continue;
        memset(temp,0,sizeof(temp));
        sprintf(temp,"%s %-2ld %-7s %-7s %5ld %s %-s\n",typebuf, \
                statbuf.st_nlink, \
                getpwuid(statbuf.st_uid)->pw_name, \
                getgrgid(statbuf.st_gid)->gr_name, \
                statbuf.st_size,timebuf,pdir->d_name);
        strcat(buf,temp);
    }
    datalen=strlen(buf);
    send_n(fd,&datalen,sizeof(int));
    send_n(fd,buf,datalen);
    chdir("-");
    closedir(p);
    return 0;
}


int my_rm(const char *pathname,int fd)
{
    int datalen;
    char buf[MAX_BUF_SIZE]={0};
    if(-1==unlink(pathname))
    {
        perror("delete failed");
        return -1;
    }
    sprintf(buf,"delete file success\n");
    datalen=strlen(buf);
    send_n(fd,&datalen,sizeof(int));
    send_n(fd,buf,datalen);
    return 0;
}


