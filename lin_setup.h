/*lin_setup.h
the same as server*/
//server
#define SERVER_IP "111.231.102.16"
#define SERVER_PORT "8888"
//buf
#define CLIENT_MAX 50
#define NAMEBUF 10
#define SAYBUF 150
#define PACKAGEBUF 200
#define COMMAND 300
#define WELCOMEBUF 1024
#define INPUTSLEEP 0.5

//format
#define ROWS 40
#define MOVEY 40
#define MOVEX 0
#define ARROW "\033[1;32m-->\033[0m"
#define PRINTFLOG " tail -n %d \"%s\" "
#define ECHOFORMAT " echo \"%s\" >> \"%s\" "   //echo "str" >>  log   the str must don't have "

//color
#define GREENLEFT "\033[1;32m"
#define REDLEFT "\033[0;31m"
#define NOCOLOR "\033[0m"
//chat file
#define CHATLOG ".chat_log"
#define WELCOMEFILE "/root/selfstart/welcome"

struct ConUserInfo{
        char flag;
        int id;
        int connect_fd;
};


char Name[NAMEBUF];
FILE * FpLog;
int CliFd;
char MyInput[SAYBUF] = "\0";
char showPackCommand[COMMAND];