#include <func.h>

int main(int argc,char** argv)
{
	args_check(argc,2);
	int ret;
	ret=unlink(argv[1]);
	if(-1==ret)
	{
		perror("unlink");
		return -1;
	}
	return 0;
}
