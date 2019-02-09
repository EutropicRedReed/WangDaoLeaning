#include <stdio.h>
//Debug信息太多就要分级
int main()
{
	FILE *fp=fopen("noexist","rb+");
#ifdef DEBUG
	printf("I am a debug information\n");
#endif
	return 0;
}
