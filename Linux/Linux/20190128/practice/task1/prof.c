#include <func.h>
void sigfunc(int signum)
{
    time_t now;
    now=time(NULL);
    printf("%s\n",ctime(&now));
}

int main()
{
    struct timeval start,end;
    gettimeofday(&start,NULL);
    sigfunc(0);
    signal(SIGPROF,sigfunc);
    struct itimerval t;
    memset(&t,0,sizeof(t));
    t.it_value.tv_sec=3;
    t.it_interval.tv_sec=2;
    //if(-1==setitimer(ITIMER_REAL,&t,NULL))
    //{
    //    perror("setitimer real");
    //    return -1;
    //}
    if(-1==setitimer(ITIMER_PROF,&t,NULL))
    {
        perror("setitimer prof");
        return -1;
    }
    //if(-1==setitimer(ITIMER_VIRTUAL,&t,NULL))
    //{
    //    perror("setitimer virtual");
    //    return -1;
    //}
    sleep(5);
    gettimeofday(&end,NULL);
    printf("total time=%ld,utime=%ld\n",end.tv_sec-start.tv_sec,\
           (end.tv_usec-start.tv_usec));
    while(1);
    return 0;
}

