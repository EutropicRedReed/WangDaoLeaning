#include<func.h>

int main()
{
	int fd=open("./file1",O_APPEND|O_RDWR,0755);
	close(fd);
	return 0;
}

