#include "../transmit/head.h"
typedef struct{
    int fd;
    char name[ACC_INF_NAME_];
}Tmp_Fd_Acci;
int insertmysqltablethree(Tmp_Fd_Acci *tfa)
{
    MYSQL *conn;
    const char* server=MYSQL_SERVER_NAME_;
    const char* user=MYSQL_USER_NAME_;
    const char* password=MYSQL_PASSWORD_;
    const char* database=MYSQL_DATABASES_NAME_;
    int t;
    conn=mysql_init(NULL);
    if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
    {
        printf("Error connecting to database:%s\n",mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    char insert[MYSQL_BUF_SIZE_]="insert into temp_fd_acci(fd,acci_name) values(";
    sprintf(insert,"%s%d,'%s');",insert,tfa->fd,tfa->name);
    puts(insert);
    t=mysql_query(conn,insert);
    if(t)
    {
        printf("Error making query:%s\n",mysql_error(conn));
        mysql_close(conn);
        return -1;
    }else{
        printf("insert success\n");
    }
    mysql_close(conn);
    return 0;
}
int main()
{
    Tmp_Fd_Acci t;
    t.fd=2;
    strcpy(t.name,"lihua");
    insertmysqltablethree(&t);
    return 0;
}
