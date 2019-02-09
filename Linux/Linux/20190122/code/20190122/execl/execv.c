#include "func.h"

int main()
{
	char *const argv[4]={"test","3","4",NULL};
	execv("./print",argv);
	printf("you can't see me\n");
}
