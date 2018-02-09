#include "lin_head.h"
#include "lin_setup.h"
#include "lin_setup_ser.h"
#include <signal.h>
void signal_handler(int sigm);
int bindSocket(void);
void InitiaConUserList(void);
void GetWelcome();
bool peopleOverLimit(void);
int acceptCli(int ser_fd);
void thread(void * temp_fd);
        int addUser(int con_fd);
                bool sendWelcome(int con_fd);
                    void addWelToPack(char package[]);
                void recvAndSend(int id,int con_fd);
                	void publish(int id,const char package[]);
                		int getKind(const char package[]);
        void cleanUserInfo(int id);

int People = 0;
char Welcome[WELCOMEBUF] = {'\0'};
struct ConUserInfo ConUserList[CLIENT_MAX];
char Name[NAMEBUF]; 
int main(void)
{
        int ser_fd,con_fd;
        pthread_t pid;

        ser_fd = bindSocket();
        InitiaConUserList();
        GetWelcome();
        listen(ser_fd,5);
        while(true)
        {
		if(peopleOverLimit())
		{
			sleep(10);
			continue;
		}
        	con_fd = acceptCli(ser_fd);
			pthread_create(&pid,NULL,(void *)thread,(void *)&con_fd);
               
        }
        return 0;
}
int acceptCli(int ser_fd)
{
	int con_fd;
	struct sockaddr_in cli_addr;
	socklen_t addr_len = sizeof(struct sockaddr_in);
	while(true)
	{
		con_fd = accept(ser_fd,(struct sockaddr *)&cli_addr,&addr_len);
		if(con_fd >= 0)
			return con_fd;
	}
	printf("Have people\n");
	
}
void thread(void * temp_fd)
{
        const int con_fd = *(int *)temp_fd;
        int id;
        ++People;
        id = addUser(con_fd);
        if(sendWelcome(con_fd))
        	recvAndSend(id,con_fd);
        close(con_fd);
        cleanUserInfo(id);
        --People;
        printf("ID%d quit\n",id);
}
int addUser(int con_fd)
{
        int id;
        const struct ConUserInfo * user = ConUserList;
        for(id = 1;id <= CLIENT_MAX;id++)
        {
                if(NOT_HAVE == user[id].flag)
                        break;
        }
        ConUserList[id].flag = HAVE;
        ConUserList[id].connect_fd = con_fd;
        
        printf("adduser success,ID%d,people have %d\n",id,People);
        return(id);
}
bool sendWelcome(int con_fd)
{
        int ret,i;
        char package[BUF];
        memset(package,0,BUF);

        addWelToPack(package);
        ret = send(con_fd,package,BUF,0);
        if(ret < 0)
        {
                perror("(sendWelcome) failure\n");
                return false;
        }
        return true;
}
void recvAndSend(int id,int con_fd)
{
        char package[BUF];
        int ret;
        while(true)
        {
                ret = recv(con_fd,package,BUF,0);
                if(ret < 0)
                {
					printf("(recvAndSend) recv trans failure\n");
                    fflush(stdout);
                    break;
                }
                if(ret == 0)
                {
                	printf("(recvAndSend) recv wait failure\n");
                	break;
				}
                package[ret] = '\0';
		printf("%s",package);
		fflush(stdout);
                if(strncmp(package,QUIT,4) == 0)
                	break ;
                publish(id,package);
           
        }
}
void publish(int id,const char package[])
{
        int i,ret;
        const struct ConUserInfo *user = ConUserList;
        for(i = 1;i < CLIENT_MAX;i++)
        {
                if(HAVE == user[i].flag)
                {
                        ret = send(user[i].connect_fd,package,strlen(package),0);
                        if(ret < 0)
                        {
                                printf("(publish) to ID%d failure\n",i);
                        }
                }
        }
}

bool peopleOverLimit(void)
{
        return (People>(CLIENT_MAX - 3)?true:false);
}
int bindSocket(void)
{
        int ser_fd;
        struct sockaddr_in ser_addr;
        socklen_t addr_len = sizeof(struct sockaddr_in);
        ser_fd = socket(AF_INET,SOCK_STREAM,0);
        if(ser_fd < 0)
        {
                perror("(bindSocket) socket failure\n");
		exit(-1);
        }
        memset(&ser_addr,0,addr_len);
        ser_addr.sin_family = AF_INET;
        ser_addr.sin_addr.s_addr = INADDR_ANY;
        ser_addr.sin_port = htons(atoi(SERVER_PORT));

        if(bind(ser_fd,(struct sockaddr *)&ser_addr,sizeof(struct sockaddr)) < 0)
        {
                perror("(bindSocket) bind failure\n");
		close(ser_fd);
                exit(-1);
        }
        return ser_fd;
}
void InitiaConUserList(void)
{
        int i;
        for(i = 0;i < CLIENT_MAX;i++)
        {
                ConUserList[i].flag = NOT_HAVE;
                ConUserList[i].id = i;
                ConUserList[i].connect_fd = NO;
        }
        printf("(InitiaConUserList) success\n");
}
void GetWelcome()
{
        FILE * fp;
        char ch;
        fp = fopen(WELCOMEFILE,"r");
        if(NULL == fp)
        {
                perror("(GetWelcome)fopen failure\n");
        }
        rewind(fp);
        fgets(Welcome,WELCOMEBUF,fp);
        fclose(fp);
}
void cleanUserInfo(int id)
{
        ConUserList[id].flag = NOT_HAVE;
        ConUserList[id].connect_fd = NO;
        printf("CleanUserInfo ID%d success\n",id);
}
void addWelToPack(char package[])
{
        strcat(package,Welcome);
}
void signal_handler(int sigm)
{
	struct sigaction act;  
	memset(&act,0,sizeof(act));  
	 act.sa_handler = SIG_IGN;//设定接受到指定信号后的动作为忽略  
	act.sa_handler = signal_handler;//设定接受到指定信号后的动作为 相关函数  
	act.sa_flags = 0;  
	sigemptyset(&act.sa_mask);  
	sigaction(SIGPIPE,&act,NULL);//屏蔽SIGPIPE信号  
	sigaction(SIGCHLD,&act,NULL);//屏蔽子进程终结信号，让init进程去处  

}


