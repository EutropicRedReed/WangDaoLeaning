#include <func.h>

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
    recv(socketfd,&dataLen,sizeof(int),0);
    recv(socketfd,buf,dataLen,0);
    int fd;
    fd=open(buf,O_WRONLY|O_CREAT,0666);
    if(-1==fd)
    {
        perror("open");
        return -1;
    }
    while(1)
    {
        recv(socketfd,&dataLen,sizeof(int),0);
        if(dataLen>0)
        {
            recv(socketfd,buf,dataLen,0);
            write(fd,buf,dataLen);
        }else{
            close(fd);
            printf("recv success\n");
            break;
        }
    }
    close(socketfd);
}
