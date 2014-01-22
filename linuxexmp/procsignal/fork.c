#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	pid_t pid;
	char *mes;
	int n;
	int exit_code;
        pid=fork();

	switch(pid)
	{
	case -1:
		perror("fork failed");
		exit(1);
	case 0:
		mes="This is the child";
		n=5;
		exit_code=37;
		break;
	default:
		mes="This is the parent";
		n=3;
		exit_code=0;
		break;
	}
	for (;n>0;n--)
	{	
		printf("n=%d",n);
		puts(mes);
		sleep(1);
	}
	exit(0);
}
	


