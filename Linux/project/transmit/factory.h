#ifndef __FACTORY_H__
#define __FACTORY_H__
#include "head.h"
#include "work_que.h"
#include "tranfile.h"
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
    int id;
    char name[26];
    char salt[11];
    char encode[128];
}Acc_Inf;
void factoryInit(pFactory pf,threadfunc_t threadfunc);
void factoryStart(pFactory);
int tcpInit();
int my_chdir(const char *addr,int);
void my_pwd(int);
int my_ls(const char *addr,int);
int my_rm(const char *pathname,int);
int sendorder(int);
int recvorder(int);
int querymysql(Acc_Inf *);
int insertmysql(Acc_Inf *);
int generateSalt(int length,char *salt);
int signinconfirmserver(int fd);
int myGetPasswd(char *);
#endif
