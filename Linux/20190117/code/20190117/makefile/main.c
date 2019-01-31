#include <stdlib.h>
#include <stdio.h>
int sub(int,int);
int muti(int,int);
int main(int argc,char* argv[])
{
	int iNum,iNum1,result;
	iNum=3;
	iNum1=4;
	result=muti(iNum,iNum1);
	printf("main result=%d\n",result);
	printf("sub result=%d\n",sub(iNum1,iNum));
	return 0;
}


