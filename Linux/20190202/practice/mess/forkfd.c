#include <func.h>
//不能正确传递file文件的文件描述符给子进程，close过fds，文件描述符有变化
int main()
{
    int fds[2];
    pipe(fds);
    if(!fork())
    {
        close(fds[1]);
        int fd;
        read(fds[0],&fd,sizeof(int));
        printf("%d\n",fd);
        char buf[128]={0};
        lseek(fd,0,SEEK_SET);
        read(fd,buf,sizeof(buf));
        printf("*%d\n",(int)strlen(buf));
        puts(buf);
        exit(0);
    }else{
        int fd=open("file",O_RDWR);
        printf("%d\n",fd);
        close(fds[0]);
        write(fds[1],&fd,sizeof(int));
        wait(NULL);
    }
    return 0;
}

