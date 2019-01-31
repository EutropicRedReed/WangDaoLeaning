#include <func.h>

void sigfunc(int signum)
{
    printf("\t%d\tchange\n",signum);
}

int main()
{
    signal(SIGINT,sigfunc);
    while(1);
    return 0;
}

