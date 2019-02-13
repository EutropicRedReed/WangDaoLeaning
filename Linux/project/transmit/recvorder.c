#include "factory.h"

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
            fprintf(stdout,"%d:%s%s\n",fd,"cd ",buf);
            if(-1==my_chdir(buf,fd))
            {
                datalen=-1;
                send_n(fd,&datalen,sizeof(int));
            }
            break;
        case 2:
            fprintf(stdout,"%d:%s%s\n",fd,"ls ",buf);
            if(-1==my_ls(buf,fd))
            {
                datalen=-1;
                send_n(fd,&datalen,sizeof(int));
            }
            break;
        case 3:
            fprintf(stdout,"%d:%s%s\n",fd,"rm ",buf);
            if(-1==my_rm(buf,fd))
            {
                datalen=-1;
                send_n(fd,&datalen,sizeof(int));
            }
            break;
        case 4:
            printf("%d:%s\n",fd,"pwd ");
            my_pwd(fd);
            break;
        case 5:
            fprintf(stdout,"%d:%s%s\n",fd,"gets ",buf);
            if(-1==tranFile(fd,buf))
            {
                datalen=-1;
                send_n(fd,&datalen,sizeof(int));
            }
            break;
        case 6:
            fprintf(stdout,"%d:%s%s\n",fd,"puts ",buf);
            if(-1==uploadFile(fd))
            {
                datalen=-1;
                send_n(fd,&datalen,sizeof(int));
            }
            break;
        case 7:
            printf("%d:disconnect\n",fd);
            Tmp_Fd_Acci tfa;
            tfa.fd=fd;
            deletemysqltablethree(&tfa);
            close(fd);
            break;
        default :
            break;
        }
    }
    return 0;
}

