#include "func.h"

int main()
{
	uid_t uid;
	gid_t gid;
	uid=getuid();
	gid=getgid();
	printf("uid=%d,gid=%d,euid=%d,egid=%d\n",uid,gid,geteuid(),getegid());
	return 0;
}
