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
    sigprocmask(SIG_UNBLOCK,&mask,NULL);
    return 0;
}

