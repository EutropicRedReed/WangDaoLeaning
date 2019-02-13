char cur_cat;   // '0' normal '1' current catalog '2' screen belong+md5sum '3' screen belong+name '4' screen belong+cur_cat '5' screen belong+type
}Vir_File_Sys;  
typedef struct{ // table three make it easy to transmit data between table 1 and table 2.
    int fd;
    char name[ACC_INF_NAME_];
}Tmp_Fd_Acci;
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
int getMd5Sum(char *);
int virFileInsertSer(Vir_File_Sys *);
int querymysqltablethree(Tmp_Fd_Acci *);
int insertmysqltablethree(Tmp_Fd_Acci *);
int updatemysqltablethree(Tmp_Fd_Acci *);
int deletemysqltablethree(Tmp_Fd_Acci *);
#endif
