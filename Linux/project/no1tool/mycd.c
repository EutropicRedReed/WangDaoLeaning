#include <func.h>

int my_chdir(const char *addr)
{
    printf("%s",addr);
    if(-1==chdir(addr))
    {
        perror("chdir");
        return -1;
    }
    printf("currnt working directory: %s\n",getcwd(NULL,0));
    return 0;
}

int main()
{
    char buf[128]={0};
    scanf("%s",buf);
    my_chdir(buf);
    return 0;
}

