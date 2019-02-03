#include "pro_pool_server.h"

int tranFile(int new_fd)
{
    train t;
    //发送文件名
    strcpy(t.buf,DOWNFILE);
    t.dataLen=strlen(DOWNFILE);
    send(new_fd,&t,4+t.dataLen,0);
    //发文件内容
    int fd=open(DOWNFILE,O_RDONLY);
    while(t.dataLen=read(fd,t.buf,sizeof(t.buf)))
    {
        send(new_fd,&t,4+t.dataLen,0);
    }
    send(new_fd,&t,4+t.dataLen,0);//发送结束标志
    close(new_fd);
    return 0;
}

