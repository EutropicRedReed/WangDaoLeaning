#include "tranfile.h"
typedef struct{
    int PasswdId;
    int id;
    char name[ACC_INF_NAME_];
    char salt[ACC_INF_SALT_];
    char encode[ACC_INF_ENCODE_];
}Acc_Inf;
int signinconfirmclient(int socketfd)
{
    myProtocol mp;
    Acc_Inf acci;
    int i=0,flag;
    char passwd[ACC_INF_PASSWD_]={0};
    struct crypt_data data;
    data.initialized=0;
    memset(&mp,0,sizeof(mp));
    memset(&acci,0,sizeof(acci));
    char temp[MAX_BUF_SIZE]={0};
    printf("please input account name\n");
    read(STDIN_FILENO,mp.buf,sizeof(mp.buf));
    mp.buf[strlen(mp.buf)-1]=0; // rewrite '\r' to '0' 
    mp.datalen=strlen(mp.buf);
    mp.type=1<<8;   // type is unsigned 2 bytes lower 8 bits is transmit order higher 8 bits is transmit signin/signup information.
    send_n(socketfd,&mp,MYPRO_LEN_); 
#ifdef DEBUG
        printf("%d,%s,%s,%s\n",acci.id,acci.salt,acci.encode,acci.name);
#endif
    recv_n(socketfd,&acci,sizeof(acci));
#ifdef DEBUG
        printf("%d,%s,%s,%s\n",acci.id,acci.salt,acci.encode,acci.name);
#endif
    if(-1==acci.id) //databases have wrong.
    {
        printf("error: databases;\n");
    }else if(-2==acci.id)   //create account.
    {
        char *saltbuf=(char*)calloc(1,sizeof(acci.salt));
        strcpy(saltbuf,acci.salt);
        printf("Create a account\n");
        printf("********************\n");
        i=0;
Create_Psd_Again:
        myGetPasswd(passwd);
        crypt_r(passwd,saltbuf,&data);
        strcpy(acci.encode,data.crypt_3_buf);
#ifdef DEBUG
        printf("%d,%s,%s,%s\n",acci.id,acci.salt,acci.encode,acci.name);
#endif
        myGetPasswd(passwd);
        crypt_r(passwd,saltbuf,&data);
        strcpy(acci.encode,data.crypt_3_buf);
        if(!strcmp(acci.encode,data.crypt_3_buf))
        {
            printf("correct!\n");
        }else{
            printf("wrong!\n");
            memset(acci.encode,0,sizeof(acci.encode));
            i++;
            printf("left %d chances\n",ACC_INF_PSD_RETRY_-i);
            if(i<ACC_INF_PSD_RETRY_) // chances to input passwd.
            {
                goto Create_Psd_Again;
            }
            free(saltbuf);
            saltbuf=NULL;
            return -1;
        }
        free(saltbuf);
        saltbuf=NULL;
        
        acci.id=ACC_INF_ENCRYPT_;
#ifdef DEBUG
        printf("%d,%s,%s,%s\n",acci.id,acci.salt,acci.encode,acci.name);
#endif
        send_n(socketfd,&acci,sizeof(acci));    // send information to signup.
        recv_n(socketfd,&flag,sizeof(int));
        if(0==flag)
        {
            printf("Account create success!\n");
            printf("********************\n");
        }else{
            printf("Account create failed!\n");
            printf("********************\n");
        }
    }else{  // confirm account information.
        sprintf(temp,"$%d$%s$%s",acci.id,acci.salt,acci.encode);    
#ifdef DEBUG
        printf("%s\n",temp);
#endif
        i=0;
Confirm_PSD_Again:
        myGetPasswd(passwd);
        crypt_r(passwd,acci.salt,&data);
        if(!strcmp(acci.encode,data.crypt_3_buf))
        {
            printf("Passwd correct!\n");
            send_n(socketfd,&i,sizeof(int));
        }else{
            printf("Pasdwd wrong!\n");
            if(++i<ACC_INF_PSD_RETRY_)
            {
                memset(passwd,0,sizeof(passwd));
                printf("left %d chances\n",ACC_INF_PSD_RETRY_-i);
                goto Confirm_PSD_Again;
            }else{
                send_n(socketfd,&i,sizeof(int));
                exit(-1);
            }
        }
    }
    return 0;
}
