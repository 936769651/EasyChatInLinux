
void createChatLog();
void setName(void);
struct sockaddr_in serAddr(void);
void bindSocket(void);
void connectSer(struct sockaddr_in ser_addr);
void getWelcome(void);
void startChat(void);
void showPack();
void recvPack(void);
void sendPack(void);
void clear(void);
void moveyx(void);
void removeLine(char package[]);
void color(const char *c);

void color(const char *c)
{
    printf("%s",c);
}
struct sockaddr_in serAddr(void)
{
    struct sockaddr_in ser_addr;
    memset(&ser_addr,0,sizeof(struct sockaddr_in));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    ser_addr.sin_port = htons(atoi(SERVER_PORT));
    return ser_addr;
}
void bindSocket(void)
{
    int cli_fd;
    cli_fd = socket(AF_INET,SOCK_STREAM,0);
    if(cli_fd < 0)
    {
        printf("(bindSocket) failure\n");
        exit(-1);
    }
    CliFd = cli_fd;
}
void connectSer(struct sockaddr_in ser_addr)
{
    int ret;
    const int cli_fd = CliFd;
    ret = connect(cli_fd,(const struct sockaddr *)&ser_addr,sizeof(struct sockaddr));
    if(ret != 0)
    {
        printf("(connectSer) failure\n");
        exit(-1);
    }
}
void setName(void)
{
    char *p;
    printf("Input your name(less than 10 character): ");
    fgets(Name,NAMEBUF-1,stdin);
    if(p = strchr(Name,'\n'))
        *p = '\0';
    fflush(stdin);
}
void clear(void)
{
    system("clear");
}
void moveyx(void)
{
    const char * my_input = MyInput;
    printf("\033[%d;%dH",MOVEY,MOVEX);

}
void removeLine(char package[])
{
    char * p;
    p = strchr(package,'\n');
    if(p)
        *p = '\0';
}
