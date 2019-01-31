#include <func.h>
void* pthreadfunc(void *p)
{
    while(1)
    {
        pthread_testcancel();
    }
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
    ret=pthread_cancel(threadid);
    if(ret!=0)
    {
        printf("pthread_cancel failed err code=%d\n",ret);
        return -1;
    }
    pthread_join(threadid,(void**)&lret);
    printf("thread ret=%ld\n",lret);
    return 0;
}

