#include <func.h>

int main()
{
    struct itimerval t;
    memset(&t,0,sizeof(t));
    getitimer(ITIMER_REAL,&t);
    printf("%ld-%ld",t.it_interval.tv_sec,t.it_interval.tv_usec);
    printf("%ld-%ld",t.it_value.tv_sec,t.it_value.tv_usec);
    return 0;
}

