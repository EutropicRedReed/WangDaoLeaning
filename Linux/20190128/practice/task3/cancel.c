#include <func.h>
void *pthreadfunc(void *p)
{
    printf("*.*\ninput number is:%ld\n",(long)p);
    pthread_exit((void*)0);
}
int main()
{
    pthread_t pthreadid;
    pthread_create(&pthreadid,NULL,pthreadfunc,(void*)1);
    long ret;
    pthread_join(pthreadid,(void**)&ret);
    printf("return value is:%ld\n",ret);
    return 0;
}

