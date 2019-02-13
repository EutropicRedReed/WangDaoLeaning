#include "factory.h"
int deletemysqltablethree(Tmp_Fd_Acci *tfa)
{
	MYSQL *conn;
	const char* server=MYSQL_SERVER_NAME_;
	const char* user=MYSQL_USER_NAME_;
	const char* password=MYSQL_PASSWORD_;
	const char* database=MYSQL_DATABASES_NAME_;
	int t=0;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
        mysql_close(conn);
        return -1;
	}

    if(tfa->fd>0)
    {
	    char Delete[MYSQL_BUF_SIZE_]="delete from temp_fd_acci where fd=";
        sprintf(Delete,"%s%d",Delete,tfa->fd);
        puts(Delete);
	    t=mysql_query(conn,Delete);
    }else{
	    char Delete[MYSQL_BUF_SIZE_]="delete from temp_fd_acci where acci_name=";
        sprintf(Delete,"%s'%s'",Delete,tfa->name);
        puts(Delete);
	    t=mysql_query(conn,Delete);
    }
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
	    mysql_close(conn);
        return -1;
	}else{
		printf("delete success,delete row=%ld\n",(long)mysql_affected_rows(conn));
	}
	mysql_close(conn);
	return 0;
}
//int main()
//{
//    Tmp_Fd_Acci t;
//    t.fd=1;
//    strcpy(t.name,"test");
//    deletemysqltablethree(&t);
//    return 0;
//}
