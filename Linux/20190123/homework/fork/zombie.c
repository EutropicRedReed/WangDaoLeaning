#include<func.h>

int main()
{
	if(!fork())
	{
		//son
		printf("son\n");
		exit(0);
	}else{
		//father
		printf("father\n");
		sleep(5);
		exit(0);
	}
	return 0;
}
