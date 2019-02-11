#include "tranfile.h"
int tranFile(int socketfd,char *pathname)
{
    int datalen;
    char buf[MAX_BUF_SIZE]={0};
    strcpy(buf,pathname);
    datalen=strlen(pathname);
    if(-1==send_n(socketfd,&datalen,sizeof(int)))
    {close(socketfd);printf("server close\n");return -1;}
    if(-1==send_n(socketfd,buf,datalen))
    {close(socketfd);printf("server close\n");return -1;}
    int fd=open("file",O_RDONLY);
    if(-1==fd){perror("oprn");return -1;}
    struct stat statbuf;
    fstat(fd,&statbuf);
    memcpy(buf,&statbuf.st_size,sizeof(statbuf.st_size));
    datalen=sizeof(statbuf.st_size);
    if(-1==send_n(socketfd,&datalen,sizeof(int)))
    {close(socketfd);printf("server close\n");return -1;}
    if(-1==send_n(socketfd,buf,datalen))
    {close(socketfd);printf("server close\n");return -1;}
    while((datalen=read(fd,buf,sizeof(buf))))
    {
        if(-1==send_n(socketfd,&datalen,sizeof(int)))
        {close(socketfd);printf("server close\n");return -1;}
        if(-1==send_n(socketfd,buf,datalen))
        {close(socketfd);printf("server close\n");return -1;}
    }
    send_n(socketfd,&datalen,sizeof(int));
    send_n(socketfd,buf,datalen);
    close(socketfd);
    return 0;
}

