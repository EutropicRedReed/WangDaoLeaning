#include <func.h>

int main()
{
	shmctl(65536,IPC_RMID,NULL);
	return 0;
}
