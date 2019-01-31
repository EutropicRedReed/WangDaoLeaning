#include <func.h>

int main()
{
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask,SIGINT);
    int ret;
    ret=sigprocmask(SIG_BLOCK,&mask,NULL);
    if(-1==ret)
    {
        perror("sigprocmask");
        return -1;
    }
    printf("sigprocmask block success\n");//关键代码
    sleep(3);
    sigset_t pend;
    sigemptyset(&pend);
    sigpending(&pend);
    if(sigismember(&pend,SIGINT))
    {
        printf("SIGINT have come\n");
    }else{
        printf("SIGINT don't come\n");
    }
    sigprocmask(SIG_UNBLOCK,&mask,NULL);
    return 0;
}

