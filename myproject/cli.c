#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<assert.h>
#include<arpa/inet.h>
#include<string.h>

int main()
{
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	assert(sockfd != -1);

	struct sockaddr_in saddr,caddr;
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(6001);

	saddr.sin_addr.s_addr=inet_addr("172.21.0.16");

	char buf[128]={0};

	int con=connect(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
	if(con <0)
	{
		printf("connect failed!\n");
		exit(0);
	}
	printf("please input:\n");
	fgets(buf,127,stdin);

	send(sockfd,buf,strlen(buf),0);
	memset(buf,0,128);

	int n=	recv(sockfd,buf,127,0);
	
	if(n ==0 )
	{
	   printf("ser close!\n");
	} 
	if(n < 0 )
	{
		printf("client recv failed!\n");
	}
	else
		printf("recv:%s\n",buf);

	close(sockfd);
}
