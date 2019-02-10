#include <func.h>

void my_pwd()
{
    printf("currnt directory: %s\n",getcwd(NULL,0));
}

int main()
{
    my_pwd();
    return 0;
}

