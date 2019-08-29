#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <mysql/mysql.h>
#include "mysql_helper.h"
#include <map>
#include<vector>
using namespace std;
map<int,int>clientfd;

struct UserInformation
{
	const int userid;
	const int userfd;
	const char ipaddr[32];
};

/* 返回值0为正常，用户不存在返回1，密码错误发生错误返回-1， */  
int userLogin(char *buf)
{

	char uId[32]={0};
	char pWord[32]={0};
	/*TODO



	sscanf(buf+2,"%[^|]|%s",uId,pWord);
	*/
	char sqlStr[1024]={0};
	sprintf(sqlStr,"%s'%s'", "select Password from User where Id=",uId);
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
			printf("用户：%s登录成功\n",uId);
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
	struct  UserInformation *p = static_cast<struct  UserInformation*>(arg);
	int confd = p->userfd;
	while(1)
	{
		if(recv(confd,buf,sizeof(buf),0) == 0)
		{	printf("用户 %d 已退出",p->userid);
			clientfd.erase(p->userid);
			delete[] p;
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
	myaddr.sin_addr.s_addr = inet_addr("172.17.210.103");
	myaddr.sin_port = htons(15129);

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
		int confd = accept(lisfd, (struct sockaddr*)&cliaddr,(socklen_t*)&socklen);
		if(confd == -1)
		{
			printf("accpet\n");
			return -1;
		}
		char buf[1005]={0};
		int userid=0;
		recv(confd,buf,sizeof(buf),0);
		/*TODO
		if regrister
		{

		}
		else login
		{

		}
		userid =;
		clientfd[userid]=confd;
		*/
		clientfd[userid] = confd;
		printf("newclient ip=%s\t,port=%d\n",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));
		struct  UserInformation* newuser=new struct  UserInformation(
		 {
			userid,
			confd,
			*inet_ntoa(cliaddr.sin_addr)
		});
		pthread_create(&tid,NULL,handClient,newuser);

		

	}
}

