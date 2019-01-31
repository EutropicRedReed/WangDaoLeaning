#include <func.h>
void sigfunc(int signum)
{
    printf("signal is coming\n");
}
int main()
{
    signal(SIGINT,sigfunc);
    printf("Hello world\n");
    char buf[128]={0}; 
    read(0,buf,sizeof(buf));
    printf("buf=%s\n",buf);
    return 0;
}
