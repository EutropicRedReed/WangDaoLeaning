#include <func.h>

int main(int argc,char *argv[])
{
    args_check(argc,2);
    int sfd=socket(AF_INET,SOCK_DGRAM,0);
    if(-1==sfd){perror("socket");exit(-1);}
    struct sockaddr_in seraddr;
    bzero(&seraddr,sizeof(seraddr));    //bzero just like memset 
    seraddr.sin_family=AF_INET;
    seraddr.sin_port=htons(atoi(argv[1]));
    seraddr.sin_addr.s_addr=INADDR_ANY;
    if(-1==bind(sfd,(struct sockaddr*)&seraddr,sizeof(struct sockaddr)))
    {
        perror("bind");
        close(sfd);
        exit(-1);
    }
    fd_set rdset;
    char buf[128]={0};
    int ret=0;
    struct sockaddr_in fromaddr;
    while(1)
    {
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(sfd,&rdset);
        ret=select(sfd+1,&rdset,NULL,NULL,NULL);
        if(ret>0)
        {
            if(FD_ISSET(STDIN_FILENO,&rdset))
            {
                bzero(buf,sizeof(buf));
                fgets(buf,sizeof(buf),stdin);
                sendto(sfd,buf,strlen(buf)-1,0,\
                       (struct sockaddr*)&fromaddr,sizeof(struct sockaddr));
            }
            if(FD_ISSET(sfd,&rdset))
            {
                bzero(&fromaddr,sizeof(fromaddr));
                bzero(buf,sizeof(buf));
                socklen_t fromaddrlen=sizeof(struct sockaddr);
                if(-1==recvfrom(sfd,buf,sizeof(buf),0,\
                                (struct sockaddr*)&fromaddr, &fromaddrlen))
                {
                    perror("recvfrom");
                    close(sfd);
                    exit(-1);
                }
                printf("receive from %s %d,message is %s\n",\
                       inet_ntoa(fromaddr.sin_addr),ntohs(fromaddr.sin_port),\
                       buf);
            }
        }
    }
    close(sfd);
    return 0;
}

