#include "factory.h"
int updatemysqltabletwo(Vir_File_Sys *vfs)
{
	MYSQL *conn;
	const char* server=MYSQL_SERVER_NAME_;
	const char* user=MYSQL_USER_NAME_;
	const char* password=MYSQL_PASSWORD_;
	const char* database=MYSQL_DATABASES_NAME_;
    const char* table=MYSQL_TABLE_TWO_;
	int t=0;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	    mysql_close(conn);
        return -1;
	}

    if('3'==vfs->cur_cat){
        char update[MYSQL_BUF_SIZE_]="update ";
        sprintf(update,"%s%s set",update,table);
        sprintf(update,"%s md5sum='%s'",update,vfs->md5sum);
        sprintf(update,"%s where code=%d",update,vfs->code);
        puts(update);
        t=mysql_query(conn,update);
    }else if('4'==vfs->cur_cat){
        char update[MYSQL_BUF_SIZE_]="update ";
        sprintf(update,"%s%s set",update,table);
        sprintf(update,"%s name='%s'",update,vfs->name);
        sprintf(update,"%s where code=%d",update,vfs->code);
        puts(update);
        t=mysql_query(conn,update);
    }else if('5'==vfs->cur_cat){
        char update[MYSQL_BUF_SIZE_]="update ";
        sprintf(update,"%s%s set",update,table);
        sprintf(update,"%s procode=%d",update,vfs->procode);
        sprintf(update,"%s where code=%d",update,vfs->code);
        puts(update);
        t=mysql_query(conn,update);
    }else if('6'==vfs->cur_cat){
        char update[MYSQL_BUF_SIZE_]="update ";
        sprintf(update,"%s%s set",update,table);
        sprintf(update,"%s size=%ld",update,vfs->size);
        sprintf(update,"%s where code=%d",update,vfs->code);
        puts(update);
        t=mysql_query(conn,update);
    }else{
        char update[MYSQL_BUF_SIZE_]="update ";
        sprintf(update,"%s%s set",update,table);
        sprintf(update,"%s cur_cat=%c",update,vfs->cur_cat);
        sprintf(update,"%s where code=%d",update,vfs->code);
        puts(update);
        t=mysql_query(conn,update);
    }

    if(t)
	{
        printf("Error making update:%s\n",mysql_error(conn));
        mysql_close(conn);
        return -1;
	}
	mysql_close(conn);
	return 0;
}

