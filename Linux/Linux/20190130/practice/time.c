#include <func.h>

void *pthfunc(void *p)
{
    time_t childt=time(NULL);
    struct tm t;
    gmtime_r(&childt,&t);
    printf("%04d-%02d-%02d %02d:%02d:%02d\n",t.tm_year+1900,\
           t.tm_mon+1,t.tm_mday,t.tm_hour+8,t.tm_min,t.tm_sec);
    sleep(5);
    childt=time(NULL);
    gmtime_r(&childt,&t);
    printf("%04d-%02d-%02d %02d:%02d:%02d\n",t.tm_year+1900,\
           t.tm_mon+1,t.tm_mday,t.tm_hour+8,t.tm_min,t.tm_sec);
    pthread_exit(NULL);

}

int main()
{
    pthread_t pthid;
    pthread_create(&pthid,NULL,pthfunc,NULL);
    sleep(2);
    time_t maint=time(NULL);
    struct tm t;
    gmtime_r(&maint,&t);
    printf("%04d-%02d-%02d %02d:%02d:%02d\n",t.tm_year+1900,\
           t.tm_mon+1,t.tm_mday,t.tm_hour+8,t.tm_min,t.tm_sec);
    pthread_join(pthid,NULL);
    return 0;
}

