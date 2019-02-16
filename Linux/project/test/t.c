#include <func.h>
int main()
{
    	char buf[5][20];
	int i = 0, j = 0, k = 0;
	const char *addr = "/dir1/dir2/dir3/dri4";
	char temp[20];

    i=1;
    k=0;
    j=0;
	while (addr[i] != 0)
	{
		if (addr[i] == '/')
		{
			i++;
		}
		while (addr[i] != '/'&&addr[i] != 0)
		{
			temp[k++] = addr[i++];
		}
		temp[k] = 0;
		strcpy(buf[j++], temp);
		k = 0;
	}
	for (i = 0; i<j; i++)
		printf("%s\n", buf[i]);
	return 0;
}

