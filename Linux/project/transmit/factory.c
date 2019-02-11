#include "factory.h"

void factoryInit(pFactory pf,threadfunc_t threadfunc)
{
    int i;
    memset(pf,0,sizeof(Factory));
    pf->pthid=(pthread_t*)calloc(THREAD_NUM_,sizeof(pthread_t));
    pf->que=(pQue_t)calloc(CAPACITY_,sizeof(Que_t));
    pf->Flag=(short*)calloc(1,sizeof(short));
    *pf->Flag=-1;
    for(i=0;i<CAPACITY_;i++)
    {
        pf->que[i].queCapacity=CAPACITY_;
    }
    pf->threadNum=THREAD_NUM_;
    pthread_mutex_init(&pf->que->queMutex,NULL);
    pthread_cond_init(&pf->cond,NULL);
    pf->downFileFunc=threadfunc;
    return;
}

void factoryStart(pFactory pf)
{
    int i;
    if(-1==*pf->Flag)
    {
        for(i=0;i<pf->threadNum;i++)
        {
            pthread_create(pf->pthid+i,NULL,pf->downFileFunc,pf);
        }
        *pf->Flag=0;
    }
}

