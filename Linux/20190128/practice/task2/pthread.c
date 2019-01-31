#include <func.h>
void* pthreadfunc(void *p)
{
    printf("I am child thread,i got a number:%ld\n",(long)p);
    pthread_exit((void*)2);
}

int main()
{
    pthread_t threadid;
    int ret;
    ret=pthread_create(&threadid,NULL,pthreadfunc,(void*)1);
    if(ret!=0)
    {
        printf("pthread_create failed err code=%d\n",ret);
        return -1;
    }
    long lret;
    ret=pthread_join(threadid,(void**)&lret);
    if(ret!=0)
    {
        printf("pthread_join failed err code=%d\n",ret);
        return -1;
    }
    printf("I am main thread,i got a number:%ld\n",lret);
    return 0;
}

