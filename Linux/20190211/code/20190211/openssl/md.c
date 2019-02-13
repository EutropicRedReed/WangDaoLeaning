#include <openssl/md5.h>
#include <string.h>
#include <stdio.h>
#include "factory.h"
// gcc md.c -lcrypto -lssl 
int getMd5Sum(char *buf)
{
    MD5_CTX ctx;
    unsigned char outmd[16];
    int i;
    memset(outmd,0,sizeof(outmd));
    MD5_Init(&ctx);
    MD5_Update(&ctx,buf,strlen(buf));
    MD5_Final(outmd,&ctx);
    memset(&buf,0,FILE_SYS_MD5_SIZE_;
    int j=0;
    for(i=0;i<16;i++)
    {
        sprintf(&buf[j],"%02X",outmd[i]);
        j+=2;
    }
    printf("%s,%d\n",buf,(int)strlen(buf));
    return 0;
}

int main()
{
    char buf[33]={0};
    getMd5Sum(buf);
    return 0;
}
