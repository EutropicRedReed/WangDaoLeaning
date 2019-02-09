#include <func.h>

struct msgbuf{
    long mtype;
    char mtext[512];
};

int main()
{
    FILE *fp1=popen("./1.pipe","w");
    FILE *fp2=popen("./2.pipe","r");
    char buf[128]={0};
    int msgid=msgget(1000,IPC_CREAT|0600);
    size_t ret=fread((void*)buf,(size_t)sizeof(char),(size_t)sizeof(buf),fp2);
    if((size_t)-1==ret)
    {
        perror("fread");
        return -1;
    }else if((size_t)0==ret){
        return 0;
    }
    struct msgbuf msgbuf;
    msgbuf.mtype=1;
    memset(msgbuf.mtext,0,sizeof(msgbuf.mtext));
    strcpy(msgbuf.mtext,buf);
    msgsnd(msgid,&msgbuf,(size_t)sizeof(msgbuf.mtext),0);

    fread((void*)buf,(size_t)sizeof(char),(size_t)sizeof(buf),STDIN_FILENO);
    ret=fwrite((void*)buf,(size_t)sizeof(char),(size_t)sizeof(buf),fp1);
    if((size_t)-1==ret)
    {
        perror("fwrite");
        return -1;
    }
    return 0;
}

