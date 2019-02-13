#include "factory.h"
int my_chdir(const char *addr,int fd)
{
    Vir_File_Sys vfs[VIR_FILE_SYS_MAX_NUM_];
    Tmp_Fd_Acci tfa;
    Acc_Inf ai;
    tfa.fd=fd;
    querymysqltablethree(&tfa);
    strcpy(ai.name,tfa.name);
    querymysql(&ai);
    vfs[0].belong=ai.PasswdId;
    vfs[0].cur_cat='5';
    vfs[0].type='d';
    querymysqltabletwo(vfs);

    int i,j=0,k=0;
    char *catbuf[VIR_FILE_SYS_MAX_DEEP_];
    memset(catbuf,0,VIR_FILE_SYS_MAX_DEEP_*sizeof(int *));
    for(i=0;i<VIR_FILE_SYS_MAX_DEEP_;i++)
    {
        if(vfs[i].belong==ai.PasswdId)
        {
            if('1'==vfs[i].cur_cat)
            {
                j=i;    // j is current level of catalog
                catbuf[k++]=vfs[i].name;    // k is position
                updatemysqltabletwo(&vfs);
                break;
            }
        }
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

    Vir_File_Sys vfs[VIR_FILE_SYS_MAX_DEEP_];
    Tmp_Fd_Acci tfa;
    Acc_Inf ai;
    tfa.fd=fd;
    querymysqltablethree(&tfa);
    strcpy(ai.name,tfa.name);
    querymysql(&ai);
    vfs[0].belong=ai.PasswdId;
    vfs[0].cur_cat='5';
    vfs[0].type='d';
    querymysqltabletwo(vfs);
    int i,j=0,k=0;
    char *catbuf[VIR_FILE_SYS_MAX_DEEP_];
    memset(catbuf,0,VIR_FILE_SYS_MAX_DEEP_*sizeof(int *));
    for(i=0;i<VIR_FILE_SYS_MAX_DEEP_;i++)
    {
        if(vfs[i].belong==ai.PasswdId)
        {
            if('1'==vfs[i].cur_cat)
            {
                j=i;    // j is current level of catalog
                catbuf[k++]=vfs[i].name;    // k is position
                break;
            }
        }
    }
    --j;    
    while(j)
    {
        for(i=0;i<VIR_FILE_SYS_MAX_DEEP_;i++)
        {
            if(vfs[i].type=='d'&&vfs[i].procode==j)
            {
                catbuf[k++]=vfs[i].name;
                j--;
            }
        }
    }
    --k;
    //strcpy(buf,"/");    // root catalog
    for(i=k;i>=0;i--) // reverse
    {
        sprintf(buf,"%s/%s",buf,catbuf[i]);
    }
    sprintf(buf,"%s\n",buf);

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
            typebuf[0]='l'; // link file type
        if(S_ISBLK(statbuf.st_mode))
            typebuf[0]='b'; // block file type
        if(S_ISCHR(statbuf.st_mode))
            typebuf[0]='c'; // character device file type
        if(S_ISDIR(statbuf.st_mode))
            typebuf[0]='d'; // catalog file type
        if(S_ISSOCK(statbuf.st_mode))
            typebuf[0]='s'; // socket file type
        if(S_ISFIFO(statbuf.st_mode))
            typebuf[0]='p'; // pipe file type
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


