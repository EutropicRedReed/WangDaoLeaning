#include <func.h>
void sigfunc(int signum,siginfo_t *p,void *p1)
{
    printf("%d is coming\n",signum);
}
int main()
{
    struct sigaction act;
    memset(&act,0,sizeof(act));
    act.sa_sigaction=sigfunc; 
    act.sa_flags=SA_SIGINFO|SA_RESTART;
    int ret;
    ret=sigaction(SIGINT,&act,NULL);
    if(-1==ret)
    {
        perror("sigaction");
        return -1;
    }
    char buf[128]={0}; 
    ret=read(0,buf,sizeof(buf));
    printf("ret=%d,buf=%s\n",ret,buf);
    return 0;
}

