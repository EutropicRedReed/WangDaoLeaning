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
		sleep(5);
		printf("father\n");
		exit(0);
	}
	return 0;
}
