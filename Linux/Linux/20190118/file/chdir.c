#include<unistd.h>
#include<stdio.h>
int main()
{
	chdir("/home/lucky/Linux/20180118");
	printf("currnt working directory: %s\n",getcwd(NULL,0));
}
