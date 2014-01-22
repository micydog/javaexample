#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


int main()
{
	int sockfd;
	int sock_len;
	struct sockaddr_in sock_add;
	int result ;
	char buffer[128];	

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	
	sock_add.sin_family = AF_INET;
	sock_add.sin_addr.s_addr = inet_addr("192.168.1.51");
	sock_add.sin_port = htons(9734);
	sock_len = sizeof(sock_add);

	result = connect(sockfd,(struct sockaddr *)&sock_add,sock_len);

	if(result == -1)
	{
		perror("oops:client2 ");
		exit(1);
	}
	//write(sockfd,(char*)"newclient",8);

	while(strncmp(buffer,"end",3)!=0)
	{
		scanf("%s",buffer);
		write(sockfd,buffer,sizeof(buffer));
				
		printf("send to serv =%s\n",buffer);
		memset(buffer,0,sizeof(buffer));
                read(sockfd,buffer,sizeof(buffer));
		printf("recv from serv =%s\n",buffer);
	}
	close(sockfd);
	exit(0);
}
