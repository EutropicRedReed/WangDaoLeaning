#include "func.h"

int main(int argc,char **argv)
{
	args_check(argc,2);
	uid_t uid;
	gid_t gid;
	uid=getuid();
	gid=getgid();
	printf("uid=%d,gid=%d,euid=%d,egid=%d\n",uid,gid,geteuid(),getegid());
	int fd=open(argv[1],O_RDWR);
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
	write(fd,"getuid",6);
	return 0;
}
