#include<stdio.h>
void add(int,int);

void add(int a,int b)
{
	printf("%d + %d = %d\n",a,b,a+b);
}

int main()
{
	int a,b;
	a=5;
	b=8;
	int i;
	for(i=0;i<a;i++)
		printf("%d\n",i);
	add(a,b);
	return 0;
}
