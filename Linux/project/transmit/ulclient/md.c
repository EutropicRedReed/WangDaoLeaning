#include "tranfile.h"
// gcc md.c -lcrypto -lssl -o md
int getMd5Sum(char *addr)
{
    MD5_CTX ctx;
    char buf[MAX_BUF_SIZE]={0};
    unsigned char outmd[16];
    int i,ret=0;
    memset(outmd,0,sizeof(outmd));
    MD5_Init(&ctx);
    int fd=open(addr,O_RDONLY);
    if(-1==fd)
    {
        perror("open");
        return -1;
    }
    while(0!=(ret=read(fd,buf,sizeof(buf))))
    {
        MD5_Update(&ctx,buf,ret);
        memset(buf,0,sizeof(buf));
    }
    MD5_Final(outmd,&ctx);
    memset(addr,0,FILE_SYS_MD5_SIZE_);
    int j=0;
    for(i=0;i<16;i++)
    {
        sprintf(&addr[j],"%02X",outmd[i]);
        j+=2;
    }
    close(fd);
    return 0;
}

//int main()
//{
//    char buf[33]={"file"};
//    getMd5Sum(buf);
//    printf("%s,%d\n",buf,(int)strlen(buf));
//    return 0;
//}
