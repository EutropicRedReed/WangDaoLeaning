#include "factory.h"
//产生长度为length的随机字符串
int generateSalt(int length,char *salt)
{
    LOG_REDIRECT_
	int flag, i;
	srand((unsigned) time(NULL ));
	for (i = 0; i < length - 1; i++)
	{
		flag = rand() % 3;
		switch (flag)
		{
			case 0:
				salt[i] = 'A' + rand() % 26;
				break;
			case 1:
				salt[i] = 'a' + rand() % 26;
				break;
			case 2:
				salt[i] = '0' + rand() % 10;
				break;
			default:
				salt[i] = 'x';
				break;
		}
	}
	salt[length - 1] = '\0';
	return 1;
}

//int main()
//{
//    char *salt=(char*)calloc(1,10*sizeof(char));
//    generateSalt(10,salt);
//    printf("%s %d\n",salt,(int)strlen(salt));
//    free(salt);
//    salt=NULL;
//    return 0;
//}

