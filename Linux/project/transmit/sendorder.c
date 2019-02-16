#include "factory.h"
int sendorder(int socketfd)
{
    LOG_REDIRECT_
    int datalen;
    char buf[MAX_BUF_SIZE]={0};
    while(1)
    {
        memset(buf,0,sizeof(buf));
        int i=0;
        char temp[MAX_BUF_SIZE]={0};
        short type;
        read(STDIN_FILENO,buf,sizeof(buf));
        i=strlen(buf);
        buf[i-1]=0;
        i=0;
        while(buf[i]!=EOF)
        {
            if(buf[i]!=' '&&buf[i]!=0)
            {
                i++;
            }else{  // find first word.
                strncpy(temp,buf,i);
                if(!strcmp(temp,"cd"))
                {
                    type=1;
                    while(buf[++i]==' ');   // ignore blank.
                    strncpy(temp,buf+i,MAX_BUF_SIZE-i);
                    datalen=strlen(temp);
                    if(-1==send_n(socketfd,&datalen,sizeof(int)))
                    {close(socketfd);printf("server close\n");return -1;}
                    if(-1==send_n(socketfd,&type,sizeof(short)))
                    {close(socketfd);printf("server close\n");return -1;}
                    if(-1==send_n(socketfd,temp,datalen))
                    {close(socketfd);printf("server close\n");return -1;}

                    if(-1==recv_n(socketfd,&datalen,sizeof(int)))
                    {close(socketfd);printf("server close\n");return -1;}
                    if(-1==recv_n(socketfd,buf,datalen))
                    {close(socketfd);printf("server close\n");return -1;}
                    printf("%s",buf);
                    fflush(stdout);
                    break;
                    
                }else if(!strcmp(temp,"ls"))
                {
                    type=2;
                    while(buf[++i]==' ');
                    strncpy(temp,buf+i,MAX_BUF_SIZE-i);
                    if(0==(datalen=strlen(temp)))
                    {
                        strcpy(temp,".");
                        datalen=strlen(temp);
                        if(-1==send_n(socketfd,&datalen,sizeof(int)))
                        {close(socketfd);printf("server close\n");return -1;}
                        if(-1==send_n(socketfd,&type,sizeof(short)))
                        {close(socketfd);printf("server close\n");return -1;}
                        if(-1==send_n(socketfd,temp,datalen))
                        {close(socketfd);printf("server close\n");return -1;}
                    }else{
                        if(-1==send_n(socketfd,&datalen,sizeof(int)))
                        {close(socketfd);printf("server close\n");return -1;}
                        if(-1==send_n(socketfd,&type,sizeof(short)))
                        {close(socketfd);printf("server close\n");return -1;}
                        if(-1==send_n(socketfd,temp,datalen))
                        {close(socketfd);printf("server close\n");return -1;}
                    }

                    if(-1==recv_n(socketfd,&datalen,sizeof(int)))
                    {close(socketfd);printf("server close\n");return -1;}
                    if(-1==recv_n(socketfd,buf,datalen))
                    {close(socketfd);printf("server close\n");return -1;}
                    printf("%s",buf);
                    fflush(stdout);
                    break;
                }else if(!strcmp(temp,"remove"))
                {
                    type=3;
                    while(buf[++i]==' ');
                    strncpy(temp,buf+i,MAX_BUF_SIZE-i);
                    datalen=strlen(temp);
                    if(-1==send_n(socketfd,&datalen,sizeof(int)))
                    {close(socketfd);printf("server close\n");return -1;}
                    if(-1==send_n(socketfd,&type,sizeof(short)))
                    {close(socketfd);printf("server close\n");return -1;}
                    if(-1==send_n(socketfd,temp,datalen))
                    {close(socketfd);printf("server close\n");return -1;}

                    if(-1==recv_n(socketfd,&datalen,sizeof(int)))
                    {close(socketfd);printf("server close\n");return -1;}
                    if(-1==recv_n(socketfd,buf,datalen))
                    {close(socketfd);printf("server close\n");return -1;}
                    printf("%s",buf);
                    fflush(stdout);
                    break;
                }else if(!strcmp(temp,"pwd"))
                {
                    type=4;
                    strcpy(temp,".");
                    datalen=strlen(temp);
                    if(-1==send_n(socketfd,&datalen,sizeof(int)))
                    {close(socketfd);printf("server close\n");return -1;}
                    if(-1==send_n(socketfd,&type,sizeof(short)))
                    {close(socketfd);printf("server close\n");return -1;}
                    if(-1==send_n(socketfd,temp,datalen))
                    {close(socketfd);printf("server close\n");return -1;}

                    if(-1==recv_n(socketfd,&datalen,sizeof(int)))
                    {close(socketfd);printf("server close\n");return -1;}
                    if(-1==recv_n(socketfd,buf,datalen))
                    {close(socketfd);printf("server close\n");return -1;}
                    printf("%s",buf);
                    fflush(stdout);
                    break;
                }else if(!strcmp(temp,"gets"))
                {
                    type=5;
                    while(buf[++i]==' ');
                    strncpy(temp,buf+i,MAX_BUF_SIZE-i);
                    datalen=strlen(temp);
                    if(-1==send_n(socketfd,&datalen,sizeof(int)))
                    {close(socketfd);printf("server close\n");return -1;}
                    if(-1==send_n(socketfd,&type,sizeof(short)))
                    {close(socketfd);printf("server close\n");return -1;}
                    if(-1==send_n(socketfd,temp,datalen))
                    {close(socketfd);printf("server close\n");return -1;}
                    uploadFile(socketfd);
                    break;
                }else if(!strcmp(temp,"puts"))
                {
                    type=6;
                    while(buf[++i]==' ');
                    strncpy(temp,buf+i,MAX_BUF_SIZE-i);
                    datalen=strlen(temp);
                    if(-1==send_n(socketfd,&datalen,sizeof(int)))
                    {close(socketfd);printf("server close\n");return -1;}
                    if(-1==send_n(socketfd,&type,sizeof(short)))
                    {close(socketfd);printf("server close\n");return -1;}
                    if(-1==send_n(socketfd,temp,datalen))
                    {close(socketfd);printf("server close\n");return -1;}
                    tranFile(socketfd,temp);    // begin upload file.
                    break;
                }else if(!strcmp(temp,"exit"))
                {
                    type=7;
                    datalen=strlen(temp);
                    if(-1==send_n(socketfd,&datalen,sizeof(int)))
                    {close(socketfd);printf("server close\n");return -1;}
                    if(-1==send_n(socketfd,&type,sizeof(short)))
                    {close(socketfd);printf("server close\n");return -1;}
                    if(-1==send_n(socketfd,temp,datalen))
                    {close(socketfd);printf("server close\n");return -1;}
                    close(socketfd);
                    printf("disconnect\n");
                    return 0;
                }else{  
                    printf("invalid order\n");
                    break;
                }
            }
        }
    }
    close(socketfd);
    return 0;
}

