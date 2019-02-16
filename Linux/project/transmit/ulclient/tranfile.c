#include "tranfile.h"
int tranFile(int socketfd,char *pathname)
{
    int datalen;
    char buf[MAX_BUF_SIZE]={0};
    char md5[FILE_SYS_MD5_SIZE_]={0};
    // send file name.
    strcpy(buf,pathname);
    datalen=strlen(pathname);
    if(-1==send_n(socketfd,&datalen,sizeof(int)))
    {close(socketfd);printf("server close\n");return -1;}
    if(-1==send_n(socketfd,buf,datalen))
    {close(socketfd);printf("server close\n");return -1;}
    // send file size.
    int fd=open(pathname,O_RDONLY);
    if(-1==fd){perror("open");return -1;}
    struct stat statbuf;
    fstat(fd,&statbuf);
    memcpy(buf,&statbuf.st_size,sizeof(statbuf.st_size));
    datalen=sizeof(statbuf.st_size);
    if(-1==send_n(socketfd,&datalen,sizeof(int)))
    {close(socketfd);printf("server close\n");return -1;}
    if(-1==send_n(socketfd,buf,datalen))
    {close(socketfd);printf("server close\n");return -1;}
    // send file md5sum.
    strcpy(md5,pathname);
    getMd5Sum(md5);
    datalen=strlen(md5);
    strcpy(buf,md5);
    if(-1==send_n(socketfd,&datalen,sizeof(int)))
    {close(socketfd);printf("server close\n");return -1;}
    if(-1==send_n(socketfd,buf,datalen))
    {close(socketfd);printf("server close\n");return -1;}

    recv_n(socketfd,&datalen,sizeof(int));  // receive symbol file exist?.
    if(datalen)
    {
        return 0;
    }
    // begin send file.
    if(-1==sendfile(socketfd,fd,0,statbuf.st_size))
    {close(socketfd);perror("sendfile");return -1;}
    // finish.
    //
    //recv_n(socketfd,&datalen,sizeof(int));

    //datalen=0;
    //send_n(socketfd,&datalen,sizeof(int));
    return 0;
}

