#include <func.h>

int main(int argc,char **argv)
{
	key_t key;
	args_check(argc,2);
	key=ftok(argv[1],1);
	printf("%d\n",key);
	return 0;
}
