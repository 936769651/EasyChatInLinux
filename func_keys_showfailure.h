#include <termios.h>

static struct termios initial_settings, new_settings;  
static int peek_character = -1;
int getch(void);

void getKeys()
{
    struct termios tm, tm_old;
    int fd = 0;
    int ch = 0;
    int i = 0;
    memset(MyInput,0,SAYBUF);
//no problem
    if (tcgetattr(fd, &tm) < 0) {//保存现在的终端设置
        exit(0);
    }
//no problem

    tm_old = tm;
//no problem
    cfmakeraw(&tm);//更改终端设置为原始模式，该模式下所有的输入数据以字节为单位被处理
//no problem
    fflush(stdin);
    fflush(stdout);
    if (tcsetattr(fd, TCSANOW, &tm) < 0) {//设置上更改之后的设置
        exit(0);
    }
    getchar();
    while(true)
    {  
            ch = getchar();
            if(13 == ch)    //ch == '\n'
                break;
            if('-' == ch){
                printf("\b \b");
                MyInput[--i] = '\0'; //if (i == 0) continue
                continue;
            }
            printf("%c",ch);
	        fflush(stdout);
	        MyInput[i++] = ch;
            MyInput[i] = '\0';
        sleep(0.1);
    }

    if (tcsetattr(fd, TCSANOW, &tm_old) < 0) {//更改设置为最初的样子
        exit(0);
    }
}

int getch(void)
{
    struct termios tm, tm_old;
    int fd = 0, ch;

    if (tcgetattr(fd, &tm) < 0) {//保存现在的终端设置
        return -1;
    }

    tm_old = tm;
    cfmakeraw(&tm);//更改终端设置为原始模式，该模式下所有的输入数据以字节为单位被处理
    if (tcsetattr(fd, TCSANOW, &tm) < 0) {//设置上更改之后的设置
        return -1;
    }

    ch = getchar();
    if (tcsetattr(fd, TCSANOW, &tm_old) < 0) {//更改设置为最初的样子
        return -1;
    }

    return ch;
}

