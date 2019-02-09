#include "func.h"
void sigfunc(int signum);

int main()
{
    int semid=semget((key_t)1000,1,IPC_CREAT|0600);
    semctl(semid,0,SETVAL,1);
    signal(SIGINT,sigfunc);

	int fdr=open("1.pipe",O_RDONLY);
	if(-1==fdr)
	{
		perror("open");
		return -1;
	}
	int fdw=open("2.pipe",O_WRONLY);
	if(-1==fdw)
	{
		perror("open1");
		return -1;
	}
    int shmid=shmget((key_t)1000,(size_t)4096,IPC_CREAT|0600);
    char *p=(char*)shmat(shmid,NULL,0);
	char buf[128]={0};
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
                    shmdt(p);
                    shmctl(shmid,IPC_RMID,0);
                    return 0;
                }
                *p=1;
                strcpy(p+1,buf);
				write(fdw,buf,strlen(buf)-1);
			}
			if(FD_ISSET(fdr,&rdset))
			{
				memset(buf,0,sizeof(buf));
				ret=read(fdr,buf,sizeof(buf));
                if(0==ret)
                {
                    printf("End\n");
                    shmdt(p);
                    shmctl(shmid,IPC_RMID,0);
                    return 0;
                }
                *p=2;
                strcpy(p+1,buf);
			}
		}else{
            if(0==semctl(semid,0,GETVAL))
            {
                shmdt(p);
                shmctl(shmid,IPC_RMID,0);
                return 0;
            }
		}
	}
	close(fdr);
	close(fdw);
	return 0;
}

void sigfunc(int signum)
{
    int semid=semget(1000,0,IPC_CREAT|0600);
    int shmid=shmget((key_t)1000,(size_t)4096,IPC_CREAT|0600);
    char *p=(char*)shmat(shmid,NULL,0);
    struct sembuf sopp;
    sopp.sem_num=0;
    sopp.sem_op=-1;
    sopp.sem_flg=SEM_UNDO;
    semop(semid,&sopp,1);
    while(1)
    {
        if(1==semctl(semid,0,GETVAL))
        {
            break;
        }
    }
    shmdt(p);
    shmctl(shmid,IPC_RMID,0);
    semctl(semid,0,IPC_RMID);
    //unlink("1.pipe");
    //unlink("2.pipe");
    exit(0);
}
