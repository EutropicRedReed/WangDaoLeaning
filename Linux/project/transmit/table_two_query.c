#include "factory.h"
int querymysqltabletwo(Vir_File_Sys *vfs)
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

    if('2'==vfs->cur_cat)
    {
        char query[MYSQL_BUF_SIZE_]="select procode,name,type,belong,md5sum,cur_cat from ";
        sprintf(query,"%s%s where belong=",query,MYSQL_TABLE_TWO_);
        sprintf(query,"%s%d and md5sum='%s';",query,vfs->belong,vfs->md5sum);
        puts(query);
        t=mysql_query(conn,query);
    }else if('3'==vfs->cur_cat){
        char query[MYSQL_BUF_SIZE_]="select procode,name,type,belong,md5sum,cur_cat from ";
        sprintf(query,"%s%s where belong=",query,MYSQL_TABLE_TWO_);
        sprintf(query,"%s%d and name='%s';",query,vfs->belong,vfs->name);
        puts(query);
        t=mysql_query(conn,query);
    }else if('4'==vfs->cur_cat){
        char query[MYSQL_BUF_SIZE_]="select procode,name,type,belong,md5sum,cur_cat from ";
        sprintf(query,"%s%s where belong=",query,MYSQL_TABLE_TWO_);
        sprintf(query,"%s%d and cur_cat='%c';",query,vfs->belong,vfs->cur_cat);
        puts(query);
        t=mysql_query(conn,query);
    }else if('5'==vfs->cur_cat){
        char query[MYSQL_BUF_SIZE_]="select procode,name,type,belong,md5sum,cur_cat from ";
        sprintf(query,"%s%s where belong=",query,MYSQL_TABLE_TWO_);
        sprintf(query,"%s%d and type='%c';",query,vfs->belong,vfs->type);
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
                if(j<VIR_FILE_SYS_MAX_NUM_)
                {
#ifdef DEBUG
                    printf("%d,%s,%c,%d,%s,%c\n",atoi(row[0]),row[1],*row[2],atoi(row[3]),row[4],*row[5]);
#endif
                    if((vfs[j].belong=atoi(row[3]))>0)
                    {
                        vfs[j].procode=atoi(row[0]);
                        strcpy(vfs[j].name,row[1]);
                        vfs[j].type=*row[2];
                        if(0==strlen(row[4]))
                        {
                            strcpy(vfs[j].md5sum,row[4]);
                        }else{
                            strcpy(vfs[j].md5sum,"NULL");
                        }
                        vfs[j].cur_cat=*row[5];
                    }
                    j++;
                }
                if(j==VIR_FILE_SYS_MAX_NUM_)
                {
                    break;
                }
            }while(NULL!=(row=mysql_fetch_row(res)));
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
//    Vir_File_Sys t[VIR_FILE_SYS_MAX_DEEP_];
//    t[0].belong=17;   // 17 -> table one procode ~ name -> table three name ~ fd.  two query.
//    querymysqltabletwo(t);
//    int i;
//    for(i=0;i<VIR_FILE_SYS_MAX_DEEP_;i++)
//    {
//        if(t[i].belong==17)
//        {
//            printf("%d,%s,%c,%d,%s,%c\n",t[i].procode,t[i].name,t[i].type,t[i].belong,t[i].md5sum,t[i].cur_cat);
//        }
//    }
//    Vir_File_Sys t1;
//    t1.belong=17;
//    querymysqltabletwo(&t1);
//    printf("%d,%s,%c,%d,%s,%c\n",t1.procode,t1.name,t1.type,t1.belong,t1.md5sum,t1.cur_cat);
//    return 0;
//}
