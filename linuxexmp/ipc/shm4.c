#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "msg_com.h"
#include <sys/msg.h>
#include <math.h>

static void add(int p1[],int p2[],int p3[]);
static void equal(int p1[],int p2[]);


int main()
{
	int serv_msg,clin_msg;
	pid_t fork_result;
	struct my_msg_st msg_data;
	char msg_buff[BUFSIZ];
	long int msg_to_recv =0;	
	int p2c[2],c2p[2],p1[3],p2[3],p3[3];
	int i;
        memset(msg_buff,0,sizeof(msg_buff));
        p1[2]=0,p1[1]=0,p1[0]=1,p2[2]=0,p2[1]=0,p2[0]=1;

	serv_msg = msgget((key_t)1234,0666|IPC_CREAT);
	if(serv_msg == -1)
	{
		fprintf(stderr,"msget failed\n");
		exit(EXIT_FAILURE);
	}
	clin_msg = msgget((key_t)1235,0666|IPC_CREAT);
	if(clin_msg == -1)
        {
                fprintf(stderr,"msget failed\n");
                exit(EXIT_FAILURE);
        }
	fork_result = fork();
	 if(fork_result == -1)
         {
                fprintf(stderr,"fork failure\n");
                exit(EXIT_FAILURE);

         }
         if(fork_result == 0)
         {

		//printf("the child  begin:");
		for(i=0;i<50;i++)
		{
			if(i%5==0)
                        {
				
                                if(msgrcv(clin_msg,(void*)&msg_data,BUFSIZ,msg_to_recv,0) == -1)
                                {
                                        fprintf(stderr,"serv msgrcv failed \n");
                                        exit(EXIT_FAILURE);
                                }
				usleep(800);
				printf("the child begin:");
				strcpy(msg_buff,msg_data.some_text);
                                sscanf(msg_buff,"%d,%d,%d,%d,%d,%d",p1+2,p1+1,p1,p2+2,p2+1,p2);
                                //sprintf(msg_buff,"%d,%d,%d,%d,%d,%d",p1[2],p1[1],p1[0],p2[2],p2[1],p2[0]);
                                add(p1,p2,p3);//p3=p2+p1;
                                equal(p2,p1);//p1=p2;
                                equal(p3,p2);//p2=p3;    
				printf("%d,%d,%d  ",p3[2],p3[1],p3[0]);
			}
			else
			{
				add(p1,p2,p3);//p3=p2+p1;
                                equal(p2,p1);//p1=p2;
                                equal(p3,p2);//p2=p3;
                                printf("%d,%d,%d ",p3[2],p3[1],p3[0]);
                                if(i%5==4)
				{
				     msg_data.msg_type = 1;
                                      //sscanf(msg_buff,"%d,%d,%d,%d,%d,%d",p1+2,p1+1,p1,p2+2,p2+1,p2);
                                     sprintf(msg_buff,"%d,%d,%d,%d,%d,%d",p1[2],p1[1],p1[0],p2[2],p2[1],p2[0]);
                                     strcpy(msg_data.some_text,msg_buff);  
                                     if(msgsnd(serv_msg,(void*)&msg_data,BUFSIZ,0) ==-1) {  
                                           fprintf(stderr,"msgsnd failed\n");
                                           exit(EXIT_FAILURE);
                                     }
				     printf("\n");
				}
			}
		}
		if(msgctl(clin_msg,IPC_RMID,0)==-1)
                {
                      fprintf(stderr,"msgctl(IPC_RMID) serv failed\n");
                }
		printf("child exit\n");
		exit(EXIT_SUCCESS);	
	 }
	 else
	 {
		printf("the parent begin:");
                add(p1,p2,p3);//p3=p2+p1;
                equal(p2,p1);//p1=p2;
                equal(p3,p2);//p2=p3;
                printf("%d,%d,%d ",p3[2],p3[1],p3[0]);
		for(i=1;i<50;i++)
                {
			if(i%5==0)
                      	{
				if(msgrcv(serv_msg,(void*)&msg_data,BUFSIZ,msg_to_recv,0) == -1)
				{
					fprintf(stderr,"serv msgrcv failed \n");
					exit(EXIT_FAILURE);
				}
			        usleep(800);
				printf("the parent begin:");
				strcpy(msg_buff,msg_data.some_text);
				sscanf(msg_buff,"%d,%d,%d,%d,%d,%d",p1+2,p1+1,p1,p2+2,p2+1,p2);
				//sprintf(msg_buff,"%d,%d,%d,%d,%d,%d",p1[2],p1[1],p1[0],p2[2],p2[1],p2[0]);
				add(p1,p2,p3);//p3=p2+p1;
                                equal(p2,p1);//p1=p2;
                                equal(p3,p2);//p2=p3;
                                printf("%d,%d,%d  ",p3[2],p3[1],p3[0]);
				
			}
			else
			{
				add(p1,p2,p3);//p3=p2+p1;
                                equal(p2,p1);//p1=p2;
                                equal(p3,p2);//p2=p3;
                                printf("%d,%d,%d ",p3[2],p3[1],p3[0]);
				if(i%5==4)
                                {
				      msg_data.msg_type = 1;
				      //sscanf(msg_buff,"%d,%d,%d,%d,%d,%d",p1+2,p1+1,p1,p2+2,p2+1,p2);
                                      sprintf(msg_buff,"%d,%d,%d,%d,%d,%d",p1[2],p1[1],p1[0],p2[2],p2[1],p2[0]);
				      strcpy(msg_data.some_text,msg_buff);
				      
				      if(msgsnd(clin_msg,(void*)&msg_data,BUFSIZ,0) == -1)
					{
						fprintf(stderr,"msgsnd failed\n");
						exit(EXIT_FAILURE);
					}

                                      printf("\n");
                                      
                                }
	
			}
	              		
		}
		int start_val;
                pid_t childpid = wait(&start_val);
                if(msgctl(serv_msg,IPC_RMID,0)==-1)
                {
                      fprintf(stderr,"msgctl(IPC_RMID) serv failed\n");
                }
		printf("parent exit\n");
                exit(EXIT_SUCCESS);
	 }
}

static void add(int p1[],int p2[],int p3[]){
        int fnum = pow(10,9);
        int i;
        int flag=0;
        for(i=0;i<3;i++)
        {
                p1[i]=p1[i]%fnum;
                p2[i]=p2[i]%fnum;
                p3[i]=(p1[i]+p2[i]+flag)%fnum ;
                flag = (p1[i]+p2[i]+flag)/fnum;
                //printf("\nthe p num: %d,%d,%d\n",i,p1[i],p2[i]);
        }
                
}

static void equal(int p1[],int p2[])
{
      memcpy(p2,p1,3*sizeof(int));
      //printf("\n the equal :%d,%d %d|%d %d\n",sizeof(p1),p2[1],p2[0],p1[1],p1[0]);
}


 
