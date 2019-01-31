#include <func.h>

void* pthreadfunc(void *p)
{
    int *pchild=(int*)p;
    *pchild=5;
    printf("I am child thread, %d\n",*pchild);
}

int main()
{
    pthread_t threadid,threadid1;
    int ret;
    int iArg=10;
    ret=pthread_create(&threadid,NULL,pthreadfunc,&iArg);
    if(ret!=0)
    {
        printf("pthread_create failed err code=%d\n",ret);
        return -1;
    }
    sleep(1);
    printf("I am main thread,iArg=%d\n",iArg);
    return 0;
}

