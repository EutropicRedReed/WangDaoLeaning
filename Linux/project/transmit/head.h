#ifndef __HEAD_H__
#define __HEAD_H__
#define _GNU_SOURCE
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <signal.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/epoll.h>
#include <errno.h>
#include <sys/uio.h>
#include <sys/sendfile.h>
#include <mysql/mysql.h>
#include <crypt.h>
#include <shadow.h>
#include <termios.h>
#include <openssl/md5.h>
#define MYPRO_LEN_ (sizeof(int)+sizeof(unsigned short) \
                         +MAX_BUF_SIZE*sizeof(char))
#define args_check(argc,num) {if(argc!=num) {printf("error args\n");return -1;}}
#define MYSQL_SERVER_NAME_ "localhost"
#define MYSQL_USER_NAME_ "root"
#define MYSQL_PASSWORD_ "123"
#define MYSQL_DATABASES_NAME_ "ftp_server" 
#define MYSQL_TABLE_ONE_ "account_information"
#define MYSQL_TABLE_TWO_ "vir_file_sys"
#define MYSQL_TABLE_THREE_ "tmp_fd_acci"
#define FILE_STORAGE_PATH_ "/home/lucky/ftp_server_file/"
#define FILE_LOG_PATH_ "/home/lucky/ftp_server_file/log/log"
// table of account information : account_information
// table of virtual file system : vir_file_sys
// table of temp fd to account information : tmp_fd_acci
#define THREAD_NUM_ 10
#define CAPACITY_ 10
#define MAX_BUF_SIZE 4096
#define DEFAULT_PORT 2333
#define PIPE_BUF_ 32768
#define MYSQL_BUF_SIZE_ 256
#define ACC_INF_NAME_ 24    // signin or signup name max 23.
#define ACC_INF_SALT_ 11    // random generate string that size is 10.
#define ACC_INF_ENCODE_ 89  // crypt_r sha-512 88 characters.
#define ACC_INF_PASSWD_ 32  // signin or signup passwd max 32
#define ACC_INF_ENCRYPT_ 6  // encrypt type : SHA-512.
#define ACC_INF_PSD_RETRY_ 3 // passwd retry input number.
#define FILE_SYS_MD5_SIZE_ 33   // md5 22 characters 
#define VIR_FILE_SYS_MAX_DEEP_ 15   // maximal catalog depth
#define VIR_FILE_SYS_MAX_NUM_ 256   // maximal catalog number
#define CAT_NAME_SIZE_ 24

#define LOG_REDIRECT_ do{ \
    int log_fd = open(FILE_LOG_PATH_,O_RDWR|O_APPEND); \
    dup3(STDIN_FILENO,log_fd,O_APPEND);  \
    dup3(STDOUT_FILENO,log_fd,O_APPEND); \
    dup3(STDERR_FILENO,log_fd,O_APPEND); \
}while(0);
#endif
