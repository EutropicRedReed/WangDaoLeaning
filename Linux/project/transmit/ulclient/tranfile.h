#ifndef __TRANFILE_H__
#define __TRANFILE_H__
#include "head.h"
typedef struct{
    int datalen;
    unsigned short type;
    char buf[MAX_BUF_SIZE];
}myProtocol;
int tranFile(int new_fd,char *pathname);
int uploadFile(int new_fd);
int send_n(int sfd,void* ptran,int len);
int recv_n(int sfd,void* ptran,int len);
int generateSalt(int length,char *salt);
int signinconfirmclient(int fd);
int myGetPasswd(char *);
#endif
