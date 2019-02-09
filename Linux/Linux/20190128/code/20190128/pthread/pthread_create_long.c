#include <func.h>

void* pthreadfunc(void *p)
{
    printf("I am child thread, %ld\n",(long)p);
}

int main()
{
    pthread_t threadid,threadid1;
    int ret;
    ret=pthread_create(&threadid,NULL,pthreadfunc,(void*)1);
    if(ret!=0)
    {
        printf("pthread_create failed err code=%d\n",ret);
        return -1;
    }
    ret=pthread_create(&threadid1,NULL,pthreadfunc,(void*)2);
    sleep(1);
    printf("I am main thread\n");
    return 0;
}

