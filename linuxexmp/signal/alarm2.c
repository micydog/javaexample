#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int alarm_fired=0;
void ding(int sig)
{
	if(sig==SIGALRM)
	{	printf("sigalrm begin\n");	
		alarm_fired=1;
	}
	else
	{
		if(sig==SIGUSR1)
		{
			printf("siguser1 begin\n");
			alarm_fired=2;
		}	
	}
}

int main()
{
	pid_t pid;
	printf("alarm application staring\n");
	pid=fork();
	switch(pid)
	{
		/*failed*/
		case -1:
		perror("fork failed");
		exit(1);
		case 0:
		sleep(10);
		kill(getppid(),SIGUSR1);
		
		exit(0);


	}
	printf("waiting for alarm to go off\n");
	signal(SIGUSR1,ding);


	signal(SIGALRM,ding);
 	alarm(15);
	
	pause();
	if(alarm_fired)
		printf("ding\n");
	printf("done\n");
	sleep(8);
	exit(0);



}




