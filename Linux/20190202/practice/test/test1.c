#include <func.h>

int main()
{
    pid_t pid;
    int i;
    for(i=0;i<4;i++)
    {
        pid=fork();
        if(!pid)
        {
            printf("child\n");
        }
        //else
        printf("main\n");
    }
    while(1);
    return 0;
}
