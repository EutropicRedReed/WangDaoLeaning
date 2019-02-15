#include "factory.h"
int insertmysqltableone(Acc_Inf *acci)
{
	MYSQL *conn;
    const char* server=MYSQL_SERVER_NAME_;     
	const char* user=MYSQL_USER_NAME_;         
	const char* password=MYSQL_PASSWORD_;      
	const char* database=MYSQL_DATABASES_NAME_;
	char insert[MYSQL_BUF_SIZE_]="insert into account_information(salt,encode,name) values";
    sprintf(insert,"%s('%s','%s','%s');",insert,acci->salt, \
            acci->encode,acci->name);
    puts(insert);
	int t;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	    mysql_close(conn);
        return -1;
	}
	t=mysql_query(conn,insert);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
	    mysql_close(conn);
        return -1;
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

