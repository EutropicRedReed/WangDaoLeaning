#include "factory.h"

int send_n(int sfd,void* p,int len)
{
    LOG_REDIRECT_
    char *ptran=(char*)p;
    int total=0;
    int ret;
    while(total<len)
    {
        ret=send(sfd,ptran+total,len-total,0);
        if(-1==ret)
        {
            return -1;
        }
        total+=ret;
    }
    return 0;
}
int recv_n(int sfd,void* p,int len)
{
    LOG_REDIRECT_
    char *ptran=(char*)p;
    int total=0;
    int ret;
    while(total<len)
    {
        ret=recv(sfd,ptran+total,len-total,0);
        total+=ret;
    }
    return 0;
}
