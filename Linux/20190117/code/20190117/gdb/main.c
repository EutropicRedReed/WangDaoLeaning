#include <stdlib.h>
#include <stdio.h>

int muti(int a,int b)
{
	printf("muti result=%d\n",a*b);
	return a*b;
}

int main(int argc,char* argv[])
{
	int iNum,iNum1,result;
	iNum=atoi(argv[1]);
	iNum1=atoi(argv[2]);
	result=muti(iNum,iNum1);
	printf("main result=%d\n",result);
	int i;
	for(i=0;i<5;i++)
	{
		printf("this is circle\n");
	}
	return 0;
}


