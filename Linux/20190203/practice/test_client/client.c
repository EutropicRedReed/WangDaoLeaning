#ifndef _TCP_NET_SOCKET_H
#define _TCP_NET_SOCKET_H

#include <func.h>

extern int tcp_init(const char* ip,int port);
extern int tcp_accept(int sfd);
extern int tcp_connect(const char* ip,int port);
extern void signalhandler(void);
int send_loop(int sfd,void* ptr,int len);
int recv_loop(int sfd,void* ptr,int len);

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
    sigaddset(&sigSet,SIGQUIT);
    sigprocmask(SIG_BLOCK,&sigSet,NULL);
}

int send_loop(int sfd,void* p,int len)
{
    char *ptr=(char*)p;
    int total=0;
    int ret;
    while(total<len)
    {
        ret=send(sfd,ptr+total,len-total,0);
        total+=ret;
    }
    return 0;
}

int recv_loop(int sfd,void* p,int len)
{
    char *ptr=(char*)p;
    int total=0;
    int ret;
    while(total<len)
    {
        ret=recv(sfd,ptr+total,len-total,0);
        total+=ret;
    }
    return 0;
}



int main(int argc,char *argv[])
{
    args_check(argc,3);
    int sfd=tcp_connect(argv[1],atoi(argv[2]));
    char buf[1024]={0};
    int fd,datalen,type;
    fscanf(stdin,"%s",buf);//ex blank
    datalen=strlen(buf);
    type=1;
    send_loop(sfd,&datalen,sizeof(int));
    send_loop(sfd,&type,sizeof(int));
    send_loop(sfd,buf,strlen(buf));
    memset(buf,0,sizeof(buf));
    recv_loop(sfd,&datalen,sizeof(int));
    recv_loop(sfd,&type,sizeof(int));
    recv_loop(sfd,buf,datalen);
    off_t FileSize,LoadSize=0;
    recv_loop(sfd,&datalen,sizeof(int));
    recv_loop(sfd,&type,sizeof(int));
    recv_loop(sfd,&FileSize,datalen);
    if(-1==(fd=open(buf,O_WRONLY|O_CREAT,0666))){perror("open");return -1;}
    
    //time_t start=time(NULL),now;
    //now=start;

    off_t fileslice=FileSize*0.0001;
    off_t prefilesize=0;
    if(1==type)
    {
        while(1)
        {
            if(-1==recv_loop(sfd,&datalen,sizeof(int)))
            {printf("server crash\n"); close(sfd);return 0;}
            recv_loop(sfd,&type,sizeof(int));
            if(datalen>0)
            {
                recv_loop(sfd,buf,datalen);
                write(fd,buf,datalen);
                LoadSize+=datalen;
                if(LoadSize-prefilesize>fileslice)
                {
                    printf("%5.2f%%\r",(double)LoadSize/FileSize*100);
                    fflush(stdout);
                    prefilesize=LoadSize;
                }
                //now=time(NULL);
                //if(now-start>0)
                //{
                //    printf("%5.2f%%\r",(float)LoadSize/FileSize*100);
                //    fflush(stdout);
                //    start=now;
                //}
            }else{
                printf("100.00%%\n");
                close(fd);
                printf("recv success\n");
                break;
            }
        }
    }
    //int epfd=epoll_create(1);
    //struct epoll_event event,evs[2];
    //event.events=EPOLLIN;
    //event.data.fd=STDIN_FILENO;
    //ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    //if(-1==ret){perror("epoll_ctl");exit(-1);}
    //event.data.fd=sfd;
    //ret=epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);
    //if(-1==ret){perror("epoll_ctl");exit(-1);}
    //while(1)
    //{
    //    memset(evs,0,sizeof(evs));
    //    ready=epoll_wait(epfd,evs,2,-1);
    //    for(i=0;i<ready;i++)
    //    {
    //        if(sfd==evs[i].data.fd)
    //        {
    //            memset(buf,0,sizeof(buf));
    //            ret=recv(sfd,buf,sizeof(buf)-1,0);
    //            if(0==ret)
    //            {
    //                printf("server disconnect\n");
    //                close(sfd);
    //                exit(0);
    //            }
    //            printf("%s--froms server\n",buf);//already have \n in sfd cache.
    //        }else if(STDIN_FILENO==evs[i].data.fd)
    //        {
    //            memset(buf,0,sizeof(buf));
    //            fgets(buf,sizeof(buf)-1,stdin);
    //            send(sfd,buf,strlen(buf)-1,0);
    //        } else {
    //            continue;
    //        }
    //    }
    //}
    close(sfd);
    return 0;
}
