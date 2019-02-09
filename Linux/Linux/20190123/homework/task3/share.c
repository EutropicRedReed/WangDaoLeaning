#include<func.h>

#define N 100000000
void lock(int *p)
{
	while(*p==0)
	{}
	*p=0;
}
void unlock(int *p)
{
	*p=1;
}
int main()
{
	int shmid=shmget(1000,4096,IPC_CREAT|0600);
	if(-1==shmid)
	{
		perror("shmget");
		return -1;
	}
	int *p=(int*)shmat(shmid,NULL,0);
	if((int*)-1==p)
	{
		perror("shmat");
		return -1;
	}
	p[0]=0;
	p[1]=1;
	int i=0;
	if(!fork())
	{
		for(i=0;i<N;i++)
		{
			lock(&p[1]);
			p[0]+=1;
			unlock(&p[1]);
		}
		return 0;
	}else{
		for(i=0;i<N;i++)
		{
			lock(&p[1]);
			p[0]+=1;
			unlock(&p[1]);
		}
		wait(NULL);
		printf("total number = %d\n",p[0]);
		return 0;
	}
}
