#include <func.h>
#define N 10000000
typedef struct{
    pthread_mutex_t mutex;
    long tickets;
}thData;
void* threadfunc1(void *p)
{
    thData *p1=(thData*)p;
    while(1)
    {
        pthread_mutex_lock(&p1->mutex);
        if(p1->tickets>0)
        {
            printf("I am windows1,I will sale tickets %ld\n",p1->tickets);
            p1->tickets--;
            printf("I am windows1,sale ok %ld\n",p1->tickets);
            pthread_mutex_unlock(&p1->mutex);
        }else{
            pthread_mutex_unlock(&p1->mutex);
            break;
        }
    }
}
void* threadfunc2(void *p)
{
    thData *p1=(thData*)p;
    while(1)
    {
        pthread_mutex_lock(&p1->mutex);
        if(p1->tickets>0)
        {
            printf("I am windows2,I will sale tickets %ld\n",p1->tickets);
            p1->tickets--;
            printf("I am windows2,sale ok %ld\n",p1->tickets);
            pthread_mutex_unlock(&p1->mutex);
        }else{
            pthread_mutex_unlock(&p1->mutex);
            break;
        }
    }
}

int main()
{
    thData threadinfo; 
    int ret;
    ret=pthread_mutex_init(&threadinfo.mutex,NULL);
    if(ret!=0)
    {
        printf("pthread_mutex_init failed ret=%d\n",ret);
        return -1;
    }
    pthread_t pthid1,pthid2;
    threadinfo.tickets=50;
    pthread_create(&pthid1,NULL,threadfunc1,&threadinfo);
    pthread_create(&pthid2,NULL,threadfunc2,&threadinfo);
    pthread_join(pthid1,NULL);
    pthread_join(pthid2,NULL);
    return 0;
}

