#include <func.h>

int main()
{
    int semid=semget(1000,2,IPC_CREAT|0600);
    if(-1==semid)
    {
        perror("semget");
        return -1;
    }
    unsigned short arr[2]={0,10};
    semctl(semid,0,SETALL,arr);
    struct sembuf sopp,sopv;
    if(!fork())
    {
        sopp.sem_num=0;
        sopp.sem_op=-1;
        sopp.sem_flg=SEM_UNDO;
        sopv.sem_num=1;
        sopv.sem_op=1;
        sopv.sem_flg=SEM_UNDO;
        while(1)
        {
            printf("customer:product=%d,space=%d\n", \
                   semctl(semid,0,GETVAL), \
                   semctl(semid,1,GETVAL));
            semop(semid,&sopp,1);
            printf("got one\n");
            semop(semid,&sopv,1);
            printf("customer:product=%d,space=%d\n", \
                   semctl(semid,0,GETVAL), \
                   semctl(semid,1,GETVAL));
            sleep(2);
        }
    }else{
        sopp.sem_num=1;
        sopp.sem_op=-1;
        sopp.sem_flg=SEM_UNDO;
        sopv.sem_num=0;
        sopv.sem_op=1;
        sopv.sem_flg=SEM_UNDO;
        while(1)
        {
            printf("producer:product=%d,space=%d\n", \
                   semctl(semid,0,GETVAL), \
                   semctl(semid,1,GETVAL));
            semop(semid,&sopp,1);
            printf("sell one\n");
            semop(semid,&sopv,1);
            printf("producer:product=%d,space=%d\n", \
                   semctl(semid,0,GETVAL), \
                   semctl(semid,1,GETVAL));
            sleep(1);
        }

    }
    return 0;
}

