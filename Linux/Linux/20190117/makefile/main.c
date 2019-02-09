#include <stdlib.h>
#include <stdio.h>
int sub(int,int);
int muti(int,int);
int main(int argc,char* argv[])
{
	int a,b,result;
	a=argv[1];
	b=argv[2];
	result=muti(a,b);
	printf("main result=%d\n",result);
	printf("sub result=%d\n",sub(a,b));
	return 0;
}


