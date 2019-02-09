#include <func.h> 
void sigfunc(int signum,siginfo_t *pinfo,void *preserved)
{
    printf("before %d\n",signum);
    sleep(2);
    printf("after %d\n",signum);
}

int main()
{
    struct sigaction act;
    act.sa_flags=SA_NODEFER|SA_SIGINFO;
    act.sa_sigaction=sigfunc;
    sigaction(SIGINT,&act,NULL);
    while(1);
    return 0;
}

