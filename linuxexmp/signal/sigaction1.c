#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <setjmp.h>

void sig_handler(int);
void count_prime(int);

int main(int argc, char **argv)
{
 struct sigaction nact;
 int i;
 
 if(argc < 2) {
  printf("Usage: argv[0] <number> \n\n");
  exit(1);
 }
 
 i = atoi(argv[1]);
 nact.sa_handler = sig_handler;
 nact.sa_flags = SA_RESTART;
 
 sigaction(SIGINT, &nact, NULL);
 printf("****************************************************************************/n");
 count_prime(i);
 printf("****************************************************************************/n");
 
 exit(0);
}

void sig_handler(int sig)
{
 printf("SIGINT is caught\n");

 return;
}

void count_prime(int num)
{
 static int j, k = 2;
 static unsigned int total = 0;


 puts("counting ...");
 
 for(; k <= num; ++k) {
  j = 2;
  
  while(k % j != 0)
   ++j;
  
  if(j == k) {
   printf("%d/t", k);
   
   if(total % 10 == 0)
    printf("\n");
  
   ++total;
  }
 }
 
 printf("\n");
 printf("Total number of primes between 0~%d is %d /n", num, total);
 return;
}
