#include <signal.h>  
#include <unistd.h>  
#include <stdio.h>  
   

static void sig_int(int); 
static void pr_mask(const char*); 
 int main(void){  
     sigset_t newmask,oldmask,waitmask;  
       
//     pr_mask("program start:\n");//前面我们定义的打印信号掩码的函数  
       
     if(signal(SIGINT, sig_int) == SIG_ERR){  
         perror("signal");  
         return 1;  
     }  
   
     sigemptyset(&waitmask);  
     sigaddset(&waitmask,SIGUSR1);  
     sigemptyset(&newmask);  
     sigaddset(&newmask,SIGINT);  
       
     /* block SIGINT and save current signal mask */  
     if(sigprocmask(SIG_BLOCK,&newmask,&oldmask) < 0){  
         perror("sigprocmask");  
         return 1;  
     }  
       
     pr_mask("in critical region: ");  
   
     /* pause, allowing all signals except SIGUSR1. */     
     if(sigsuspend(&waitmask) != -1){  
         perror("sigsuspend");  
         return 1;  
     }  
    
     pr_mask("after return from sigsuspend:");  
       
     /* reset signal mask with unblock SIGINT */  
     if(sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0){  
         perror("sigmaskproc");  
         return 1;  
     }  
   
     pr_mask("program exit:\n");  
     return 0; 
 } 

 static void sig_int(int signo){  
     printf("caught SIGINT\n");  
 	 if( signal(SIGINT, SIG_DFL) == SIG_ERR)  
         perror("SIGINT");    
          
 }  

static void pr_mask(const char *str){
     sigset_t sigset;
     int errno_save;


     if(sigprocmask(0,NULL,&sigset) < 0){
         perror("sigprocmask");
         return;
     }
     printf("this is prmask\n");
     printf("%s",str);
     if(sigismember(&sigset,SIGINT)) printf("SIGINT");
     if(sigismember(&sigset,SIGQUIT)) printf("SIGQUIT");
     if(sigismember(&sigset,SIGUSR1)) printf("SIGUSR1");
     if(sigismember(&sigset,SIGALRM)) printf("SIGALRM");
        return;
}




 
