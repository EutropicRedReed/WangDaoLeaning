#include <func.h>
//3号信号到来，会打断2号信号的执行
void sigfunc(int signum,siginfo_t *p,void *p1)
{
    printf("before sleep %d is coming\n",signum);
    sleep(3);
    printf("after sleep %d is coming\n",signum);
}
int main()
{
    struct sigaction act;
    memset(&act,0,sizeof(act));
    act.sa_sigaction=sigfunc; 
    act.sa_flags=SA_SIGINFO;
    sigaddset(&act.sa_mask,SIGQUIT);
    int ret;
    ret=sigaction(SIGINT,&act,NULL);
    if(-1==ret)
    {
        perror("sigaction");
        return -1;
    }
    sigaction(SIGQUIT,&act,NULL);
    while(1);
    return 0;
}

