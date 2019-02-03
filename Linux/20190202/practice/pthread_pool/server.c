#include <func.h>

typedef struct{
    pid_t pid;
    int fds;
    unsigned int busy; // 1 busy ; 0 leisure
}proData;


int tcp_init(const char*,const char*);   
int tcp_accept(int sfd);                 
int tcp_connect(const char*,int);
void signalhandler(void);                
int send_fd(int,int);
int recv_fd(int,int*);
int create_sleep_child(proData*,int);
void child_handle(int);


int main(int argc,char *argv[])
{
    if(4!=argc){
        printf("./server ip port pro_num\n");
        return -1;
    }
    int pro_num=atoi(argv[3]);
    proData *cp=(proData*)calloc(pro_num,sizeof(proData));
    if(-1==create_sleep_child(cp,pro_num)){printf("fork");return -1;}   //creat pro_num process sleep

    int socketfd;
    socketfd=tcp_init(argv[1],argv[2]);

    struct epoll_event event,*evs;
    evs=(struct epoll_event*)calloc(pro_num+1,sizeof(struct epoll_event));
    int epfd=epoll_create(1);
    event.events=EPOLLIN;
    event.data.fd=socketfd;
    epoll_ctl(epfd,EPOLL_CTL_ADD,socketfd,&event);

    int i;
    for(i=0;i<pro_num;i++)
    {
        event.data.fd=cp[i].fds;
        epoll_ctl(epfd,EPOLL_CTL_ADD,cp[i].fds,&event);
    }
    int j,value,new_fd;
    char flag;
    while(1)
    {
        memset(evs,0,(pro_num+1)*sizeof(struct epoll_event));
        value=epoll_wait(epfd,evs,pro_num+1,-1);    //client and child process.
        for(i=0;i<value;i++)
        {
            if(socketfd==evs[i].data.fd)
            {
                new_fd=tcp_accept(socketfd);    //accpet client connect request.
                for(j=0;j<pro_num;j++)
                {
                    if(0==cp->busy)
                    {
                        send_fd(cp[i].fds,new_fd);
                        close(new_fd);  //have two reference counts
                        cp[i].busy=1;
                        break;
                    }
                }
            }
            for(j=0;j<pro_num;j++)
            {
                if(cp[j].fds==evs[i].data.fd)
                {
                    cp[j].busy=0;
                    read(cp[i].fds,&flag,sizeof(char));
                    printf("NO.%d process is leisure\n",i+1);
                }
            }
        }
    }
    return 0;
}

int create_sleep_child(proData* cp,int pro_num)
{
    int i;
    pid_t pid;
    int fds[2];
    for(i=0;i<pro_num;i++)
    {
        socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
        pid=fork();
        if(!pid)
        {
            close(fds[1]); //close write
            child_handle(fds[0]);
        }else if(pid>0){
            close(fds[0]);  //close read
            cp[i].pid=pid;
            cp[i].fds=fds[1];
        }else if(-1==pid)
        {
            return -1;
        }
    }
    return 0;
}

void child_handle(int fds)
{
    int new_fd;
    char flag=1;
    while(1)
    {
        recv_fd(fds,&new_fd);
        printf("start server\n");
        close(new_fd);
        write(fds,&flag,sizeof(char));
    }
}



int tcp_init(const char* ip,const char* port)
{
    int sfd = socket(AF_INET,SOCK_STREAM,0);
    if(sfd==-1)
    {
        perror("socket");
        exit(-1);
    }
    int reuse=1;
    setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
    struct sockaddr_in serveraddr;
    memset(&serveraddr,0,sizeof(struct sockaddr_in));
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(atoi(port));
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

int send_fd(int fds,int fd)
{
    char buf1[10]="hello";
    char buf2[10]="world";
    struct iovec inv[2];
    inv[0].iov_base=buf1;
    inv[0].iov_len=sizeof(buf1);
    inv[1].iov_base=buf2;
    inv[1].iov_len=sizeof(buf2);
    struct msghdr msg;
    memset(&msg,0,sizeof(struct msghdr));
    msg.msg_iov=inv;
    msg.msg_iovlen=2;
    struct cmsghdr *cmsg;
    int len=CMSG_LEN(sizeof(int));
    cmsg=(struct cmsghdr*)calloc(1,len);
    cmsg->cmsg_len=len;
    cmsg->cmsg_level=SOL_SOCKET;
    cmsg->cmsg_type=SCM_RIGHTS;
    *(int*)CMSG_DATA(cmsg)=fd;
    msg.msg_control=cmsg;
    msg.msg_controllen=len;
    if(-1==sendmsg(fds,&msg,0)){perror("sendmsg");return -1;}
    return 0;
}
int recv_fd(int fds,int *fd)    //fd is Value-result paramete.
{
    char buf1[10]={0};
    char buf2[10]={0};
    struct iovec inv[2];    //man readv/writev
    inv[0].iov_base=buf1;
    inv[0].iov_len=sizeof(buf1);
    inv[1].iov_base=buf2;
    inv[1].iov_len=sizeof(buf2);
    struct msghdr msg;
    memset(&msg,0,sizeof(struct msghdr));
    msg.msg_iov=inv;
    msg.msg_iovlen=2;
    struct cmsghdr *cmsg;
    int len=CMSG_LEN(sizeof(int));
    cmsg=(struct cmsghdr*)calloc(1,len);
    cmsg->cmsg_len=len;
    cmsg->cmsg_level=SOL_SOCKET;
    cmsg->cmsg_type=SCM_RIGHTS;
    msg.msg_control=cmsg;
    msg.msg_controllen=len;
    if(-1==recvmsg(fds,&msg,0)){perror("recvmsg");return -1;}
    *fd=*(int*)CMSG_DATA(cmsg);
    return 0;
}
