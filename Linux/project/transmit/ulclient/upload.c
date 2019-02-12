#include "tranfile.h"
int uploadFile(int new_fd)
{
    int ret;
    int datalen;
    char buf[MAX_BUF_SIZE]={0};
    //receive file name.
    recv_n(new_fd,&datalen,sizeof(int));
    if(-1==datalen)
    {printf("error: gets\n");return -1;}
    recv_n(new_fd,buf,datalen);
    //receive file size.
    off_t fileTotalSize,fileLoadSize=0,fileSlice=0;
    recv_n(new_fd,&datalen,sizeof(int));
    recv_n(new_fd,&fileTotalSize,datalen);
    int fd;
    fd=open(buf,O_CREAT|O_WRONLY,0666);
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
        fileLoadSize+=ret;
        fileSlice+=ret;
        if(fileSlice>=fileTotalSize/10000)
        {
            printf("\r%5.2f%%",(float)fileLoadSize/fileTotalSize);
            fflush(stdout);
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
                      PIPE_BUF_, SPLICE_F_MORE | SPLICE_F_MOVE ))
        {
            perror("splice");
            return -1;
        }
        fileSlice=0;
    }
    close(fd);
    printf("receive success\n");
    return 0;
}

