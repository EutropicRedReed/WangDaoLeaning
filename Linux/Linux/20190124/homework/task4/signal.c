#include <func.h>

void sigfunc2(int signum)
{
    printf("\tNo.%d\tstart\n",signum);
    sleep(2);
    printf("\tNo.%d\tend\n",signum);
}
void sigfunc3(int signum)
{
    printf("\tNo.%d\tstart\n",signum);
    sleep(2);
    printf("\tNo.%d\tend\n",signum);
}

int main()
{
    signal(SIGINT,sigfunc2);
    signal(SIGQUIT,sigfunc3);
    while(1);
    return 0;
}

