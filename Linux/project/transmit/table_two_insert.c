#include "factory.h"
int virFileInsertSer(Vir_File_Sys *vfs)
{
	MYSQL *conn;
	const char* server=MYSQL_SERVER_NAME_; 
    const char* user=MYSQL_USER_NAME_; 
    const char* password=MYSQL_PASSWORD_;
	const char* database=MYSQL_DATABASES_NAME_;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	    mysql_close(conn);
        return -1;
	}

    int t;
    if('d'==vfs->type)  // catalog file
    {
        char insert[MYSQL_BUF_SIZE_]="insert into vir_file_sys(procode,name,type,belong,cur_cat) values(";
        sprintf(insert,"%s'%d','%s','%c','%d','%c');",insert,vfs->procode,\
                vfs->name,vfs->type,vfs->belong,vfs->cur_cat);
        puts(insert);
        t=mysql_query(conn,insert);
    }else{  // vfs->type == '-' normal file
        char insert[MYSQL_BUF_SIZE_]="insert into vir_file_sys(procode,name,type,belong,md5sum,cur_cat) values(";
        sprintf(insert,"%s'%d','%s','%c','%d','%s','%c');",insert,vfs->procode,\
                vfs->name,vfs->type,vfs->belong,vfs->md5sum,vfs->cur_cat);
        puts(insert);
        t=mysql_query(conn,insert);
    }
    
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
	    mysql_close(conn);
        return -1;
	}else{
		printf("insert success\n");
	}
	mysql_close(conn);
	return 0;
}

//int main()
//{
//    Vir_File_Sys v;
//    v.procode=0;
//    strcpy(v.name,"file");
//    v.type='-';
//    v.belong=10;
//    strcpy(v.md5sum,"123d");
//    virFileInsertSer(&v);
//    return 0;
//}
