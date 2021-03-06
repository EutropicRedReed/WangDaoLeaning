#ifndef __FACTORY_H__
#define __FACTORY_H__
#include "head.h"
#include "work_que.h"
typedef void* (*threadfunc_t)(void*);
typedef struct{
    pthread_t *pthid;
    int threadNum;
    pQue_t que;
    pthread_cond_t cond;
    threadfunc_t downFileFunc;
    short *Flag;
}Factory,*pFactory;
typedef struct{
    int PasswdId;
    int id;
    char name[ACC_INF_NAME_];
    char salt[ACC_INF_SALT_];
    char encode[ACC_INF_ENCODE_];
}Acc_Inf;
typedef struct{
    int procode;
    int code;
    char name[ACC_INF_NAME_];
    char type;
    int belong;
    char md5sum[FILE_SYS_MD5_SIZE_];
    char cur_cat;   // '0' normal '1' current catalog '2' screen belong+md5sum '3' screen belong+name '4' screen belong+cur_cat '5' screen belong+type
    long int size;
}Vir_File_Sys;  
typedef struct{ // table three make it easy to transmit data between table 1 and table 2.
    int fd;
    char name[ACC_INF_NAME_];
}Tmp_Fd_Acci;
typedef struct{
    int datalen;
    unsigned short type;
    char buf[MAX_BUF_SIZE];
}myProtocol;
int tranFile(int new_fd,char *pathname);
int uploadFile(int new_fd);
int send_n(int sfd,void* ptran,int len);
int recv_n(int sfd,void* ptran,int len);

void factoryInit(pFactory pf,threadfunc_t threadfunc);
void factoryStart(pFactory);
int tcpInit();
int my_chdir(const char *addr,int);
void my_pwd(int);
int my_ls(const char *addr,int);
int my_rm(const char *pathname,int);
int sendorder(int);
int recvorder(int);
int querymysqltableone(Acc_Inf *);
int insertmysqltableone(Acc_Inf *);
int generateSalt(int length,char *salt);
int signinconfirmserver(int fd);
int myGetPasswd(char *);
int getMd5Sum(char *);
int querymysqltablethree(Tmp_Fd_Acci *);
int insertmysqltablethree(Tmp_Fd_Acci *);
int updatemysqltablethree(Tmp_Fd_Acci *);
int deletemysqltablethree(Tmp_Fd_Acci *);
int insertmysqltabletwo(Vir_File_Sys *);
int deletemysqltabletwo(Vir_File_Sys *);
int querymysqltabletwo(Vir_File_Sys *);
int updatemysqltabletwo(Vir_File_Sys *);
#endif
