#include <func.h>

int main()
{
    printf("uid=%d,gid=%d\n",getuid(),getgid());
    printf("euid=%d,egid=%d\n",geteuid(),getegid());
    int fd=open("test.txt",O_CREAT|O_RDWR,0755);
    int ret=fchmod(fd,07000|0755);
    if(-1==ret)
    {
        perror("fchmod");
        return -1;
    }
    if(-1==fd)
    {
        perror("open");
        return -1;
    }
    char buf[128]={"hello world"};
    ret=write(fd,buf,sizeof(buf));
    if(-1==ret)
    {
        perror("write");
        return -1;
    }
    close(fd);
    return 0;
}

