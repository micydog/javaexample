#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include<string.h>

int main()
{
	int serv_sockfd,client_sockfd;
	int serv_len,client_len;
	struct sockaddr_in serv_add;
	struct sockaddr_in client_add;
	int result;
	fd_set readfds,testfds;
	serv_sockfd = socket(AF_INET,SOCK_STREAM,0);
	
	serv_add.sin_family = AF_INET;
	//serv_add.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_add.sin_addr.s_addr = inet_addr("192.168.1.51");
	serv_add.sin_port = htons(9734);
	serv_len =  sizeof(serv_add);
	struct timeval timeout;
	timeout.tv_sec = 5;
	timeout.tv_usec = 500000;
		
	bind(serv_sockfd,(struct sockaddr *)&serv_add,serv_len);
	listen(serv_sockfd,500);
	
	FD_ZERO(&readfds);
	FD_SET(serv_sockfd,&readfds);
	printf("servsockfd %d\n",serv_sockfd);	

	while(1)
	{
		char buffer[128];
		int fd;
		int nread;
		testfds = readfds;
		printf("server waiting\n");
		//printf("fdsize is %d\n",FD_SETSIZE);
		result = select (FD_SETSIZE,&testfds,(fd_set*)NULL,(fd_set*)NULL,0);
		
		if(result <0)
		{
			perror("server2");
			exit(1);
		}

		if(result == 0)
			continue;
		
		for(fd=0;fd<FD_SETSIZE;fd++)
		{
			if(FD_ISSET(fd,&testfds)){
				if(fd==serv_sockfd){
					client_len = sizeof(client_add);
					client_sockfd = accept(serv_sockfd,(struct sockaddr*)&client_add,&client_len);
					FD_SET(client_sockfd,&readfds);
					printf("adding client on fd %d \n",client_sockfd);
				}
			
				else
				{
					ioctl(fd,FIONREAD,&nread);
				
					if(nread==0&&fd!=serv_sockfd){
					
						close(fd);
						FD_CLR(fd,&readfds);
						printf("removing client on fd %d\n",fd);
					}
					else
					{
						memset(buffer,0,sizeof(buffer));
						read(fd,buffer,sizeof(buffer));
						usleep(1000);
						write(fd,"hello!!",7);
						usleep(2000);
						printf("serving client on fd %d\n",fd);
						printf("recv chars is %s\n",buffer);
					//ch++;
					//write(fd,&ch,1);
					}			
				}
			}
		}
	}
}
