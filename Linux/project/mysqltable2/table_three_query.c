#include "../transmit/factory.h"
int querymysqltabletwo(Vir_File_Sys *vfs,int fd)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	const char* server=MYSQL_SERVER_NAME_;
	const char* user=MYSQL_USER_NAME_;
	const char* password=MYSQL_PASSWORD_;
	const char* database=MYSQL_DATABASES_NAME_;
	int t;
    Tmp_Fd_Acci tfa;
    tfa.fd=fd;
    querymysqltablethree(&tfa);

	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	    mysql_close(conn);
        return -1;
	}

    if('2'==vfs->cur_cat)
    {
	    char query[MYSQL_BUF_SIZE_]="select procode,name,type,belong,md5sum,cur_cat from ";
        sprintf(query,"%s%s where belong=",query,MYSQL_TABLE_TWO_);
        sprintf(query,"%s%d and where md5sum='%s';",query,vfs->belong,vfs->md5sum);
        puts(query);
	    t=mysql_query(conn,query);
    }else if('3'==vfs->cur_cat){
	    char query[MYSQL_BUF_SIZE_]="select procode,name,type,belong,md5sum,cur_cat from ";
        sprintf(query,"%s%s where belong=",query,MYSQL_TABLE_TWO_);
        sprintf(query,"%s%d and where name='%s';",query,vfs->belong,vfs->name);
        puts(query);
	    t=mysql_query(conn,query);
    }else if('4'==vfs->cur_cat){
	    char query[MYSQL_BUF_SIZE_]="select procode,name,type,belong,md5sum,cur_cat from ";
        sprintf(query,"%s%s where belong=",query,MYSQL_TABLE_TWO_);
        sprintf(query,"%s%d and where name='%c';",query,vfs->belong,vfs->cur_cat);
        puts(query);
	    t=mysql_query(conn,query);
    }else if('5'==vfs->cur_cat){
	    char query[MYSQL_BUF_SIZE_]="select procode,name,type,belong,md5sum,cur_cat from ";
        sprintf(query,"%s%s where belong=",query,MYSQL_TABLE_TWO_);
        sprintf(query,"%s%d and where name='%c';",query,vfs->belong,vfs->type);
        puts(query);
	    t=mysql_query(conn,query);
    }else{  // normal query.
	    char query[MYSQL_BUF_SIZE_]="select procode,name,type,belong,md5sum,cur_cat from ";
        sprintf(query,"%s%s where belong=%d;",query,MYSQL_TABLE_TWO_,vfs->belong);
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
            }
            int j=0;
            do{	
                while(j<VIR_FILE_SYS_MAX_DEEP_)
                {
                    vfs[j]->
                    j++;
                }
            }while(NULL!=(row=nysql_setch_row(res)));
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
    querymysqltabletwo(&t,6);
    printf("%s\n",t.name);

    memset(&t,0,sizeof(t));
    strcpy(t.name,"test");
    querymysqltabletwo(&t);
    printf("%d\n",t.fd);
    return 0;
}
