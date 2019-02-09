#include <func.h>


int main()
{
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset,SIGINT);
    if(-1==sigprocmask(SIG_BLOCK,&sigset,NULL))
    {
        perror("sigprocmask");
        return -1;
    }
    printf("\tbefore\n");
    sleep(5);
    sigset_t pending;
    sigemptyset(&pending);
    sigpending(&pending);
    if(sigismember(&pending,SIGINT))
    {
        printf("\tSIGINT is pending\n");
    }else{
        printf("\tno signal pending\n");
    }
    printf("\tafter\n");
    sigprocmask(SIG_UNBLOCK,&sigset,NULL);
    printf("\tif SIGINT is pending,you can't see it!\n");
    return 0;
}

