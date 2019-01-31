#include <func.h>
int g_Num=10;
void* pthreadfunc(void *p)
{
    printf("I am child thread,g_Num=%d\n",g_Num);
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
    g_Num=5;
    sleep(1);
    printf("I am main thread\n");
    return 0;
}

