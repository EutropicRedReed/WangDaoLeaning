#include "tranfile.h"
int tcpInit();
int my_chdir(const char *addr,int fd);
void my_pwd(int fd);
int my_ls(const char *addr,int fd);
void my_rm(const char *pathname,int fd);

int recvorder(int fd)
{
    int datalen;
    char buf[MAX_BUF_SIZE]={0};
    short type=0;
    while(1)
    {
        memset(buf,0,sizeof(buf));
        if(-1==recv_n(fd,&datalen,sizeof(int)))
        {close(fd);printf("server close\n");return -1;}
        if(-1==recv_n(fd,&type,sizeof(short)))
        {close(fd);printf("server close\n");return -1;}
        if(-1==recv_n(fd,buf,datalen))
        {close(fd);printf("server close\n");return -1;}
        switch(type)
        {
        case 1:
            my_chdir(buf,fd);
            break;
        case 2:
            my_ls(buf,fd);
            break;
        case 3:
            my_rm(buf,fd);
            break;
        case 4:
            my_pwd(fd);
            break;
        case 5:
            tranFile(fd,buf);
            break;
        case 6:
            uploadFile(fd);
            break;
        default :
            break;
        }
    }
    return 0;
}

