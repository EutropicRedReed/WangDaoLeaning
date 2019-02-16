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
        int datalen,count=0,i=0,code=0;
        char buf[MAX_BUF_SIZE]={0};
        char catbuf[VIR_FILE_SYS_MAX_DEEP_][VIR_FILE_SYS_MAX_DEEP_];

        Vir_File_Sys vfs;
        Acc_Inf ai;
        Tmp_Fd_Acci tfa;
        tfa.fd=fd;
        querymysqltablethree(&tfa);
        strcpy(ai.name,tfa.name);
        querymysqltableone(&ai);
        vfs.belong=ai.PasswdId;
        vfs.cur_cat='1';
        querymysqltabletwo(&vfs);   // current catalog
        code=vfs.code;
        do{
            strcpy(catbuf[count++],vfs.name);
            vfs.code=vfs.procode;
            vfs.cur_cat='4';
            querymysqltabletwo(&vfs);
        }while(vfs.procode);    // belong + code(previous procode) mode
        count--;
        vfs.code=code;
        vfs.cur_cat='4';
        querymysqltabletwo(&vfs);
        if(0==vfs.procode) // root catalog
        {
            memset(buf,0,sizeof(buf));
            strcpy(buf,"/\n");
            datalen=strlen(buf);
            send_n(fd,&datalen,sizeof(int));
            send_n(fd,buf,datalen);
            return 0;
        }
        vfs.cur_cat='0';
        updatemysqltabletwo(&vfs);  // cancel current catalog symbol
        vfs.code=vfs.procode;   // get upper catalog code
        vfs.cur_cat='4';    // shift belong + code(previous procode) query mode.
        querymysqltabletwo(&vfs);   
        vfs.cur_cat='1';    // upper catalog set current catalog symbol.
        updatemysqltabletwo(&vfs);
        if(count>=0&&vfs.code!=0)
        {
            for(i=count;i>0;i--)
            {
                sprintf(buf,"%s/%s",buf,catbuf[i]);
            }
            strcat(buf,"\n");
            datalen=strlen(buf);
            send_n(fd,&datalen,sizeof(int));
            send_n(fd,buf,datalen);
            return 0;
        }else{
            vfs.code=code;
            vfs.cur_cat='1';
            updatemysqltabletwo(&vfs);
            return -1;
        }
        return 0;
    }

    if((0!=strncmp(addr,"/",1))&&(0!=strncmp(addr,".",1)))  // relative path
    {
        int datalen,code=0,i=0,j=0,k=0,flag=0,aflag=0;
        char buf[MAX_BUF_SIZE]={0};
        char temp[MAX_BUF_SIZE]={0};
        char catbuf[VIR_FILE_SYS_MAX_DEEP_][VIR_FILE_SYS_MAX_NUM_];

        Vir_File_Sys vfs[VIR_FILE_SYS_MAX_NUM_];
        Tmp_Fd_Acci tfa;
        Acc_Inf ai;
        tfa.fd=fd;
        querymysqltablethree(&tfa);
        strcpy(ai.name,tfa.name);
        querymysqltableone(&ai);
        vfs[0].belong=ai.PasswdId;
        vfs[0].cur_cat='1';
        querymysqltabletwo(&vfs[0]);
        code=vfs[0].code;

        while (addr[i] != 0)
        {
            if (addr[i] == '/')
            {
                i++;
            }
            while (addr[i] != '/'&&addr[i] != 0)
            {
                temp[k++] = addr[i++];
            }
            temp[k] = 0;
            strcpy(catbuf[j++],temp);
            memset(temp,0,sizeof(temp));
            k = 0;
        }

        for(i=0;i<j;i++)
            printf("%s\n",catbuf[i]);

        vfs[0].procode=code;
        vfs[0].cur_cat='6';
        querymysqltabletwo(vfs);
        k=0;
        for(i=0;i<j+1;i++)
        {
            while(vfs[k].belong>0&&vfs[k].type=='d')
            {
                if(!strcmp(vfs[k].name,catbuf[i]))
                {
                    flag=1;
                    if(i==j-1)
                    {
                        aflag=1;
                        vfs[k].cur_cat='1';
                        updatemysqltabletwo(&vfs[k]);
                        break;
                    }
                    vfs[0].procode=vfs[0].code;
                    vfs[0].cur_cat='6';
                    querymysqltabletwo(vfs);
                    break;
                }
                k++;
            }
            if(flag==0||aflag==1)
            {
                break;
            }
            flag=0;
        }
        if(aflag==1)
        {
            vfs[0].code=code;
            vfs[0].cur_cat='4';
            querymysqltabletwo(&vfs[0]);
            vfs[0].cur_cat='0';
            updatemysqltabletwo(&vfs[0]);
            strcpy(buf,"success change\n");
            datalen=strlen(buf);
            send_n(fd,&datalen,sizeof(int));
            send_n(fd,buf,datalen);
            return 0;
        }

       // strcpy(buf,"please check pathname\n");
       // datalen=strlen(buf);
       // send_n(fd,&datalen,sizeof(int));
       // send_n(fd,buf,datalen);
        return -1;
    }

    if(!strncmp(addr,"/",1))    // case 4: absolute path
    {
        int datalen,code=0,i=0,j=0,k=0,flag=0,aflag=0;
        char buf[MAX_BUF_SIZE]={0};
        char temp[MAX_BUF_SIZE]={0};
        char catbuf[VIR_FILE_SYS_MAX_DEEP_][VIR_FILE_SYS_MAX_NUM_];

        Vir_File_Sys vfs[VIR_FILE_SYS_MAX_NUM_];
        Tmp_Fd_Acci tfa;
        Acc_Inf ai;
        tfa.fd=fd;
        querymysqltablethree(&tfa);
        strcpy(ai.name,tfa.name);
        querymysqltableone(&ai);
        vfs[0].belong=ai.PasswdId;
        vfs[0].cur_cat='1';
        querymysqltabletwo(&vfs[0]);
        code=vfs[0].code;
        i=1;
        while (addr[i] != 0)
        {
            if (addr[i] == '/')
            {
                i++;
            }
            while (addr[i] != '/'&&addr[i] != 0)
            {
                temp[k++] = addr[i++];
            }
            temp[k] = 0;
            strcpy(catbuf[j++],temp);
            memset(temp,0,sizeof(temp));
            k = 0;
        }
        for(i=0;i<j;i++)
            printf("%s\n",catbuf[i]);

        vfs[0].cur_cat='6';
        vfs[0].procode=0;
        querymysqltabletwo(&vfs[0]);
        vfs[0].procode=vfs[0].code;
        vfs[0].cur_cat='6';
        querymysqltabletwo(vfs);
        k=0;
        for(i=0;i<j;i++)
        {
            while(vfs[k].belong>0&&vfs[k].type=='d')
            {
                if(!strcmp(vfs[k].name,catbuf[i]))
                {
                    flag=1;
                    if(i==j-1)
                    {
                        aflag=1;
                        vfs[k].cur_cat='1';
                        updatemysqltabletwo(&vfs[k]);
                        break;
                    }
                    vfs[0].procode=vfs[0].code;
                    vfs[0].cur_cat='6';
                    querymysqltabletwo(vfs);
                    break;
                }
                k++;
            }
            if(flag==0||aflag==1)
            {
                break;
            }
            flag=0;
        }
        if(aflag==1)
        {
            vfs[0].code=code;
            vfs[0].cur_cat='4';
            querymysqltabletwo(&vfs[0]);
            vfs[0].cur_cat='0';
            updatemysqltabletwo(&vfs[0]);
            strcpy(buf,"success change\n");
            datalen=strlen(buf);
            send_n(fd,&datalen,sizeof(int));
            send_n(fd,buf,datalen);
            return 0;
        }
       // strcpy(buf,"please check pathname\n");
       // datalen=strlen(buf);
       // send_n(fd,&datalen,sizeof(int));
       // send_n(fd,buf,datalen);
        return -1;
    }
    return 0;
}

void my_pwd(int fd)
{
    int datalen;
    char buf[MAX_BUF_SIZE]={0};
    char catbuf[VIR_FILE_SYS_MAX_DEEP_][VIR_FILE_SYS_MAX_DEEP_];
    int count=0,i;

    Vir_File_Sys vfs;
    Acc_Inf ai;
    Tmp_Fd_Acci tfa;
    tfa.fd=fd;
    querymysqltablethree(&tfa);
    strcpy(ai.name,tfa.name);
    querymysqltableone(&ai);
    vfs.belong=ai.PasswdId;
    vfs.cur_cat='1';
    querymysqltabletwo(&vfs);   // current catalog
    do{
        strcpy(catbuf[count++],vfs.name);
        vfs.code=vfs.procode;
        vfs.cur_cat='4';
        querymysqltabletwo(&vfs);
    }while(vfs.procode);    // belong + code(previous procode) mode
    count--;
    if(count>=0&&vfs.code!=0)
    {
        for(i=count;i>=0;i--)
        {
            sprintf(buf,"%s/%s",buf,catbuf[i]);
        }
        strcat(buf,"\n");
        datalen=strlen(buf);
        send_n(fd,&datalen,sizeof(int));
        send_n(fd,buf,datalen);
        return ;
    }
    strcpy(buf,"/ \n");
    datalen=strlen(buf);
    send_n(fd,&datalen,sizeof(int));
    send_n(fd,buf,datalen);
}

int my_ls(const char *addr,int fd)
{
    if(!strcmp(addr,".")||strlen(addr)==0)
    {
        int datalen;
        char buf[MAX_BUF_SIZE]={0};
        char temp[MAX_BUF_SIZE]={0};
        int i=0,code=0,num=0;

        Vir_File_Sys vfs[VIR_FILE_SYS_MAX_NUM_];
        Acc_Inf ai;
        Tmp_Fd_Acci tfa;
        tfa.fd=fd;
        querymysqltablethree(&tfa);
        strcpy(ai.name,tfa.name);
        querymysqltableone(&ai);
        vfs[0].belong=ai.PasswdId;
        vfs[0].cur_cat='1';
        querymysqltabletwo(&vfs[0]);   // current catalog


        code=vfs[0].code;
        vfs[0].procode=code;
        vfs[0].cur_cat='6';
        num=querymysqltabletwo(vfs);
        if(!num)
        {
           // strcpy(buf,"no file\n");
           // datalen=strlen(buf);
           // send_n(fd,&datalen,sizeof(int));
           // send_n(fd,buf,datalen);
            return -1;
        }
        i=0;
        while(i<num)
        {
            sprintf(temp,"%s\t%c\t%ld\n",vfs[i].name,vfs[i].type,vfs[i].size);
            i++;
            strcat(buf,temp);
            memset(temp,0,sizeof(temp));
        }
        strcat(buf,"\n");
        datalen=strlen(buf);
        send_n(fd,&datalen,sizeof(int));
        send_n(fd,buf,datalen);
        return 0;
    }
    if(!strcmp(addr,".."))
    {
        int datalen;
        char buf[MAX_BUF_SIZE]={0};
        char temp[MAX_BUF_SIZE]={0};
        int i=0,code=0,num=0;
        Vir_File_Sys vfs[VIR_FILE_SYS_MAX_NUM_];
        Acc_Inf ai;
        Tmp_Fd_Acci tfa;
        tfa.fd=fd;
        querymysqltablethree(&tfa);
        strcpy(ai.name,tfa.name);
        querymysqltableone(&ai);
        vfs[0].belong=ai.PasswdId;
        vfs[0].cur_cat='1';
        querymysqltabletwo(&vfs[0]);   // current catalog
        code=vfs[0].procode;
        vfs[0].procode=code;
        vfs[0].cur_cat='6';
        num=querymysqltabletwo(vfs);
        if(!num)
        {
           // strcpy(buf,"no file\n");
           // datalen=strlen(buf);
           // send_n(fd,&datalen,sizeof(int));
           // send_n(fd,buf,datalen);
            return -1;
        }
        i=0;
        memset(temp,0,sizeof(temp));
        while(i<num)
        {
            sprintf(temp,"%s\t%c\t%ld\n",vfs[i].name,vfs[i].type,vfs[i].size);
            i++;
            strcat(buf,temp);
            memset(temp,0,sizeof(temp));
        }
        strcat(buf,"\n");
        datalen=strlen(buf);
        send_n(fd,&datalen,sizeof(int));
        send_n(fd,buf,datalen);
        return 0;


    }
    if((0!=strncmp(addr,"/",1))&&(0!=strncmp(addr,".",1)))
    {
        int datalen,code=0,i=0,j=0,k=0,flag=0,aflag=0,num=0;
        char buf[MAX_BUF_SIZE]={0};
        char temp[MAX_BUF_SIZE]={0};
        char catbuf[VIR_FILE_SYS_MAX_DEEP_][VIR_FILE_SYS_MAX_NUM_];

        Vir_File_Sys vfs[VIR_FILE_SYS_MAX_NUM_];
        Tmp_Fd_Acci tfa;
        Acc_Inf ai;
        tfa.fd=fd;
        querymysqltablethree(&tfa);
        strcpy(ai.name,tfa.name);
        querymysqltableone(&ai);
        vfs[0].belong=ai.PasswdId;
        vfs[0].cur_cat='1';
        querymysqltabletwo(&vfs[0]);
        code=vfs[0].code;
        while (addr[i] != 0)
        {
            if (addr[i] == '/')
            {
                i++;
            }
            while (addr[i] != '/'&&addr[i] != 0)
            {
                temp[k++] = addr[i++];
            }
            temp[k] = 0;
            strcpy(catbuf[j++],temp);
            memset(temp,0,sizeof(temp));
            k = 0;
        }
#ifdef DEBUG
        for(i=0;i<j;i++)
            printf("%s\n",catbuf[i]);
#endif

        vfs[0].procode=code;
        vfs[0].cur_cat='6';
        querymysqltabletwo(vfs);
        k=0;
        for(i=0;i<j;i++)
        {
            while(vfs[k].belong>0&&vfs[k].type=='d')
            {
                if(!strcmp(vfs[k].name,catbuf[i]))
                {
                    flag=1;
                    if(i==j-1)
                    {
                        aflag=1;
                        code=vfs[k].code;
                        break;
                    }
                    vfs[0].procode=vfs[0].code;
                    vfs[0].cur_cat='6';
                    querymysqltabletwo(vfs);
                    break;
                }
                k++;
            }
            if(flag==0||aflag==1)
            {
                break;
            }
            flag=0;
        }
        printf("%d,%d\n",aflag,code);
        if(aflag==1)
        {
            printf("pathname right\n");
            vfs[0].procode=code;
            vfs[0].cur_cat='6';
            num=querymysqltabletwo(vfs);
#ifdef DEBUG
            printf("%d\n",num);
#endif
            if(!num)
            {
               // strcpy(buf,"no file\n");
               // printf("no file\n");
               // send_n(fd,&datalen,sizeof(int));
               // send_n(fd,buf,datalen);
                return -1;
            }
            i=0;
            memset(buf,0,sizeof(buf));
            memset(temp,0,sizeof(temp));
            while(i<num)
            {
#ifdef DEBUG
                printf("%s\t%c\t%ld\n",vfs[i].name,vfs[i].type,vfs[i].size);
#endif
                sprintf(temp,"%s\t%c\t%ld\n",vfs[i].name,vfs[i].type,vfs[i].size);
                i++;
                strcat(buf,temp);
                memset(temp,0,sizeof(temp));
            }
            strcat(buf,"\n");
            datalen=strlen(buf);
            printf("success\n");
            send_n(fd,&datalen,sizeof(int));
            send_n(fd,buf,datalen);
            return 0;
        }
        printf("error\n");
       // strcpy(buf,"error: pathname\n");
       // datalen=strlen(buf);
       // send_n(fd,&datalen,sizeof(int));
       // send_n(fd,buf,datalen);
        return -1;
    }
    if(!strncmp(addr,"/",1))
    {
        int datalen,code=0,i=0,j=0,k=0,flag=0,aflag=0,num=0;
        char buf[MAX_BUF_SIZE]={0};
        char temp[MAX_BUF_SIZE]={0};
        char catbuf[VIR_FILE_SYS_MAX_DEEP_][VIR_FILE_SYS_MAX_NUM_];

        Vir_File_Sys vfs[VIR_FILE_SYS_MAX_NUM_];
        Tmp_Fd_Acci tfa;
        Acc_Inf ai;
        tfa.fd=fd;
        querymysqltablethree(&tfa);
        strcpy(ai.name,tfa.name);
        querymysqltableone(&ai);
        vfs[0].belong=ai.PasswdId;
        vfs[0].cur_cat='1';
        querymysqltabletwo(&vfs[0]);
        code=vfs[0].code;
        i=1;
        while (addr[i] != 0)
        {
            if (addr[i] == '/')
            {
                i++;
            }
            while (addr[i] != '/'&&addr[i] != 0)
            {
                temp[k++] = addr[i++];
            }
            temp[k] = 0;
            strcpy(catbuf[j++],temp);
            memset(temp,0,sizeof(temp));
            k = 0;
        }
#ifdef DEBUG
        for(i=0;i<j;i++)
            printf("%s\n",catbuf[i]);
#endif

        vfs[0].procode=vfs[0].code;
        vfs[0].cur_cat='6';
        querymysqltabletwo(vfs);
        k=0;
        for(i=0;i<j;i++)
        {
            while(vfs[k].belong>0&&vfs[k].type=='d')
            {
                if(!strcmp(vfs[k].name,catbuf[i]))
                {
                    flag=1;
                    if(i==j-1)
                    {
                        aflag=1;
                        code=vfs[k].code;
                        break;
                    }
                    vfs[0].procode=vfs[0].code;
                    vfs[0].cur_cat='6';
                    querymysqltabletwo(vfs);
                    break;
                }
                k++;
            }
            if(flag==0||aflag==1)
            {
                break;
            }
            flag=0;
        }
        if(aflag==1)
        {
            vfs[0].procode=code;
            vfs[0].cur_cat='6';
            if(!(num=querymysqltabletwo(vfs)))
            {
               // strcpy(buf,"no file\n");
               // printf("no file\n");
               // send_n(fd,&datalen,sizeof(int));
               // send_n(fd,buf,datalen);
                return -1;
            }
            i=0;
            memset(temp,0,sizeof(temp));
            while(i<num)
            {
                printf("%s\t%c\t%ld\n",vfs[i].name,vfs[i].type,vfs[i].size);
                sprintf(temp,"%s\t%c\t%ld\n",vfs[i].name,vfs[i].type,vfs[i].size);
                i++;
                strcat(buf,temp);
                memset(temp,0,sizeof(temp));
            }
            strcat(buf,"\n");
            datalen=strlen(buf);
            printf("success\n");
            send_n(fd,&datalen,sizeof(int));
            send_n(fd,buf,datalen);
            return 0;
        }
       // printf("error\n");
       // strcpy(buf,"error: pathname\n");
       // datalen=strlen(buf);
       // send_n(fd,&datalen,sizeof(int));
       // send_n(fd,buf,datalen);
        return -1;
    }
    return 0;
}


int my_rm(const char *filename,int fd)
{
    int datalen;
    char buf[MAX_BUF_SIZE]={0};
    char md5sum[FILE_SYS_MD5_SIZE_];
    int num=0,k=0,code=0,flag=0;

    Vir_File_Sys vfs[VIR_FILE_SYS_MAX_NUM_];
    Tmp_Fd_Acci tfa;
    Acc_Inf ai;
    tfa.fd=fd;
    querymysqltablethree(&tfa);
    strcpy(ai.name,tfa.name);
    querymysqltableone(&ai);
    vfs[0].belong=ai.PasswdId;
    vfs[0].cur_cat='1';
    querymysqltabletwo(&vfs[0]);
    code=vfs[0].code;
    
    printf("%s,%d\n",filename,code);

    vfs[0].procode=vfs[0].code;
    vfs[0].cur_cat='6';
    num=querymysqltabletwo(vfs);
    k=0;
    while(k<num)
    {
        if((vfs[k].type=='-')&&(!strcmp(vfs[k].name,filename))&&(vfs[k].procode==code))
        {
            flag=1;
            strcpy(md5sum,vfs[k].md5sum);
            vfs[k].cur_cat='0';
            deletemysqltabletwo(&vfs[k]);
            break;
        }
        k++;
    }
    if(flag==1)
    {
        printf("success flag\n");
        strcpy(buf,"success remove file\n");
        datalen=strlen(buf);
        char path[MAX_BUF_SIZE];
        sprintf(path,"%s%s",FILE_STORAGE_PATH_,md5sum);
        printf("%s\n",path);
        if(-1==unlink(path))
        {
           // printf("failed rm file\n");
           // strcpy(buf,"remove file failed\n");
           // datalen=strlen(buf);
           // send_n(fd,&datalen,sizeof(int));
           // send_n(fd,buf,datalen);
            return -1;
        }
        printf("success rm\n");
        send_n(fd,&datalen,sizeof(int));
        send_n(fd,buf,datalen);
        return 0;
    }else{
       // printf("failed find filename\n");
       // strcpy(buf,"please chech filename\n");
       // datalen=strlen(buf);
       // send_n(fd,&datalen,sizeof(int));
       // send_n(fd,buf,datalen);
        return -1;
    }
}


