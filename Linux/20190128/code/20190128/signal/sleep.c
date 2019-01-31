#include <func.h>
void sigfunc(int signum)
{

}
int main()
{
    alarm(3);
    signal(SIGALRM,sigfunc);
    pause();
    return 0;
}

