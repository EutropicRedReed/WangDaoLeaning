#include <func.h>

void* pthreadfunc(void *p)
{
    char *pchild=(char*)p;
    printf("I am child thread,%s\n",pchild);
    strcpy(pchild,"world");
}

int main()
{
    pthread_t threadid;
    int ret;
    char *p=(char*)malloc(20);
    strcpy(p,"hello");
    ret=pthread_create(&threadid,NULL,pthreadfunc,p);
    if(ret!=0)
    {
        printf("pthread_create failed err code=%d\n",ret);
        return -1;
    }
    sleep(1);
    printf("I am main thread %s\n",p);
    return 0;
}

