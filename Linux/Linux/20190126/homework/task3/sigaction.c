#include <func.h> 
void sigfunc(int signum,siginfo_t *pinfo,void *preserved)
{
    printf("before %d\n",signum);
    sleep(2);
    sigset_t pending;
    sigpending(&pending);
    if(sigismember(&pending,SIGQUIT))
    {
        printf("SIGQUIT is pending\n");
    }else{
        printf("SIGQUIT is not pending\n");
    }
    printf("after %d\n",signum);
}

int main()
{
    struct sigaction act;
    act.sa_flags=SA_SIGINFO;
    act.sa_sigaction=sigfunc;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask,SIGQUIT);
    sigaction(SIGINT,&act,NULL);
    sigaction(SIGQUIT,&act,NULL);
    while(1);
    return 0;
}

