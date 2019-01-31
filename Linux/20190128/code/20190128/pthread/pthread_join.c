#include <func.h>
void print()
{
    pthread_exit(NULL);
}
void* pthreadfunc(void *p)
{
    printf("I am child thread\n");
    print();
    printf("after print,I am child thread\n");
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
    pthread_join(threadid,NULL);
    printf("I am main thread\n");
    return 0;
}

