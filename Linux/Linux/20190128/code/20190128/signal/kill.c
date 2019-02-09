#include <func.h>

int main(int argc,char** argv)
{
    args_check(argc,2);
    pid_t pid=atoi(argv[1]);
    int ret=kill(pid,SIGINT);
    if(-1==ret)
    {
        perror("kill");
        return -1;
    }
    return 0;
}

