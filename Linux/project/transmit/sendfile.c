#include "factory.h"
int tranFile(int socketfd,char *filename)
{
    int datalen;
    char buf[MAX_BUF_SIZE]={0};
    char pathname[MAX_BUF_SIZE]={0};
    char md5sum[FILE_SYS_MD5_SIZE_]={0};
    int num=0,i=0,code=0,flag=0;
    long int size=0;
    // send file name.
    Acc_Inf ai;
    Vir_File_Sys vfs[VIR_FILE_SYS_MAX_NUM_];
    Tmp_Fd_Acci tfa;
    tfa.fd=socketfd;
    querymysqltablethree(&tfa);
    strcpy(ai.name,tfa.name);
    querymysqltableone(&ai);
    vfs[0].belong=ai.PasswdId;
    vfs[0].cur_cat='1';
    querymysqltabletwo(&vfs[0]);
    vfs[0].procode=vfs[0].code;
    vfs[0].cur_cat='6';
    num=querymysqltabletwo(vfs);
    if(-1==num)
    {return -1;}
    while(i<num)
    {
        if(!strcmp(vfs[i].name,filename)&&(vfs[i].type=='-'))
        {
            strcpy(md5sum,vfs[i].md5sum);
            size=vfs[i].size;
            code=vfs[i].code;
            flag=1;
#ifdef DEBUG
            printf("%s,%d\n",vfs[i].md5sum,code);
#endif
            send_n(socketfd,&flag,sizeof(int));
        }
        i++;
    }
    if(1==flag)
    {
#ifdef DEBUG
    printf("%s,%ld\n",md5sum,size);
#endif
    sprintf(pathname,"%s%s",FILE_STORAGE_PATH_,md5sum);
    // send file name.
    strcpy(buf,filename);
    datalen=strlen(buf);
    if(-1==send_n(socketfd,&datalen,sizeof(int)))
    {close(socketfd);printf("server close\n");return -1;}
    if(-1==send_n(socketfd,buf,datalen))
    {close(socketfd);printf("server close\n");return -1;}
    // send file size.
    memcpy(buf,&size,sizeof(size));
    datalen=sizeof(size);
    if(-1==send_n(socketfd,&datalen,sizeof(int)))
    {close(socketfd);printf("server close\n");return -1;}
    if(-1==send_n(socketfd,buf,datalen))
    {close(socketfd);printf("server close\n");return -1;}

    // recv file offset.
    off_t offset;
    recv_n(socketfd,&datalen,sizeof(int));
    recv_n(socketfd,&offset,datalen);



    int fd=open(pathname,O_RDONLY);
    if(-1==fd){perror("open");return -1;}
 
    // begin send file.
    if(-1==sendfile(socketfd,fd,&offset,size))
    {perror("sendfile");return -1;}
    // send end symbol of file.
    datalen=0;
    send_n(socketfd,&datalen,sizeof(int));
    }else{
        return -1;
    }

    return 0;
}

