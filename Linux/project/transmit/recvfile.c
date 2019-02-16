#include "factory.h"
int uploadFile(int new_fd)
{
    int ret,code=0;
    int datalen;
    char buf[MAX_BUF_SIZE]={0};
    char pathname[MAX_BUF_SIZE]={0};

    Acc_Inf ai;
    Vir_File_Sys vfs;
    Tmp_Fd_Acci tfa;
    tfa.fd=new_fd;
    querymysqltablethree(&tfa);
    strcpy(ai.name,tfa.name);
    querymysqltableone(&ai);
    vfs.belong=ai.PasswdId;
    vfs.cur_cat='1';
    querymysqltabletwo(&vfs);
    code=vfs.code;
    ret=vfs.belong;
    //send_n(new_fd,&flag,sizeof(int));

    //receive file name.
    recv_n(new_fd,&datalen,sizeof(int));
    if(-1==datalen)
    {printf("error: gets\n");return -1;}
    recv_n(new_fd,buf,datalen);
#ifdef DEBUG
    printf("success receive filename\n");
#endif
    strcpy(vfs.name,buf);
    vfs.belong=ai.PasswdId;

    //receive file size.

    recv_n(new_fd,&datalen,sizeof(int));
    recv_n(new_fd,&vfs.size,datalen);

#ifdef DEBUG
    printf("success receive filesize\n");
#endif
    vfs.procode=code;
    vfs.type='-';

    // receive file md5sum.
    recv_n(new_fd,&datalen,sizeof(int));
    recv_n(new_fd,&buf,datalen);
    strcpy(vfs.md5sum,buf);
#ifdef DEBUG
    printf("success receive filemd5\n");
#endif

    vfs.cur_cat='2';
    if((ret=querymysqltabletwo(&vfs)))  // search md5sum mode, file exist.
    {
        datalen=1;
        send_n(new_fd,&datalen,sizeof(int));
        return 1;
    }
    insertmysqltabletwo(&vfs);
    datalen=0;
    send_n(new_fd,&datalen,sizeof(int));


#ifdef DEBUG
    printf("success insert filename\n");
#endif
    int fd;
    sprintf(pathname,"%s%s",FILE_STORAGE_PATH_,vfs.md5sum);
    fd=open(pathname,O_CREAT|O_WRONLY,0666);
    if(-1==fd)
    {
        perror("open");
        return -1;
    }
    int pipefd[2];
    if(-1==pipe(pipefd))
    {perror("pipe");return -1;}
    off_t fileloadSize=0,fileSlice=0;
    ret=0;
    while(1)
    {
        ret=splice(new_fd,NULL,pipefd[1],NULL,\
                   PIPE_BUF_, SPLICE_F_MORE );
        fileloadSize+=ret;
        fileSlice+=ret;
        if(fileSlice>=vfs.size/10000)
        {
            printf("\r%5.2f%%",(float)fileloadSize/vfs.size*100);
            fflush(stdout);
            if(fileloadSize==vfs.size)
            {
                break;
            }
        }
        if(-1==ret)
        {
            perror("splice");
            return -1;
        }else if(0==ret)
        {
            printf("\r100.00%%\n");
            break;
        }
        if(-1==splice(pipefd[0],NULL,fd,NULL,\
                      PIPE_BUF_, SPLICE_F_MORE ))
        {
            perror("splice");
            return -1;
        }
    }
    close(fd);
    printf("receive success\n");
    return 0;
}

