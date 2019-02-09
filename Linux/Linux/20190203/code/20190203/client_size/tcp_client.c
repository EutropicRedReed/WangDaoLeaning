#include <func.h>
int recv_n(int sfd,char* ptran,int len);
int main(int argc,char *argv[])
{
    args_check(argc,3);
    int socketfd=socket(AF_INET,SOCK_STREAM,0);
    if(-1==socketfd)
    {
        perror("socket");
        return -1;
    }
    printf("socketfd=%d\n",socketfd);
    struct sockaddr_in ser;
    memset(&ser,0,sizeof(ser));
    ser.sin_family=AF_INET;
    ser.sin_port=htons(atoi(argv[2]));
    ser.sin_addr.s_addr=inet_addr(argv[1]);
    int ret;
    ret=connect(socketfd,(struct sockaddr*)&ser,sizeof(struct sockaddr));
    if(-1==ret)
    {
        perror("connect");
        return -1;
    }
    int dataLen;
    char buf[1000]={0};
    recv_n(socketfd,(char*)&dataLen,sizeof(int));
    recv_n(socketfd,buf,dataLen);
    off_t fileTotalSize,fileLoadSize=0;
    //接文件大小
    recv_n(socketfd,(char*)&dataLen,sizeof(int));
    recv_n(socketfd,(char*)&fileTotalSize,dataLen);
    int fd;
    fd=open(buf,O_WRONLY|O_CREAT,0666);
    if(-1==fd)
    {
        perror("open");
        return -1;
    }
    off_t fileSlice=fileTotalSize/10000;
    off_t lastFileSize=0;
    while(1)
    {
        recv_n(socketfd,(char*)&dataLen,sizeof(int));
        if(dataLen>0)
        {
            recv_n(socketfd,buf,dataLen);
            write(fd,buf,dataLen);
            fileLoadSize+=dataLen;
            if(fileLoadSize-lastFileSize>=fileSlice)
            {
                printf("%5.2f%s\r",(double)fileLoadSize/fileTotalSize*100,"%");
                fflush(stdout);
                lastFileSize=fileLoadSize;
            }
        }else{
            printf("100.00%s\n","%");
            close(fd);
            printf("recv success\n");
            break;
        }
    }
    close(socketfd);
}
