/*lin_setup.h
the same as server*/
//ip
#define SERVER_IP "111.231.102.16"
#define SERVER_PORT "8888"

//buf
#define CLIENT_MAX 20
#define NAMEBUF 10
#define SAYBUF 150
#define PACKAGEBUF 200
#define COMMAND 300
#define WELCOMEBUF 1024

//format
#define ROWS 40
#define MOVEY 40
#define MOVEX 0
#define PRINTFLOG " tail -n %d \"%s\" "
#define ECHOFORMAT " echo \"%s\" >> \"%s\" "   //echo "str" >>  log   the str must don't have "


#define CHATLOG "chat.log"

struct ConUserInfo{
        char flag;
        int id;
        int connect_fd;
};


char Name[NAMEBUF];
FILE * FpLog;
int CliFd;
char MyInput[SAYBUF] = "\0";