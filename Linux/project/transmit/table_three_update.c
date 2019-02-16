#include "factory.h"
int updatemysqltablethree(Tmp_Fd_Acci *tfa)
{
    LOG_REDIRECT_
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
        char update[MYSQL_BUF_SIZE_]="update temp_fd_acci set acci_name="; 
        sprintf(update,"%s'%s' where fd=%d;",update,tfa->name,tfa->fd);
        puts(update);
        t=mysql_query(conn,update);
    }
	
    if(t)
	{
        char update[MYSQL_BUF_SIZE_]="update temp_fd_acci set fd="; 
        sprintf(update,"%s%d where name='%s';",update,tfa->fd,tfa->name);
        puts(update);
        t=mysql_query(conn,update);
	}
	mysql_close(conn);
	return 0;
}

//int main()
//{
//    Tmp_Fd_Acci t;
//    t.fd=1;
//    strcpy(t.name,"testtest");
//    updatemysqltablethree(&t);
//    printf("%s\n",t.name);
//    memset(&t,0,sizeof(t));
//
//    strcpy(t.name,"testtest");
//    t.fd=2;
//    updatemysqltablethree(&t);
//    printf("%d\n",t.fd);
//
//    return 0;
//}
