#include "factory.h"
int deletemysqltabletwo(Vir_File_Sys *vfs)
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

    if('2'==vfs->cur_cat)
    {
        char Delete[MYSQL_BUF_SIZE_]="delete from ";
        sprintf(Delete,"%s%s where belong=",Delete,MYSQL_TABLE_TWO_);
        sprintf(Delete,"%s%d and md5sum='%s';",Delete,vfs->belong,vfs->md5sum);
        puts(Delete);
        t=mysql_query(conn,Delete);
    }else if('3'==vfs->cur_cat){
        char Delete[MYSQL_BUF_SIZE_]="delete from ";
        sprintf(Delete,"%s%s where belong=",Delete,MYSQL_TABLE_TWO_);
        sprintf(Delete,"%s%d and name='%s';",Delete,vfs->belong,vfs->name);
        puts(Delete);
        t=mysql_query(conn,Delete);
    }else if('4'==vfs->cur_cat){
        char Delete[MYSQL_BUF_SIZE_]="delete from ";
        sprintf(Delete,"%s%s where belong=",Delete,MYSQL_TABLE_TWO_);
        sprintf(Delete,"%s%d and procode=%d;",Delete,vfs->belong,vfs->procode);
        puts(Delete);
        t=mysql_query(conn,Delete);
    }else if('5'==vfs->cur_cat){
        char Delete[MYSQL_BUF_SIZE_]="delete from ";
        sprintf(Delete,"%s%s where belong=",Delete,MYSQL_TABLE_TWO_);
        sprintf(Delete,"%s%d and type='%c';",Delete,vfs->belong,vfs->type);
        puts(Delete);
        t=mysql_query(conn,Delete);
    }else{  // normal Delete.
        char Delete[MYSQL_BUF_SIZE_]="delete from ";
        sprintf(Delete,"%s%s where belong=",Delete,MYSQL_TABLE_TWO_);
        sprintf(Delete,"%s%d and code=%d;",Delete,vfs->belong,vfs->code);
        puts(Delete);
        t=mysql_query(conn,Delete);
    }

	if(t)
	{
		printf("Error making delete:%s\n",mysql_error(conn));
	    mysql_close(conn);
        return -1;
	}
	mysql_close(conn);
	return 0;
}
//int main()
//{
//    Vir_File_Sys t;
//    t.belong=17;
//    t.cur_cat='2';
//    strcpy(t.md5sum,"b");
//    deletemysqltabletwo(&t);
//    t.cur_cat='0';
//    return 0;
//}
