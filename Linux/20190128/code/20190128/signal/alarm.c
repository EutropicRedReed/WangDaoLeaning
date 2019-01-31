#include <func.h>
void sigfunc(int signum)
{
}
int main()
{
    signal(SIGALRM,sigfunc);
    alarm(3);
    sleep(1000); 
    return 0;
}

