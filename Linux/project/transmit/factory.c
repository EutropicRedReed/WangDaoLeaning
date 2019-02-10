#include "factory.h"

void factoryInit(pFactory pf,threadfunc_t threadfunc)
{
    memset(pf,0,sizeof(Factory));
    pf->pthid=(pthread_t*)calloc(THREAD_NUM_,sizeof(pthread_t));
    pf->threadNum=THREAD_NUM_;
    pf->que.queCapacity=CAPACITY_;
    pthread_mutex_init(&pf->que.queMutex,NULL);
    pthread_cond_init(&pf->cond,NULL);
    pf->downFileFunc=threadfunc;
    return;
}

void factoryStart(pFactory pf)
{
    int i;
    if(0==pf->startFlag)
    {
        for(i=0;i<pf->threadNum;i++)
        {
            pthread_create(pf->pthid+i,NULL,pf->downFileFunc,pf);
        }
        pf->startFlag=1;
    }
}

