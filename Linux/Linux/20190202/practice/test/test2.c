#include <func.h>

int main()
{
    pid_t pid;
    int i;
    for(i=0;i<3;i++)
    {
        pid=fork();
        if(!pid)
        {
            printf("child\n");
        }
        //else
        printf("main\n");
    }
    return 0;
}

