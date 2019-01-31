#include <func.h>

int main()
{
    signal(SIGINT,SIG_IGN);
    printf("Hello world\n");
    sleep(10);
    printf("sleep over\n");
    signal(SIGINT,SIG_DFL);
    sleep(3);
    return 0;
}
