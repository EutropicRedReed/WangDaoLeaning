#include <func.h>

int main()
{
    int ret;
    signal(SIGINT,SIG_IGN);
    printf("sigprocmask block success\n");//关键代码
    sleep(3);
    signal(SIGINT,SIG_DFL);
    return 0;
}

