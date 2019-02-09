#include <func.h>
void sigfunc(int signum,siginfo_t *p,void *p1)
{
    printf("%d is coming,send pid=%d,send uid=%d\n",signum,p->si_pid,p->si_uid);
}
int main()
{
    struct sigaction act;
    memset(&act,0,sizeof(act));
    act.sa_sigaction=sigfunc; 
    act.sa_flags=SA_SIGINFO;
    int ret;
    ret=sigaction(SIGINT,&act,NULL);
    if(-1==ret)
    {
        perror("sigaction");
        return -1;
    }
    while(1);
    return 0;
}

