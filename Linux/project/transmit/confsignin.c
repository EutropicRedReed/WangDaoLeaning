#include "factory.h"
int signinconfirmserver(int socketfd)
{
    myProtocol mp;
    Acc_Inf acci;
    int i=0,ret;
    memset(&mp,0,sizeof(mp));
    memset(&acci,0,sizeof(acci));
    //char temp[MAX_BUF_SIZE]={0};
    recv_n(socketfd,&mp,MYPRO_LEN_); 
    i=mp.type>>8;
    if(1==i)
    {
        strcpy(acci.name,mp.buf);
        ret=querymysql(&acci);
        if(-1==ret) // databases have wrong.
        {
#ifdef DEBUG 
            printf("%d,%s,%s,%s\n",acci.id,acci.salt,acci.encode,acci.name);
#endif              
            acci.id=-1;
            send_n(socketfd,&acci,sizeof(acci));
            return -1;
        }else if(1==ret){   // create account.
            acci.id=-2;
            //char saltbuf[150]={0};
            generateSalt(11,acci.salt);
#ifdef DEBUG 
            printf("%d,%s,%s,%s\n",acci.id,acci.salt,acci.encode,acci.name);
#endif              
            send_n(socketfd,&acci,sizeof(acci));
            recv_n(socketfd,&acci,sizeof(acci));
            //strcpy(saltbuf,acci.salt);
#ifdef DEBUG 
            printf("%d,%s,%s,%s\n",acci.id,acci.salt,acci.encode,acci.name);
#endif              
            if(-1==insertmysql(&acci))
            {
                ret=-1;
                send_n(socketfd,&ret,sizeof(int));
                printf("failed\n");
            }
            ret=0;
            send_n(socketfd,&ret,sizeof(int));
            printf("success\n");
            return -1;
        }else if(0==ret)
        {
#ifdef DEBUG 
            printf("%d,%s,%s,%s\n",acci.id,acci.salt,acci.encode,acci.name);
#endif              
            ret=send_n(socketfd,&acci,sizeof(acci));
            printf("%d\n",ret);
        }
    }
    return 0;
}
