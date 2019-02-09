#include <func.h>

struct msgbuf{
    long mtype;
    char mtext[512];
};

int main()
{
    int msgid=msgget(1000,IPC_CREAT|0600);
    struct msgbuf msgbuf;
    while(1)
    {
        int semid=semget((key_t)1000,0,IPC_CREAT|0600);
        if(0==semctl(semid,0,GETVAL))
        {
            return 0;
        }
        memset(msgbuf.mtext,0,sizeof(msgbuf.mtext));
        if(0>=msgrcv(msgid,&msgbuf,(size_t)sizeof(msgbuf.mtext),0,0))
        {
            struct sembuf sopv;
            sopv.sem_num=0;
            sopv.sem_op=1;
            sopv.sem_flg=SEM_UNDO;
            semop(semid,&sopv,1);
            return 0;
        }   
        if(2==msgbuf.mtype)
        {
            fprintf(stdout,"%80s",msgbuf.mtext);
        }else if(1==msgbuf.mtype){
            fprintf(stdout,"%-80s\n",msgbuf.mtext);
        }
    }
    return 0;
}

