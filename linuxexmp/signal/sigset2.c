#include <signal.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <sys/types.h>

void ouch(int sig)
{
	printf("ouch i got signal %d \n",sig);
}

int main(void)
{
sigset_t mask; 
struct sigaction action;
sigemptyset(&action.sa_mask);
action.sa_handler=ouch;
action.sa_flags = SA_RESTART;
sigaction(SIGINT,&action,NULL);
sleep(3);
kill(getpid(),SIGINT);
   
     sigfillset(&mask);  
     //sigdelset(&mask,SIGINT);  
     sigprocmask(SIG_SETMASK,&mask,NULL);

	printf("new mask now\n");

	
     sleep(3);		  
     kill(getpid(),SIGINT);
     sigdelset(&mask,SIGINT);
	sigprocmask(SIG_SETMASK,&mask,NULL);
     printf("old mask now\n");
     sleep(2);
	kill(getpid(),SIGINT); 
     exit(1);  


}
