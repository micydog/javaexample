#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BUFFSIZ 20

int main(void)
{

	int data_processed;
	int file_pipe[2];
	const char some_data[]="123";
	const char some_data1[]="234";
	char buffer[BUFFSIZ+1];
	pid_t fork_result;
	memset(buffer,'\0',sizeof(buffer));
	if(pipe(file_pipe)==0){
	fork_result = fork();
	if(fork_result == -1){ fprintf(stderr,"fork failure");
		exit(EXIT_FAILURE);
	
	}
	if(fork_result==0){
		//sleep(2);//加上这个休眠即可一次收倒6个字符，而在下一个READ中阻塞
		data_processed = read(file_pipe[0],buffer,BUFSIZ);
		printf("Read %d bytes:%s\n",data_processed,buffer);
		data_processed = read(file_pipe[0],buffer,BUFSIZ);
		printf("Read2 %d bytes:%s\n",data_processed,buffer);
		exit(EXIT_SUCCESS);
	}
	else {
	int i=0,sum=0;
	//sleep(2);
	for(;i<200;i++)
	{data_processed = write(file_pipe[1],some_data,strlen(some_data));
	sum+=data_processed;
	}
	printf("word %d bytes\n",sum);
	sleep(2);
	data_processed = write(file_pipe[1],some_data1,strlen(some_data1));
        printf("word2  %d bytes\n",data_processed);

	}
	}
	exit(EXIT_SUCCESS);
}
