#include <func.h>
void* pthreadfunc(void *p)
{
    sleep(5);
    printf("I am child thread\n");
    return NULL;
}

int main()
{
    pthread_t threadid;
    int ret;
    ret=pthread_create(&threadid,NULL,pthreadfunc,NULL);
    if(ret!=0)
    {
        printf("pthread_create failed err code=%d\n",ret);
        return -1;
    }
    printf("I am main thread\n");
    long lret;
    pthread_cancel(threadid);
    pthread_join(threadid,(void**)&lret);
    printf("thread ret=%ld\n",lret);
    return 0;
}

