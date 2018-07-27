/*************************************************************************
	> File Name: midser.c
	> Author: 
	> Mail: 
	> Created Time: Tue 19 Jun 2018 03:37:11 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<assert.h>

int main()
{
    int sockfd =socket(AF_INET,SOCK_STREAM,0);
    assert(sockfd != 1);

    struct sockaddr_in saddr,caddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port=htons(6001);
    saddr.sin_addr.s_addr=inet_addr("172.21.0.16");
    int res=bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
    //这里首先是绑定mid_ser的端口和ip
    
    int serfd=socket(AF_INET,SOCK_STREAM,0);
    assert(serfd != -1);
    struct sockaddr_in ser_addr;
    ser_addr.sin_family=AF_INET;
    ser_addr.sin_port=htons(6000);
    ser_addr.sin_addr.s_addr=inet_addr("172.21.0.16");
    int con_ser=connect(serfd,(struct sockaddr*)&ser_addr,sizeof(ser_addr));
    char buf[128]={0};
    send(serfd,"mid_ser ready!",15,0);
    memset(buf,0,128);
    //先连上主服务器server,再连接客户端
    
    listen(sockfd,5);

    while(1)
    {
        int len=sizeof(caddr);
        int c =accept(sockfd,(struct sockaddr*)&caddr,&len);
        
        int n=recv(c,buf,127,0);
        if(n < 0)
        {
            printf("recv failed!\n") ;
            continue;
        }
        printf("recv buf:%s\n",buf);
        
        send(serfd,buf,strlen(buf),0);

        memset(buf,0,128);
        recv(serfd,buf,127,0);

        send(c,buf,strlen(buf),0);

        char req[20]="server finished!";
        send(c,req,strlen(req),0);

        memset(buf,0,128);
        close(c);
    }
    close(sockfd);
}
