#ifndef __TRANFILE_H__
#define __TRANFILE_H__
#include "head.h"
typedef struct{
    int dataLen;
    char buf[MAX_BUF_SIZE];
}train;
int tranFile(int new_fd,char *pathname);
int uploadFile(int new_fd);
int send_n(int sfd,void* ptran,int len);
int recv_n(int sfd,void* ptran,int len);
#endif
