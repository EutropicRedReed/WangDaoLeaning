/*****************************************************************************
Copyright: 1988-1999, H  Tech. Co., Ltd.
File name: ftp_tcp_server
Description: 用于详细说明此程序文件完成的主要功能，与其他模块或函数的接口，输出值、取值范围、含义及参数间的控制、顺序、独立或依赖等关系
Author: zhangyi
Version: 3
Date: 2019-02-11
History: 修改历史记录列表，每条修改记录应包括修改日期、修改者及修改内容简述。
*****************************************************************************/

#include "factory.h"
int exitFds[2];
void cleanup(void *p)
{
    pthread_mutex_unlock(&((pQue_t)p)->queMutex);
}
void* threadfunc(void* p)
{
    pFactory pf=(pFactory)p;
    int j=0;
    pthread_mutex_lock(&pf->que->queMutex);
    pQue_t pq=pf->que+*pf->Flag;    // ==pf->que+i
    j=(*pf->Flag)++;
    pthread_mutex_unlock(&pf->que->queMutex);


    pthread_cleanup_push(cleanup,pq);
    pNode_t pcur;
    int ret;
    while(1)
    {
        pthread_mutex_lock(&pq->queMutex);
        if(!pq->queSize)
        {
            pthread_cond_wait(&pf->cond,&pq->queMutex);
        }
        ret=queGet(pq,&pcur);
        pthread_mutex_unlock(&pq->queMutex);
        if(0==ret)
        {
            printf("pthread%d server\tclient:%d\n",j,pcur->ndSocketfd);
            //if send j to recvorder,can (j<<10 | pcur->ndSocketfd)
            //printf("*\n");

            if(0==signinconfirmserver(pcur->ndSocketfd))
            {
                recvorder(pcur->ndSocketfd);    
            }
            
            //printf("**\n");
            free(pcur);
        }
        pcur=NULL;
        // recycling
        //free(pf->Flag);
        //pf->Flag=NULL;
    }
    pthread_cleanup_pop(1);
}
void sigExitFunc(int signum)
{
    write(exitFds[1],&signum,1);
}
int main()
{
    chdir(FILE_STORAGE_PATH_);
    pipe(exitFds);
    if(fork())
    {//父进程
        close(exitFds[0]);
        signal(SIGUSR1,sigExitFunc);
        wait(NULL);
        //recycling f(factory)-->pthid -->que.
        exit(0);
    }
    close(exitFds[1]);
    Factory f;
    //Initialization
    factoryInit(&f,threadfunc);
    factoryStart(&f);
    int socketfd=tcpInit();
    // register events
    int epfd=epoll_create(1);
    struct epoll_event event,evs[2];
    event.events=EPOLLIN;
    event.data.fd=exitFds[0];
    epoll_ctl(epfd,EPOLL_CTL_ADD,exitFds[0],&event);
    event.data.fd=socketfd;
    epoll_ctl(epfd,EPOLL_CTL_ADD,socketfd,&event);

    int new_fd;
    pQue_t pq=f.que;
    pNode_t pnew;
    int fdReadyNum,i;
    int j=0;
    while(1)
    {
        fdReadyNum=epoll_wait(epfd,evs,2,-1);
        for(i=0;i<fdReadyNum;i++)
        {
            if(socketfd==evs[i].data.fd)
            {
                 new_fd=accept(socketfd,NULL,NULL);
                 pnew=(pNode_t)calloc(1,sizeof(Node_t));
                 pnew->ndSocketfd=new_fd;
                 pthread_mutex_lock(&pq->queMutex);
                 queInsert(pq+j++,pnew);
                 pthread_mutex_unlock(&pq->queMutex);
                 if(j>=CAPACITY_)
                 {
                     j=0;
                     pq=f.que;
                 }
                 pthread_cond_signal(&f.cond);
            }
            if(exitFds[0]==evs[i].data.fd)
            {
                close(socketfd);//关闭socket，停止接收请求
                for(i=0;i<f.threadNum;i++)
                {
                    pthread_cancel(f.pthid[i]);
                }
                for(i=0;i<f.threadNum;i++)
                {
                    pthread_join(f.pthid[i],NULL);
                }
                printf("thread_pool exit success\n");
                exit(0);
            }
        }
    }
    return 0;
}

