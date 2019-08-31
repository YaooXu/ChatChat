#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
	char buf[1024]={0};
	struct sockaddr_in myaddr;
	struct sockaddr_in cliaddr;
	int socklen = sizeof(cliaddr);

	memset(&myaddr,0,sizeof(myaddr));
	
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	myaddr.sin_port = htons(12517);

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
	//int confd = accept(lisfd, NULL,NULL);
		if(confd == -1)
		{
			printf("accpet\n");
			return -1;
		}

		printf("newclient ip=%s\t,port=%d\n",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));

		recv(confd,buf,sizeof(buf),0);
		printf("recv=%s\n",buf);
		send(confd,buf,strlen(buf),0);

	}






}
