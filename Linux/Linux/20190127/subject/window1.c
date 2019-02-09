#include <func.h>
int main()
{
    int semid=semget((key_t)1000,0,IPC_CREAT|0600);
    int shmid=shmget((key_t)1000,(size_t)4096,IPC_CREAT|0600);
    char *p=(char*)shmat(shmid,NULL,0);
    while(1)
    {
        while(*p!=0)
        {
            if(1==*p)
            {
                fprintf(stdout,"%80s",p+1);
            }else{
                fprintf(stdout,"%-80s\n",p+1);
            }
            memset(p,0,4096);
        }
        if(0==semctl(semid,0,GETVAL))
        {
            shmdt(p);
            break;
        }
    }
    return 0;
}

