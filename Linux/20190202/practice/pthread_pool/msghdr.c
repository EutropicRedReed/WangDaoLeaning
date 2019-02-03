#include <func.h>

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



int main()
{
    int fds[2];
    socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
    if(!fork())
    {
        close(fds[1]);
        int fd;
        recv_fd(fds[0],&fd);
        char buf[128]={0};
        read(fd,buf,sizeof(buf));
        puts(buf);
        exit(0);
    }else{
        close(fds[0]);
        int fd=open("file",O_RDWR);
        send_fd(fds[1],fd);
        wait(NULL);
    }
    return 0;
}

