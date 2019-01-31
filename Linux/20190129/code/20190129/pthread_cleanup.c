#include <func.h>

void cleanup(void *p)
    {
   printf("I am cleanup func\n");
}

void* threadfunc(void* p)
{
    pthread_cleanup_push(cleanup,NULL);
    printf("I am child thread\n");
    sleep(2);
    pthread_cleanup_pop(1);
    pthread_exit(NULL);
}
void sigfunc(int signum)
{
    return;
}
int main()
{
    signal(SIGALRM,sigfunc); 
    pthread_t pthid;
    pthread_create(&pthid,NULL,threadfunc,NULL);
    alarm(5);
    pause();
    printf("**\n");
    pthread_cancel(pthid);
    printf("***\n");
    long lret;
    pthread_join(pthid,(void**)&lret);
    printf("main thread %ld\n",lret);
    return 0;
}

