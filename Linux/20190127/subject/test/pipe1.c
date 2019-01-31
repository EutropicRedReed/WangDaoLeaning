#include <func.h>

int main()
{
    FILE *fp1=popen("./1.pipe","r");
    FILE *fp2=popen("./2.pipe","w");
    char buf[128]={0};
    int shmid=shmget((key_t)1000,(size_t)4096,IPC_CREAT|0600);
    char *p=(char*)shmat(shmid,NULL,0);
    size_t ret=fread((void*)p,(size_t)sizeof(char),(size_t)sizeof(buf),fp1);
    if((size_t)-1==ret)
    {
        perror("fread");
        return -1;
    }else if((size_t)0==ret){
        return 0;
    }
    fread((void*)buf,(size_t)sizeof(char),(size_t)sizeof(buf),STDIN_FILENO);
    ret=fwrite((void*)buf,(size_t)sizeof(char),(size_t)sizeof(buf),fp2);
    if((size_t)-1==ret)
    {
        perror("fwrite");
        return -1;
    }
    return 0;
}

