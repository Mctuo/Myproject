#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<assert.h>
#include<arpa/inet.h>

int main()
{
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	assert(sockfd !=-1);

	struct sockaddr_in saddr,caddr;
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(6000);
	saddr.sin_addr.s_addr=inet_addr("172.21.0.16");

	int res=bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));

	listen(sockfd,5);

	while(1)
	{
		int len=sizeof(caddr);
		int c=accept(sockfd,(struct sockaddr*)&caddr,&len);
		if(c < 0)
		{
			printf("accept failed!\n");
			continue;
		}
		printf("accept c=%d\n",c);
		char buf[128]={0};
		
		int n=recv(c,buf,127,0);
		if(n <0)
		{
			printf("server recv error!\n");
			continue;
		}
		if(n == 0)
		{
			printf("server check client close!\n");
			continue;
		}
		
		send(c,"i get the request!",18,0);
		memset(buf,0,strlen(buf));
		close(c);
	}
	close(sockfd);
}
