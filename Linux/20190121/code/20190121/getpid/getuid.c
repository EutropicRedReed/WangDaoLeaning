#include "func.h"

int main()
{
	uid_t uid;
	gid_t gid;
	uid=getuid();
	gid=getgid();
	printf("uid=%d,gid=%d\n",uid,gid);
	return 0;
}
