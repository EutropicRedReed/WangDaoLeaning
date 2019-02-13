#include "factory.h"
int querymysql(Acc_Inf *acci)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
    const char* server=MYSQL_SERVER_NAME_; 
    const char* user=MYSQL_USER_NAME_; 
    const char* password=MYSQL_PASSWORD_;
	const char* database=MYSQL_DATABASES_NAME_;
	char query[MYSQL_BUF_SIZE_]="select PasswdId,id,salt,encode from account_information where name='";
	sprintf(query,"%s%s%s",query,acci->name,"'");
	int t;
    puts(query);
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	    mysql_close(conn);
		return -1;
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
	    mysql_close(conn);
        return -1;
	}else{
		res=mysql_use_result(conn);
		if(res)
		{
            if(NULL==(row=mysql_fetch_row(res)))
            {
	            mysql_close(conn);
                return 1;
            }else{	
                acci->PasswdId=atoi(row[0]);
                acci->id=atoi(row[1]);
                strcpy(acci->salt,row[2]);
                strcpy(acci->encode,row[3]);
#ifdef DEBUG
                printf("%d,%s,%s,%s\n",acci->id,acci->salt,\
                       acci->encode,acci->name);
#endif
			}
		}else{
	        mysql_close(conn);
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
