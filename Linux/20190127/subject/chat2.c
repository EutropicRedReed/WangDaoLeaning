#include "func.h"

struct msgbuf{
    long mtype;
    char mtext[512];
};

void sigfunc(int signum);

int main()
{
    int semid=semget(1000,1,IPC_CREAT|0600);
    semctl(semid,0,SETVAL,1);
    signal(SIGINT,sigfunc);
    int fdw=open("1.pipe",O_WRONLY);
    if(-1==fdw)
    {
        perror("open");
        return -1;
    }
    int fdr=open("2.pipe",O_RDONLY);
    if(-1==fdr)
    {
        perror("open1");
        return -1;
    }
    int msgid=msgget(1000,IPC_CREAT|0600);
    char buf[512]={0};
    int ret;
    fd_set rdset;
    struct timeval t;
    while(1)
    {
        FD_ZERO(&rdset);
        FD_SET(0,&rdset);
        FD_SET(fdr,&rdset);
        memset(&t,0,sizeof(t));
        t.tv_usec=500;
        ret=select(fdr+1,&rdset,NULL,NULL,&t);
        if(ret>0)
        {
            if(FD_ISSET(STDIN_FILENO,&rdset))
            {
                memset(buf,0,sizeof(buf));
                ret=read(STDIN_FILENO,buf,sizeof(buf));
                if(0==ret)
                {
                    printf("End\n");
                    msgctl(msgid,IPC_RMID,NULL);
                    return 0;
                }
                struct msgbuf msgbuf;
                msgbuf.mtype=2; 
                memset(msgbuf.mtext,0,sizeof(msgbuf.mtext));
                strcpy(msgbuf.mtext,buf);
                msgsnd(msgid,&msgbuf,(size_t)sizeof(msgbuf.mtext),0);
                write(fdw,buf,strlen(buf)-1);
            }
            if(FD_ISSET(fdr,&rdset))
            {
                memset(buf,0,sizeof(buf));
                ret=read(fdr,buf,sizeof(buf));
                if(0==ret)
                {
                    printf("Bye Bye\n");
                    msgctl(msgid,IPC_RMID,NULL);
                    return 0;
                }
                struct msgbuf msgbuf;
                msgbuf.mtype=1;
                memset(msgbuf.mtext,0,sizeof(msgbuf.mtext));
                strcpy(msgbuf.mtext,buf);
                msgsnd(msgid,&msgbuf,(size_t)sizeof(msgbuf.mtext),0);
            }
        }else {
            if(0==semctl(semid,0,GETVAL))
            {
                struct sembuf sopv;
                sopv.sem_num=0;
                sopv.sem_op=1;
                sopv.sem_flg=SEM_UNDO;
                semop(semid,&sopv,1);
                msgctl(msgid,IPC_RMID,NULL);
                break;
            }
        }
    }
    close(fdr);
    close(fdw);
    return 0;
}

void sigfunc(int signum)
{
    int msgid=msgget((key_t)1000,IPC_CREAT|0600);
    int semid=semget((key_t)1000,0,IPC_CREAT|0600);
    struct sembuf sopp;
    sopp.sem_num=0;
    sopp.sem_op=-1;
    sopp.sem_flg=SEM_UNDO;
    semop(semid,&sopp,1);
    printf("%d\n",semctl(semid,0,GETVAL));
    sleep(2);
    msgctl(msgid,IPC_RMID,NULL);
    semctl(semid,0,IPC_RMID);
    //unlink("1.pipe");
    //unlink("2.pipe");
    exit(0);
}

