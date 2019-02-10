#include "head.h"

int tcpInit()
{
    // generate a socket descriptor
    int socketfd=socket(AF_INET,SOCK_STREAM,0);
    if(-1==socketfd)
    {
        perror("socket");
        exit(-1);
    }
    // set socket reuse time 1
    int reuse=1;
    setsockopt(socketfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
    // bind ip and port,make socket associate with ip-port.
    struct sockaddr_in ser;
    memset(&ser,0,sizeof(ser));
    ser.sin_family=AF_INET;
    ser.sin_port=htons(DEFAULT_PORT);
    ser.sin_addr.s_addr=INADDR_ANY;
    if(-1==bind(socketfd,(struct sockaddr*)&ser,sizeof(ser)))
    {
        perror("bind");
        exit(-1);
    }
    // make that port and ip in the listening mode and wait for client connect request.
    listen(socketfd,10);

    return socketfd;
}
