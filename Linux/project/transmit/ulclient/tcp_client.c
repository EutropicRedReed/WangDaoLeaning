#include "head.h"
#include "tranfile.h"
int sendorder(int);
int send_n(int sfd,void* ptran,int len);
int main()//(int argc,char *argv[])
{
    //args_check(argc,2);
    int socketfd=socket(AF_INET,SOCK_STREAM,0);
    if(-1==socketfd)
    {
        perror("socket");
        return -1;
    }
    struct sockaddr_in ser;
    memset(&ser,0,sizeof(ser));
    ser.sin_family=AF_INET;
    //ser.sin_port=htons(atoi(argv[1]));
    ser.sin_port=htons(atoi("2333"));
    //ser.sin_addr.s_addr=inet_addr(argv[1]);
    ser.sin_addr.s_addr=inet_addr("192.168.3.233");
    int ret;
    ret=connect(socketfd,(struct sockaddr*)&ser,sizeof(struct sockaddr));
    printf("success connect\n");
    if(-1==ret)
    {
        perror("connect");
        return -1;
    }
    //tranFile(socketfd);
    //uploadFile(socketfd);
    if(-1!=signinconfirmclient(socketfd))
    {
        sendorder(socketfd);
    }


    //int datalen;
    //char buf[1000]={0};
    //strcpy(buf,"file");
    //datalen=strlen("file");
    //if(-1==send_n(socketfd,&datalen,sizeof(int)))
    //{close(socketfd);printf("server close\n");return -1;}
    //if(-1==send_n(socketfd,buf,datalen))
    //{close(socketfd);printf("server close\n");return -1;}
    //int fd=open("file",O_RDONLY);
    //if(-1==fd){perror("oprn");return -1;}
    //struct stat statbuf;
    //fstat(fd,&statbuf);
    //memcpy(buf,&statbuf.st_size,sizeof(statbuf.st_size));
    //datalen=sizeof(statbuf.st_size);
    //if(-1==send_n(socketfd,&datalen,sizeof(int)))
    //{close(socketfd);printf("server close\n");return -1;}
    //if(-1==send_n(socketfd,buf,datalen))
    //{close(socketfd);printf("server close\n");return -1;}
    //while((datalen=read(fd,buf,sizeof(buf))))
    //{
    //    if(-1==send_n(socketfd,&datalen,sizeof(int)))
    //    {close(socketfd);printf("server close\n");return -1;}
    //    if(-1==send_n(socketfd,buf,datalen))
    //    {close(socketfd);printf("server close\n");return -1;}
    //}
    //send_n(socketfd,&datalen,sizeof(int));
    //send_n(socketfd,buf,datalen);
    close(socketfd);
    return 0;
}
