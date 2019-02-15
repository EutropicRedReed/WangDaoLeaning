#include "factory.h"
int signinconfirmserver(int socketfd)
{
    myProtocol mp;
    Acc_Inf acci;
    Tmp_Fd_Acci tfa;
    int i=0,ret;
    memset(&mp,0,sizeof(mp));
    memset(&acci,0,sizeof(acci));
    //char temp[MAX_BUF_SIZE]={0};
    recv_n(socketfd,&mp,MYPRO_LEN_); 
    i=mp.type>>8;
    if(1==i)
    {
        strcpy(acci.name,mp.buf);

        // renew table three
        strcpy(tfa.name,mp.buf);
        tfa.fd=socketfd;
        insertmysqltablethree(&tfa);

        ret=querymysqltableone(&acci);
#ifdef DEBUG
        printf("%d\n",ret);
        printf("%d,%s,%s,%s\n",acci.id,acci.salt,acci.encode,acci.name);
#endif
        if(-1==ret) // databases have wrong.
        {
#ifdef DEBUG 
            printf("%d,%s,%s,%s\n",acci.id,acci.salt,acci.encode,acci.name);
#endif              
            deletemysqltablethree(&tfa);
            acci.id=-1;
            send_n(socketfd,&acci,sizeof(acci));
            return -1;
        }else if(1==ret){   // create account.
            acci.id=-2;
            //char saltbuf[150]={0};
            generateSalt(ACC_INF_SALT_,acci.salt);
#ifdef DEBUG 
            printf("%d,%s,%s,%s\n",acci.id,acci.salt,acci.encode,acci.name);
#endif              
            send_n(socketfd,&acci,sizeof(acci));
            recv_n(socketfd,&acci,sizeof(acci));
            //strcpy(saltbuf,acci.salt);
#ifdef DEBUG 
            printf("%d,%s,%s,%s\n",acci.id,acci.salt,acci.encode,acci.name);
#endif              
            if(-1==insertmysqltableone(&acci))
            {
                ret=-1;
                send_n(socketfd,&ret,sizeof(int));
                printf("Account create failed\n");
                deletemysqltablethree(&tfa);
                return -1;
            }
            ret=0;
            send_n(socketfd,&ret,sizeof(int));
            // create virtual work catalog.
            Vir_File_Sys vfs;
            querymysqltableone(&acci); 
            //char md5buf[FILE_SYS_MD5_SIZE_]={0};
            vfs.procode=0;
            strcpy(vfs.name,acci.name);
            vfs.type='d';
            vfs.cur_cat='1';
            vfs.belong=acci.PasswdId;
        
            //strcpy(vfs.md5sum,md5buf);
            if(-1==insertmysqltabletwo(&vfs))
            {
                printf("Catalog create failed!\n");
            }
            printf("Account create success!\n");
        }else if(0==ret)        // confirm passwd.
        {
#ifdef DEBUG 
            printf("%d,%s,%s,%s\n",acci.id,acci.salt,acci.encode,acci.name);
#endif              
            send_n(socketfd,&acci,sizeof(acci));
            recv_n(socketfd,&i,sizeof(int));
            if(i>=ACC_INF_PSD_RETRY_)
            {
                deletemysqltablethree(&tfa);
                return -1;
            }
        }
    }
    return 0;
}
