#include <func.h>

int main()
{
    printf("uid=%d,euid=%d\n",getuid(),geteuid());
    int ret=setuid(0);
    if(-1==ret)
    {
        perror("setuid");
        return -1;
    }
    printf("uid=%d,euid=%d\n",getuid(),geteuid());
    return 0;
}

