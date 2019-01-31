#include <func.h>

void *pthfunc1(void*);
void *pthfunc2(void*);
void *pthfunc3(void*);

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    long tickets;
}Info;

int main()
{
    pthread_t ptid1,ptid2,ptid3;
    Info *p=(Info*)calloc(1,sizeof(Info));
    p->tickets=20;
    pthread_mutex_init(&p->mutex,NULL);
    pthread_cond_init(&p->cond,NULL);

    pthread_create(&ptid1,NULL,pthfunc1,p);
    pthread_create(&ptid2,NULL,pthfunc2,p);
    pthread_create(&ptid3,NULL,pthfunc3,p);

    pthread_join(ptid1,NULL);
    pthread_join(ptid2,NULL);
    pthread_join(ptid3,NULL);

    free(p);
    p=NULL;
    return 0;
}

void *pthfunc1(void *p1)
{
    Info *p= (Info*)p1;
    int i=0;
    while(1)
    {
        pthread_mutex_lock(&p->mutex);
        if(p->tickets>0)
        {
            p->tickets--;
            i++;
            if(0==p->tickets)
            {
                pthread_cond_signal(&p->cond); 
            } 
            printf("Store 1 sell one left %ld\n",p->tickets);
        }else{
            pthread_mutex_unlock(&p->mutex);
            printf("Store 1 total sell %d\n",i);
            break;
        }
        pthread_mutex_unlock(&p->mutex);
        sleep(1);
    }
    pthread_exit(NULL);
}

void *pthfunc2(void *p2)
{
    Info *p=(Info*)p2;
    int i=0;
    while(1)
    {
        pthread_mutex_lock(&p->mutex);
        if(p->tickets>0)
        {
            p->tickets--;
            i++;
            if(0==p->tickets)
            {
                pthread_cond_signal(&p->cond);
            }
            printf("Store 2 sell one left %ld\n",p->tickets);
        }else{
            pthread_mutex_unlock(&p->mutex);
            printf("Store 2 total sell %d\n",i);
            break;
        }
        pthread_mutex_unlock(&p->mutex);
        sleep(1);
    }
    pthread_exit(NULL);
}

void *pthfunc3(void *p3)
{
    Info *p=(Info*)p3;
    pthread_mutex_lock(&p->mutex);
    if(p->tickets>0)
        pthread_cond_wait(&p->cond,&p->mutex);
    p->tickets=10;
    pthread_mutex_unlock(&p->mutex);
    printf("Store 3 provide tick %ld\n",p->tickets);
    pthread_exit(NULL);
}
