#include "func.h"

int main()
{
	execl("./print","test","3","4",NULL);
	printf("you can't see me\n");
}
