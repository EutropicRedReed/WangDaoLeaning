#include <func.h>
void* pthreadfunc(void *p)
{
    printf("I am child thread\n");
    p=malloc(20);
    strcpy((char*)p,"hello");
    return p;
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
    void *pret;
    ret=pthread_join(threadid,&pret);
    if(ret!=0)
    {
        printf("pthread_join failed err code=%d\n",ret);
        return -1;
    }
    printf("I am main thread,%s\n",(char*)pret);
    return 0;
}

