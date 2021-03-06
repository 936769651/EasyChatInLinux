#include <termios.h>

static struct termios initial_settings, new_settings;  
static int peek_character = -1;  
void init_keyboard();  
void close_keyboard();  
int kbhit();  
int readch();  
  
void getKeys()
{  
    int ch = 0;  
    int i = 0;
    init_keyboard();
    while(true)
    {  
        if(kbhit())
        {  
            ch = readch();
            if( ('\n' == ch) || (i >= (SAYBUF - 1))  ) {
                break;
            }else if(!isprint(ch)) {    //include control char
                continue;
            }else if('-' == ch){
                if(0 == i)
                    continue;
                MyInput[--i] = '\0';
                printf("\b \b");
                fflush(stdout);
                continue;
            }
            printf("%c",ch);
	        fflush(stdout);
            MyInput[i+1] = '\0';
	        MyInput[i++] = ch;
        }
    }
    close_keyboard();
}
  
void init_keyboard()  
{  
    tcgetattr(0, &initial_settings);  
    new_settings = initial_settings;  
    new_settings.c_lflag &= ~ICANON;  
    new_settings.c_lflag &= ~ECHO;  
    new_settings.c_lflag &= ~ISIG;  
    new_settings.c_cc[VMIN] = 1;  
    new_settings.c_cc[VTIME] = 0;  
    tcsetattr(0,TCSANOW, &new_settings);  
}  
  
void close_keyboard()  
{  
    tcsetattr(0,TCSANOW, &initial_settings);  
}  
  
int kbhit()  
{  
    char ch;  
    int nread;  
      
    if(peek_character != -1)  
    {  
        return -1;  
    }  
    new_settings.c_cc[VMIN] = 0;  
    tcsetattr(0, TCSANOW, &new_settings);  
    nread = read(0, &ch, 1);  
    new_settings.c_cc[VMIN] = 1;  
    tcsetattr(0,TCSANOW, &new_settings);  
  
    if(nread == 1)  
    {  
        peek_character = ch;  
        return 1;  
    }  
    return 0;  
}  
  
int readch()  
{  
    char ch;  
    if(peek_character != -1)  
    {  
        ch = peek_character;  
        peek_character = -1;  
        return ch;  
    }  
    read (0, &ch, 1);  
    return ch;  
}  
