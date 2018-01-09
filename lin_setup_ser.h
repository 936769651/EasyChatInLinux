/*lin_setup.h
the same as server*/
#define SERVER_IP "111.231.102.16"
#define SERVER_PORT "8888"
#define CLIENT_MAX 50
#define NAMEBUF 10
#define BUF 200

#define RED     "\033[0;31m"    //attention 12
#define YELLOW  "\033[0;33m"    //private chat 14
#define GREEN   "\033[0;32m"    //pulic 10
#define DEFAULT "\033[0m"       //default 15

#define NOTICE  0//"#notice#"       //red 12
#define PRIVATE  1  //"#id#"       //yellow 14
#define MYSELF	2 //"#me#"
#define NUM  3//"#n#" 

#define QUIT "quit"
#define C_NOTICE "#notice#"       //red 12
#define C_PRIVATE "#id#"       //yellow 14
#define C_MYSELF  "#me#"
#define C_NUM  "#n#" 
#define NO -1
#define NOT_HAVE 0
#define HAVE 1
#define WELCOMEBUF 1024
#define OUTPUT_FORMAT "%s(%03d): %s\n"
#define WELCOMEFILE "/root/selfstart/welcome"

struct ConUserInfo{
        char flag;
        int id;
        int connect_fd;
};


