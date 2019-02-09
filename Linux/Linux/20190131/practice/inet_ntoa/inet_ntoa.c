#include <func.h>

int main(int argc,char *argv[])
{
    args_check(argc,2);
    struct in_addr addr;
    inet_aton(argv[1],&addr);
    printf("%x\n",addr.s_addr);
    char buf[16]={0};
    strcpy(buf,inet_ntoa(addr));
    printf("%s\n",buf);
    printf("%u\t%x\n",ntohl(addr.s_addr),ntohl(addr.s_addr));
    return 0;
}

