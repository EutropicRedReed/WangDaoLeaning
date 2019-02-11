#include "tranfile.h"
int uploadFile(int new_fd)
{
    int ret;
    int datalen;
    char buf[MAX_BUF_SIZE]={0};
    //receive file name.
    recv_n(new_fd,&datalen,sizeof(int));
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
    while(1)
    {
        ret=recv_n(new_fd,&datalen,sizeof(int));
        if(-1==ret)
        {
            printf("server crash\n");
            return -1;
        }
        if(datalen>0)
        {
            ret=recv_n(new_fd,buf,datalen);
            if(-1==ret)
            {
                printf("server crash\n");
                return -1;
            }
            write(fd,buf,datalen);
            fileLoadSize+=datalen;
            fileSlice+=datalen;
            if(fileLoadSize>=fileTotalSize/10000)
            {
                printf("%5.2f%%\r",(double)fileLoadSize/fileTotalSize*100);
                fflush(stdout);
                fileSlice=0;
            }
        }else{
            printf("100.00%%\n");
            printf("receive success\n");
            break;
        }
    }
    return 0;
}

