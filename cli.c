#include "lin_head.h"
#include "lin_setup.h"
#include "func.h"
#include "func_keys.h"
#include "showLog.c"

int main(void)
{
        struct sockaddr_in ser_addr;

        clear();
        createChatLog();    //get FpLog
	showLog();
        setName();      //get Name
        ser_addr = serAddr();   //get ser_addr
        bindSocket();   //bind CliFd
        connectSer(ser_addr);    //CliFd connect server

    	fflush(stdin);
        getWelcome();
        startChat();
        close(CliFd);
        return 0;
}

void startChat()
{ 
	pthread_t pid1;
	pthread_create(&pid1,NULL,(void *)recvPack,NULL);   //recv pack and echo >> chat.log
	sendPack();    // at xy input and send to server
}

void sendPack(void)
{
	char package[PACKAGEBUF];
	char say[SAYBUF];
	int ret;
    const int cli_fd = CliFd;
	while(true)
	{
		strcpy(package,Name);
        strcat(package,": ");
		getKeys();
		if(strncmp(MyInput,"quit",4) == 0)
		{
			send(cli_fd,MyInput,strlen(MyInput),0);
			break;
		}
		strcat(package,MyInput);
		ret = send(cli_fd,package,strlen(package),0);
		if(ret < 0)
		{
			printf("(sendPack) failure\n");
			break;
		}
        sleep(0.5);
	}

}
void recvPack()
{
	char package[PACKAGEBUF];
    char command[COMMAND];
	int ret;
    const int cli_fd = CliFd;
	while(true)
	{
        showPack();
		ret = recv(cli_fd,package,PACKAGEBUF,0);
		if(ret <= 0)
		{
			printf("(recvpack) failure\n");
			close(cli_fd);
			exit(-1);
		}
		package[ret] = '\0';
        removeLine(package);
        sprintf(command,ECHOFORMAT,package,CHATLOG);
        system(command);        //put package info to CHATLOG
	}
}
void showPack()
{
    char command[COMMAND];
    memset(command,0,COMMAND);
    sprintf(command,PRINTFLOG,ROWS,CHATLOG);
    clear();
    system(command);
    moveyx();           //MOVEY,MOVEX
    printf("%s: %s",Name,MyInput);
    fflush(stdout);
}
void getWelcome()
{
        char package[PACKAGEBUF];
        char command[COMMAND];
        int ret;
        const int cli_fd = CliFd;
        ret = recv(cli_fd,package,PACKAGEBUF,0);
        if(ret <= 0)
        {
                printf("(getWelcome) failure\n");
                close(cli_fd);
                exit(-1);
        }
        package[ret] = '\0';
        sprintf(command,ECHOFORMAT,package,CHATLOG);
        system(command);        //put package info to CHATLOG

}
void createChatLog(void)
{
    FILE * fp;
    fp = fopen(CHATLOG,"w");
    if(fp == NULL)
    {
        printf("(openChatLog) error");
        exit(-1);
    }
    fclose(fp);
    FpLog = fp;
}



