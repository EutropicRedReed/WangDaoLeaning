#include "tranfile.h"
typedef struct{
    int id;
    char name[26];
    char salt[11];
    char encode[128];
}Acc_Inf;
int signinconfirmclient(int socketfd)
{
    myProtocol mp;
    Acc_Inf acci;
    int i=0,flag;
    char passwd[128]={0};
    memset(&mp,0,sizeof(mp));
    memset(&acci,0,sizeof(acci));
    char temp[MAX_BUF_SIZE]={0};
    printf("please input account name\n");
    read(STDIN_FILENO,mp.buf,sizeof(mp.buf));
    mp.buf[strlen(mp.buf)-1]=0;
    mp.datalen=strlen(mp.buf);
    mp.type=1<<8;
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
Create_PSD_Again:
        myGetPasswd(passwd);
        strcpy(acci.encode,crypt(passwd,saltbuf));
#ifdef DEBUG
        printf("%d,%s,%s,%s\n",acci.id,acci.salt,acci.encode,acci.name);
#endif
        myGetPasswd(passwd);
        if(!strcmp(acci.encode,crypt(passwd,saltbuf)))
        {
            printf("correct!\n");
        }else{
            printf("wrong!\n");
            memset(acci.encode,0,sizeof(acci.encode));
            i++;
            printf("left %d chances\n",3-i);
            if(i<3)
            {
                goto Create_PSD_Again;
            }
            free(saltbuf);
            saltbuf=NULL;
            return -1;
        }
        free(saltbuf);
        saltbuf=NULL;
        
        acci.id=6;  // encrypt type : SHA-512
#ifdef DEBUG
        printf("%d,%s,%s,%s\n",acci.id,acci.salt,acci.encode,acci.name);
#endif
        send_n(socketfd,&acci,sizeof(acci));
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
        i=0;
Confirm_PSD_Again:
        myGetPasswd(passwd);
        if(!strcmp(temp,crypt(passwd,acci.salt)))
        {
            printf("Passwd correct!\n");
        }else{
            printf("Pasdwd wrong!\n");
            i++;
            printf("left %d chances\n",3-i);
            if(i<3)
            {
                goto Confirm_PSD_Again;
            }
            return -1;
        }
    }
    return 0;
}
