#include "factory.h"
int querymysql(Acc_Inf *acci)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	const char* server="localhost";
	const char* user="root";
	const char* password="123";
	const char* database="ftp_server";
	char query[MYSQL_BUF_SIZE_]="select id,salt,encode from account_information where name='";
	sprintf(query,"%s%s%s",query,acci->name,"'");
	int t;
    puts(query);
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
		return -1;
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
        return -1;
	}else{
		res=mysql_use_result(conn);
		if(res)
		{
			while((row=mysql_fetch_row(res))!=NULL)
			{	
                acci->id=atoi(row[0]);
                strcpy(acci->salt,row[1]);
                strcpy(acci->encode,row[2]);
                printf("%d,%s\n",acci->id,acci->name);
			}
            if(NULL==row)
            {
                return 1;
            }
		}else{
            return -1;
		}
		mysql_free_result(res);
	}
	mysql_close(conn);
	return 0;
}
//int main()
//{
//    Acc_Inf a;
//    strcpy(a.name,"lili");
//    querymysql(&a);
//    printf("%d %s %s\n",a.id,a.salt,a.encode);
//}
