#include "factory.h"
 
int myGetPasswd(char *buf)
{
    LOG_REDIRECT_
	int input;
    int i=0;
	struct termios save, current;
	tcgetattr(0, &save);// 得到原来的终端属性
	current = save;
	current.c_lflag &= ~ICANON;// 设置非正规模式，如果程序每次要从终端读取一个字符的话，这是必须的
	current.c_lflag &= ~ECHO;// 关闭回显
	current.c_cc[VMIN] = 1;// 设置非正规模式下的最小字符数
	current.c_cc[VTIME] = 0;// 设置非正规模式下的读延时
	tcsetattr(0, TCSANOW, &current);// 设置新的终端属性
	printf("Please input passwd:\n");
	while((input = getchar()) != 10){
        buf[i++]=input;
	}
    buf[i]=0;
	tcsetattr(0, TCSANOW, &save);// 恢复原来的终端属性，以免干扰shall和之后的程序运行
	return 0;
}
//int main()
//{
//    char buf[20]={0};
//    myGetPasswd(buf);
//    printf("%s\n",buf);
//    return 0;
//}

