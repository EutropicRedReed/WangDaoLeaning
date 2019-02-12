#include "factory.h"
int insertmysql(Acc_Inf *acci)
{
	MYSQL *conn;
	const char* server="localhost";
	const char* user="root";
	const char* password="123";
	const char* database="ftp_server";
	char insert[MYSQL_BUF_SIZE_]="insert into account_information( \
                           salt,encode,name) \
                           values";
    sprintf(insert,"%s('%s','%s','%s');",insert,acci->salt, \
            acci->encode,acci->name);
	int t;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
        return -1;
	}
	t=mysql_query(conn,insert);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
        return -1;
	}else{
        return 0;
	}
	mysql_close(conn);
	return 0;
}
//int main()
//{
//    Acc_Inf a;
//    strcpy(a.name,"test");
//    strcpy(a.encode,"test encode");
//    strcpy(a.salt,"test salt");
//    return 0;
//}

