#include "factory.h"
int querymysqltabletwo(Vir_File_Sys *vfs)
{
    LOG_REDIRECT_
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    const char* server=MYSQL_SERVER_NAME_;
    const char* user=MYSQL_USER_NAME_;
    const char* password=MYSQL_PASSWORD_;
    const char* database=MYSQL_DATABASES_NAME_;
    const char* table=MYSQL_TABLE_TWO_;
    int t;
    int num=0;

    conn=mysql_init(NULL);
    if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
    {
        printf("Error connecting to database:%s\n",mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    if('2'==vfs->cur_cat)
    {
        char query[MYSQL_BUF_SIZE_]="select procode,name,type,belong,md5sum,cur_cat,code,size from ";
        sprintf(query,"%s%s where md5sum='%s';",query,table,vfs->md5sum);
        puts(query);
        t=mysql_query(conn,query);
    }else if('3'==vfs->cur_cat){
        char query[MYSQL_BUF_SIZE_]="select procode,name,type,belong,md5sum,cur_cat,code,size from ";
        sprintf(query,"%s%s where belong=",query,table);
        sprintf(query,"%s%d and name='%s';",query,vfs->belong,vfs->name);
        puts(query);
        t=mysql_query(conn,query);
    }else if('4'==vfs->cur_cat){
        char query[MYSQL_BUF_SIZE_]="select procode,name,type,belong,md5sum,cur_cat,code,size from ";
        sprintf(query,"%s%s where belong=",query,table);
        sprintf(query,"%s%d and code=%d;",query,vfs->belong,vfs->code);
        puts(query);
        t=mysql_query(conn,query);
    }else if('5'==vfs->cur_cat){
        char query[MYSQL_BUF_SIZE_]="select procode,name,type,belong,md5sum,cur_cat,code,size from ";
        sprintf(query,"%s%s where belong=",query,table);
        sprintf(query,"%s%d and type='%c';",query,vfs->belong,vfs->type);
        puts(query);
        t=mysql_query(conn,query);
    }else if('6'==vfs->cur_cat){
        char query[MYSQL_BUF_SIZE_]="select procode,name,type,belong,md5sum,cur_cat,code,size from ";
        sprintf(query,"%s%s where belong=",query,table);
        sprintf(query,"%s%d and procode=%d;",query,vfs->belong,vfs->procode);
        puts(query);
        t=mysql_query(conn,query);
    }else if('1'==vfs->cur_cat){
        char query[MYSQL_BUF_SIZE_]="select procode,name,type,belong,md5sum,cur_cat,code,size from ";
        sprintf(query,"%s%s where belong=",query,table);
        sprintf(query,"%s%d and cur_cat='%c';",query,vfs->belong,vfs->cur_cat);
        puts(query);
        t=mysql_query(conn,query);
    }else{  // normal query.
        char query[MYSQL_BUF_SIZE_]="select procode,name,type,belong,md5sum,cur_cat,code,size from ";
        sprintf(query,"%s%s where belong=%d;",query,table,vfs->belong);
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
                return 0;
            }
            int j=0;
            do{	
                if(j<VIR_FILE_SYS_MAX_NUM_)
                {
#ifdef DEBUG
                    printf("%d,%d,%s,%c,%d,%s,%c,%d\n",atoi(row[6]),atoi(row[0]),row[1],*row[2],atoi(row[3]),row[4],*row[5],atoi(row[7]));
#endif
                    if((vfs[j].belong=atoi(row[3]))>0)
                    {
                        vfs[j].procode=atoi(row[0]);
                        strcpy(vfs[j].name,row[1]);
                        vfs[j].type=*row[2];
                        if(strlen(row[4])==32)
                        {
                            strcpy(vfs[j].md5sum,row[4]);
                        }else{
                            strcpy(vfs[j].md5sum,"NULL");
                        }
                        vfs[j].cur_cat=*row[5];
                        vfs[j].code=atoi(row[6]);
                        vfs[j].size=atoi(row[7]);
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
        num=mysql_num_rows(res);
        mysql_free_result(res);
    }
    mysql_close(conn);
    return num;
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
