#include <func.h>
#define N 10000000
int main()
{
    int semArrid=semget(1000,1,IPC_CREAT|0600);
    if(-1==semArrid)
    {
        perror("semget");
        return -1;
    }
    int ret=semctl(semArrid,0,SETVAL,1);
    if(-1==ret)
    {
        perror("semctl");
        return -1;
    }
    int shmid=shmget(1000,4096,IPC_CREAT|0600);
    int *p=(int*)shmat(shmid,NULL,0);
    p[0]=0;
    struct sembuf sopp,sopv;
    sopp.sem_num=0;
    sopp.sem_op=-1;
    sopp.sem_flg=0;
    sopv.sem_num=0;
    sopv.sem_op=1;
    sopv.sem_flg=0;
    int i;
    struct timeval start,end;
    gettimeofday(&start,NULL);
    if(!fork())
    {
        semop(semArrid,&sopp,1);
        printf("child lock success\n"); 
        p[0]=1/0;
        semop(semArrid,&sopv,1);
        return 0;
    }else{
        sleep(1);
        printf("I am parent,start lock\n");
        semop(semArrid,&sopp,1);
        p[0]=p[0]+1;
        semop(semArrid,&sopv,1);
        gettimeofday(&end,NULL);
        printf("use time=%ld\n",(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
        int status; 
        wait(&status);
        if(WIFEXITED(status))
        {
            printf("child exit nornal\n");
        }else{
            printf("child crash\n");
        }
        printf("%d\n",p[0]);
    }
    return 0;
}

