#include <func.h>

void my_rm(const char *pathname)
{
    if(-1==unlink(pathname))
    {
        perror("delete failed");
    }
    printf("delete file success\n");
}

int main(int argc,char *argv[])
{
    my_rm(argv[1]);
    return 0;
}

