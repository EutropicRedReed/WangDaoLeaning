#ifndef _TCP_NET_SOCKET_H
#define _TCP_NET_SOCKET_H

#include <func.h>

extern int tcp_init(const char* ip,int port);
extern int tcp_accept(int sfd);
extern int tcp_connect(const char* ip,int port);
extern void signalhandler(void);

#endif

int tcp_init(const char* ip,int port)
{
    int sfd = socket(AF_INET,SOCK_STREAM,0);
    if(sfd==-1)
    {
        perror("socket");
        exit(-1);
    }
    struct sockaddr_in serveraddr;
    memset(&serveraddr,0,sizeof(struct sockaddr_in));
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(port);
    serveraddr.sin_addr.s_addr=inet_addr(ip);
    if(bind(sfd,(struct sockaddr*)&serveraddr,sizeof(struct sockaddr))==-1)
    {
        perror("bind");
        close(sfd);
        exit(-1);
    }
    if(listen(sfd,10)==-1)
    {
        perror("listen");
        close(sfd);
        exit(-1);
    }
    return sfd;
}

int tcp_accept(int sfd)
{
    struct sockaddr_in clientaddr;
    memset(&clientaddr,0,sizeof(struct sockaddr_in));
    socklen_t addrlen=sizeof(struct sockaddr);
    int new_fd=accept(sfd,(struct sockaddr*)&clientaddr,&addrlen);
    if(new_fd==-1)
    {
        perror("accept");
        close(sfd);
        exit(-1);
    }
    printf("%s %d success connect. \n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
    return new_fd;
}

int tcp_connect(const char* ip,int port)
{
    int sfd = socket(AF_INET,SOCK_STREAM,0);
    if(-1==sfd)
    {
        perror("socket");
        exit(-1);
    }
    struct sockaddr_in serveraddr;
    memset(&serveraddr,0,sizeof(struct sockaddr));
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(port);
    serveraddr.sin_addr.s_addr=inet_addr(ip);
    if(-1==connect(sfd,(struct sockaddr*)&serveraddr,sizeof(struct sockaddr)))
    {
        perror("connect");
        close(sfd);
        exit(-1);
    }
    return sfd;
}

void signalhandler(void)
{
    sigset_t sigSet;
    sigemptyset(&sigSet);
    sigaddset(&sigSet,SIGINT);
    //sigaddset(&sigSet,SIGQUIT);
    sigprocmask(SIG_BLOCK,&sigSet,NULL);
}





int main(int argc,char *argv[])
{
    args_check(argc,3);
    signalhandler();
    int sfd=tcp_init(argv[1],atoi(argv[2]));
    fd_set readset;
    int ret;
    while(1)
    {
        int cfd=tcp_accept(sfd);
        while(1)
        {
            char buf[512]={0};
            FD_ZERO(&readset);
            FD_SET(cfd,&readset);
            FD_SET(STDIN_FILENO,&readset);
            ret=select(cfd+1,&readset,NULL,NULL,NULL);
            if(FD_ISSET(cfd,&readset))
            {
                memset(buf,0,sizeof(buf));
                ret=recv(cfd,buf,sizeof(buf),0);
                if(-1==ret)
                {
                    perror("recv");
                    close(cfd);
                    close(sfd);
                    exit(-1);
                }else if(0==ret)
                {
                    printf("client disconnect\n");
                    break;
                }
                printf("%s--from client\n",buf);//already have \n in cfd cache.
            }else if(FD_ISSET(STDIN_FILENO,&readset))
            {
                memset(buf,0,sizeof(buf));
                fgets(buf,sizeof(buf),stdin);
                if(-1==send(cfd,buf,strlen(buf)-1,0))
                {
                    perror("send");
                    close(cfd);
                    exit(-1);
                }
            }else if(-1==ret)
            {
                perror("select");
                close(sfd);
                exit(-1);
            }
        }
        close(cfd);
    }
    close(sfd);
    return 0;
}

