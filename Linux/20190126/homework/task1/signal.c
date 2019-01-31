#include <func.h>
void sigfunc(int signum)
{
    printf("before %d\n",signum);
    sleep(2);
    printf("after %d\n",signum);
}
int main()
{
    signal(SIGINT,sigfunc);
    signal(SIGQUIT,sigfunc);
    while(1);
    return 0;
}

