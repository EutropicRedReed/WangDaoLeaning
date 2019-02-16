#include "factory.h"
int uploadFile(int new_fd)
{
    int ret,code=0;
    int datalen;
    char buf[MAX_BUF_SIZE]={0};
    char md5buf[FILE_SYS_MD5_SIZE_]={0};

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

    //receive file name.
    recv_n(new_fd,&datalen,sizeof(int));
    if(-1==datalen)
    {printf("error: gets\n");return -1;}
    recv_n(new_fd,buf,datalen);

    strcpy(vfs.name,buf);
    vfs.belong=ai.PasswdId;

    //receive file size.
    recv_n(new_fd,&datalen,sizeof(int));
    recv_n(new_fd,&vfs.size,datalen);
    
    vfs.procode=code;
    vfs.type='-';
    getMd5Sum(md5buf);
    strcpy(vfs.md5sum,md5buf);

    insertmysqltabletwo(&vfs);


    int fd;
    fd=open(md5buf,O_CREAT|O_WRONLY,0666);
    if(-1==fd)
    {
        perror("open");
        return -1;
    }
    int pipefd[2];
    if(-1==pipe(pipefd))
    {perror("pipe");return -1;}
    while(1)
    {
        ret=splice(new_fd,NULL,pipefd[1],NULL,\
                   PIPE_BUF_, SPLICE_F_MORE | SPLICE_F_MOVE );
        if(-1==ret)
        {
            perror("splice");
            return -1;
        }else if(0==ret)
        {
            break;
        }
        if(-1==splice(pipefd[0],NULL,fd,NULL,\
                      PIPE_BUF_, SPLICE_F_MORE | SPLICE_F_MOVE ))
        {
            perror("splice");
            return -1;
        }
    }
    close(fd);
    printf("receive success\n");
    return 0;
}

