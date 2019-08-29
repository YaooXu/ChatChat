#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <mysql/mysql.h>
#include "mysql_helper.h"
int clientfd[1024]={0};


/* 返回值0为正常，用户不存在返回1，密码错误发生错误返回-1， */  
int userLogin(char *buf)
{

	char uName[32]={0};
	char pWord[32]={0};
	sscanf(buf+2,"%[^|]|%s",uName,pWord);
	char sqlStr[1024]={0};
	sprintf(sqlStr,"%s'%s'", "select password from User where Name=",uName);
	printf("sqlStr=%s\n",sqlStr);
    MYSQL *mysql = mysql_init(NULL);           // 创建一个MYSQL句柄并初始化
    if (!mysql) {
        my_error("mysql_init", __LINE__);
    }
    mysql_connect(mysql);
	if(mysql_query(mysql,sqlStr) != 0)
	{
		printf("%s\n",mysql_error(mysql));
		close_connection(mysql);
		return -1;
	}
	MYSQL_RES *result;
	result = mysql_store_result(mysql); //result为数据库中取出的密码列表
	close_connection(mysql);
	if(result == NULL)
	{
		printf("%s\n",mysql_error(mysql));
		return -1;
	}
	

	MYSQL_ROW  row;
	if((row = mysql_fetch_row(result))==NULL)
		{
			printf("用户不存在\n");
			return 1;
		}	//	
		if(strcmp(row[0], pWord) == 0)
		{
			printf("用户：%s登录成功\n",uName);
			return 0;
		}
		else
		{
			printf("密码错误\n");
			return 2;
		}
}


int userRegister(char *buf){
	char uName[32]={0};
	char pWord[32]={0};
	sscanf(buf+2,"%[^|]|%s",uName,pWord);
	char field[50]="Name,Password";
	char table_name[50]="User";
	char message[50]={0};
	sprintf(message,"'%s','%s'",uName,pWord);

	/*数据库连接*/
    MYSQL *mysql = mysql_init(NULL);           
    if (!mysql) {
        my_error("mysql_init", __LINE__);
    }
    mysql_connect(mysql);
	insert_data(mysql,field,table_name,message);
	close_connection(mysql);

}


void * handClient(void *arg)
{
	char buf[1024]={0};
	int *p = arg;
	int confd = *p;
	while(1)
	{
		if(recv(confd,buf,sizeof(buf),0) == 0)
		{
			pthread_exit(NULL);
		}
		printf("recv=%s\n",buf);
		switch(buf[0])
		{
			case '1':
				userRegister(buf);
				break;
			case '2':
				userLogin(buf);
				break;


		}
		//send(confd,buf,strlen(buf),0);
	}

}

int main()
{
	int i = 0;
	pthread_t tid;
	struct sockaddr_in myaddr;
	struct sockaddr_in cliaddr;
	int socklen = sizeof(cliaddr);

	memset(&myaddr,0,sizeof(myaddr));
	
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = inet_addr("172.17.209.241");
	myaddr.sin_port = htons(15128);

	int lisfd = socket(AF_INET,SOCK_STREAM,0);
	if(lisfd == 0)
	{
		printf("socket error\n");
		return -1;
	}
	 //给描述符绑定地址
	if(bind(lisfd, (struct sockaddr*)&myaddr,sizeof(myaddr)) != 0)
	{
		printf("bind error\n");
		return -1;
	}
	listen(lisfd, 10);
	printf("begin accpet\n");
	while(1)
	{
		int confd = accept(lisfd, (struct sockaddr*)&cliaddr,&socklen);
		if(confd == -1)
		{
			printf("accpet\n");
			return -1;
		}

		clientfd[i] = confd;
		i++;

		printf("newclient ip=%s\t,port=%d\n",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));

		pthread_create(&tid,NULL,handClient,&clientfd[i-1]);

		

	}
}

