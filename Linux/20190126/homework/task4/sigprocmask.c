#include <func.h>

void sigfunc(int signum,siginfo_t *p,void *p1)
{
    sleep(4);
    printf("\tbefore\n");
    sigset_t pending;
    sigemptyset(&pending);
    sigpending(&pending);
    if(sigismember(&pending,SIGINT)|sigismember(&pending,SIGQUIT))
    {
        printf("\tsignal is peding");
    }
    printf("\tafter\n");
}

int main()
{
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset,SIGINT);
    sigprocmask(SIG_BLOCK,&sigset,NULL);

    struct sigaction act;
    act.sa_sigaction=sigfunc;
    act.sa_flags=SA_SIGINFO;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask,SIGINT);
    sigaction(SIGINT,&act,NULL);
    sigdelset(&act.sa_mask,SIGINT);
    sigaction(SIGQUIT,&act,NULL);
    while(1)
    {
        sleep(1);
        sigprocmask(SIG_UNBLOCK,&sigset,NULL);
    }
    return 0;
}

