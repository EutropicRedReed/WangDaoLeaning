#include "factory.h"
int my_chdir(const char *addr,int fd)
{
    if(!strcmp(addr,"."))   // case 1: cd . 
    {
        my_pwd(fd);   
        return 0;
    }
    if(!strcmp(addr,"..")||!strcmp(addr,"../"))  // case 2: cd ..
    {
        int datalen;
        char buf[MAX_BUF_SIZE]={0};

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
                    vfs[i].cur_cat='0';
                    updatemysqltabletwo(&vfs[i]);
                    break;
                }
            }
        }
        --j;
        int flag=1;
        while(j>=0)
        {
            for(i=0;i<VIR_FILE_SYS_MAX_DEEP_;i++)
            {
                if((vfs[i].type=='d')&&(vfs[i].procode==j)&&(flag==1))
                {
                    vfs[i].cur_cat='1';
                    updatemysqltabletwo(&vfs[i]);
                    catbuf[k++]=vfs[i].name;
                    flag=0;
                    j--;
                    if(j<=0)
                    {
                        j--;
                        break;
                    }
                }
                if((vfs[i].type=='d')&&vfs[i].procode==j)
                {
                    catbuf[k++]=vfs[i].name;
                    if(j==0)
                    {
                        break;
                    } 
                    j--;
                    if(j<=0)
                    {
                        break;
                    }
                }
            }
            j--;
        }
        --k;
        //for(i=0;i<k;i++)
        //{
        //    printf("%s,%d,%d\n",catbuf[i],i,k);
        //}
        ////strcpy(buf,"/");    // root catalog
        //memset(buf,0,sizeof(buf));
        //for(i=k;i>=0;i--) // reverse
        //{
        //    sprintf(buf,"%s/%s",buf,catbuf[i]);
        //}
        //if((int)strlen(buf)<=1)
        //{
        //    strcpy(buf,"/      ");
        //}
        //strcat(buf,"\n");
    
        strcpy(buf,"success change\n");
        datalen=strlen(buf);
        send_n(fd,&datalen,sizeof(int));
        send_n(fd,buf,datalen);   
        return 0;
    }
    if(!strncmp(addr,"..",2)&&!strncmp(addr+2,"/",1))   // case 3: cd ../
    {
        int datalen;
        char buf[MAX_BUF_SIZE]={0};

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
        int level=0;
        char *catbuf[VIR_FILE_SYS_MAX_DEEP_];
        memset(catbuf,0,VIR_FILE_SYS_MAX_DEEP_*sizeof(int *));
        for(i=0;i<VIR_FILE_SYS_MAX_DEEP_;i++)
        {
            if(vfs[i].belong==ai.PasswdId)
            {
                if('1'==vfs[i].cur_cat)
                {
                    j=i;    
                    catbuf[k++]=vfs[i].name;    // k is position
                    vfs[i].cur_cat='0';
                    updatemysqltabletwo(vfs+i);
                    level=vfs[i].procode;   // set new temp seaerch root
                    break;
                }
            }
        }

        int count=0;
        int m=0;
        int lastflag=0;
        char namebuf[CAT_NAME_SIZE_]={0};
        while(addr[m]!=0)
        {
            if(addr[m]=='/')
            {
                count++;
                m++;
                lastflag=m;
                continue;
            }
            m++;
        }
        level =level-1+count;   // find target catalog level.
        strncpy(namebuf,&addr[lastflag+1],strlen(addr)-m);
//#ifdef DEBUG
        printf("%s\n",namebuf);
//#endif
        vfs[0].belong=ai.PasswdId;
        vfs[0].cur_cat='6';
        vfs[0].procode=level;
        memset(buf,0,sizeof(buf));
        querymysqltabletwo(vfs);
        for(i=0;i<VIR_FILE_SYS_MAX_DEEP_;i++)
        {
            if(!strcmp(vfs[i].name,namebuf))
            {
                vfs[i].cur_cat='1';
                updatemysqltabletwo(&vfs[i]);
                strcpy(buf,"success change\n");
                datalen=strlen(buf);
                send_n(fd,&datalen,sizeof(int));
                send_n(fd,buf,datalen);   
                return 0;
            }
        }
        vfs[j].cur_cat='1';
        updatemysqltabletwo(&vfs[j]);
        strcpy(buf,"please check catalog it not exist");
        datalen=strlen(buf);
        send_n(fd,&datalen,sizeof(int));
        send_n(fd,buf,datalen);
        return -1;
    }

    if((0!=strncmp(addr,"/",1))&&(0!=strncmp(addr,".",1)))  // relative path
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
        int level;
        char *catbuf[VIR_FILE_SYS_MAX_DEEP_];
        memset(catbuf,0,VIR_FILE_SYS_MAX_DEEP_*sizeof(int *));
        for(i=0;i<VIR_FILE_SYS_MAX_DEEP_;i++)
        {
            if(vfs[i].belong==ai.PasswdId)
            {
                if('1'==vfs[i].cur_cat)
                {
                    j=i;    // j is current vfs
                    catbuf[k++]=vfs[i].name;    // k is position
                    vfs[i].cur_cat='0';
                    updatemysqltabletwo(vfs+i);
                    level=vfs[i].procode;
                    break;
                }
            }
        }


        int count=0;
        int m=0;
        int lastflag=0;
        char namebuf[CAT_NAME_SIZE_]={0};
        while(addr[m]!=0)
        {
            if(addr[m]=='/')
            {
                count++;
                m++;
                lastflag=m;
                continue;
            }
            m++;
        }
        level=level+count;
        strncpy(namebuf,&addr[lastflag],strlen(addr)-lastflag);
        
        vfs[0].belong=ai.PasswdId;
        vfs[0].cur_cat='6';
        vfs[0].procode=level;
        printf("%d=level,count=%d\n",level,count);
        memset(buf,0,sizeof(buf));
        querymysqltabletwo(vfs);
        for(i=0;i<VIR_FILE_SYS_MAX_DEEP_;i++)
        {
            if((vfs[i].type=='d')&&!strcmp(vfs[i].name,namebuf))
            {
                vfs[i].cur_cat='1';
                updatemysqltabletwo(&vfs[i]);
                sprintf(buf,"success change\n");
                datalen=strlen(buf);
                send_n(fd,&datalen,sizeof(int));
                send_n(fd,buf,datalen);   
                return 0;
            }
        }
        vfs[j].cur_cat='1';
        updatemysqltabletwo(&vfs[j]);
        sprintf(buf,"%s%s\n",buf,"please check catalog it not exist");
        datalen=strlen(buf);
        send_n(fd,&datalen,sizeof(int));
        send_n(fd,buf,datalen);
        return -1;
    }

    if(!strncmp(addr,"/",1))    // case 4: absolute path
    {

        int count=0;
        int m=0;
        int lastflag=0;
        char namebuf[CAT_NAME_SIZE_]={0};
        while(addr[m]!=0)
        {
            if(addr[m]=='/')
            {
                count++;
                lastflag=m;
                m++;
                continue;
            }
            m++;
        }
        strncpy(namebuf,&addr[lastflag+1],strlen(addr)-lastflag);
//#ifdef DEBUG
        printf("%s\n",namebuf);
//#endif

        Vir_File_Sys vfs[VIR_FILE_SYS_MAX_NUM_];
        Tmp_Fd_Acci tfa;
        Acc_Inf ai;
        tfa.fd=fd;
        int datalen;
        char buf[MAX_BUF_SIZE]={0};
        memset(buf,0,sizeof(buf));
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
                    vfs[i].cur_cat='0';
                    updatemysqltabletwo(vfs+i);
                    catbuf[k++]=vfs[i].name;    // record file name
                    break;
                }
            }
        }
        --j;

        vfs[0].belong=ai.PasswdId;
        vfs[0].cur_cat='6';
        vfs[0].procode=count;
        memset(buf,0,sizeof(buf));
        querymysqltabletwo(vfs);
        for(i=0;i<VIR_FILE_SYS_MAX_DEEP_;i++)
        {
            if(!strcmp(vfs[i].name,namebuf))
            {
                vfs[i].cur_cat='1';
                updatemysqltabletwo(&vfs[i]);
                strcpy(buf,"success change\n");
                datalen=strlen(buf);
                send_n(fd,&datalen,sizeof(int));
                send_n(fd,buf,datalen);   
                return 0;
            }
        }
        strcpy(buf,"please check catalog it not exist");
        datalen=strlen(buf);
        send_n(fd,&datalen,sizeof(int));
        send_n(fd,buf,datalen);
        return -1;
    }
    return 0;
}

void my_pwd(int fd)
{
    int datalen;
    char buf[MAX_BUF_SIZE]={0};

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
    for(i=0;i<VIR_FILE_SYS_MAX_NUM_;i++)   // == i<VIR_FILE_SYS_MAX_NUM_
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
    while(j>=0)
    {
        for(i=0;i<VIR_FILE_SYS_MAX_NUM_;i++)
        {
            if(vfs[i].type=='d'&&vfs[i].procode==j)
            {
                catbuf[k++]=vfs[i].name;
                j--;
                if(0==j)
                {
                    break;
                }else if(j<0){
                    break;
                }
            }
        }
    }
    
    --k;
    //strcpy(buf,"/");    // root catalog
    for(i=k-1;i>=0;i--) // reverse
    {
        sprintf(buf,"%s/%s",buf,catbuf[i]);
    }
    if((int)strlen(buf)<1)
    {
        strcpy(buf,"/      ");
    }
    strcat(buf,"\n");
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


