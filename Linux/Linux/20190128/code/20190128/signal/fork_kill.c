#include <func.h>

int main(int argc,char** argv)
{
    if(!fork())
    {
        //int ret=kill(0,SIGINT);
        while(1);
    }else{
        wait(NULL);
        while(1);
    }
    return 0;
}

