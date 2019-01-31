#include <func.h>

void* pthreadfunc(void *p)
{
    printf("I am child thread, %d\n",*(int*)p);
}

int main()
{
    pthread_t threadid,threadid1;
    int ret;
    int threadnum=1;
    ret=pthread_create(&threadid,NULL,pthreadfunc,&threadnum);
    if(ret!=0)
    {
        printf("pthread_create failed err code=%d\n",ret);
        return -1;
    }
    threadnum=2;
    ret=pthread_create(&threadid1,NULL,pthreadfunc,&threadnum);
    sleep(1);
    printf("I am main thread\n");
    return 0;
}

