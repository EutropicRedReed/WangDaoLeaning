#include "func.h"

int main()
{
	char * const envp[2]={"PATH=/usr/bin",NULL};
	execle("./showpath","showpath",NULL,envp);
	printf("you can't see me\n");
}
