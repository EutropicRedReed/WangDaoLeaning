#include <func.h>

int main()
{
    char buf[20]={0};
    fscanf(stdin,"%s",buf);
    puts(buf);
    write(STDOUT_FILENO,buf,strlen(buf)-1);
    return 0;
}

