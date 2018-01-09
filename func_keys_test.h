#include<termios.h>
int mygetch(void);
void get_keys(void);
int mygetch(void)
{
	struct termios oldt,newt;
	int ch;
	tcgetattr(STDIN_FILENO,&oldt);
	newt = oldt;
	newt.c_lflag *= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO,TCSANOW,&newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO,TCSANOW,&oldt);
	return ch;
}
void get_keys(void)
{
	int ch;
	int i =0;
	memset(MyInput,0,SAYBUF);
	while(1)
	{
		ch = mygetch();
		if('\n' == ch)
			break;
		putchar(ch);
		fflush(stdout);
		MyInput[i++] = ch;
		MyInput[i] = '\0';
		sleep(0.2);
	}

}