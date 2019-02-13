#include "../transmit/head.h"
typedef struct{
    int fd;
    char name[ACC_INF_NAME_];
}Tmp_Fd_Acci;
int querymysqltablethree(Tmp_Fd_Acci *tfa)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
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

    if(tfa->fd>0)
    {
	    char query[MYSQL_BUF_SIZE_]="select fd,acci_name from temp_fd_acci where fd=";
        sprintf(query,"%s%d;",query,tfa->fd);
        puts(query);
	    t=mysql_query(conn,query);
    }else{
	    char query[MYSQL_BUF_SIZE_]="select fd,acci_name from temp_fd_acci where acci_name=";
        sprintf(query,"%s'%s';",query,tfa->name);
        puts(query);
	    t=mysql_query(conn,query);
    }
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
                tfa->fd=atoi(row[0]);
                strcpy(tfa->name,row[1]);
                printf("query success\n");
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
int main()
{
    Tmp_Fd_Acci t;
    t.fd=1;
    querymysqltablethree(&t);
    printf("%s\n",t.name);

    memset(&t,0,sizeof(t));
    strcpy(t.name,"test");
    querymysqltablethree(&t);
    printf("%d\n",t.fd);
    return 0;
}
