#include <func.h>

int main()
{
	int shmid=shmget(1000,4096,IPC_CREAT|0600);
	if(-1==shmid)
	{
		perror("shmget");
		return -1;
	}
	char *p=(char*)shmat(shmid,NULL,0);
	if((char*)-1==p)
	{
		perror("shmat");
		return -1;
	}
	printf("shmid=%d\n",shmid);
	strcpy(p,"How are you");
	shmdt(p);
	return 0;
}
