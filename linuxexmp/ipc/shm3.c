#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "semun.h"
#include <math.h>
#include <sys/wait.h>
#define SN_READ	0
#define SN_WRITE 1

static int set_semvalue(int semid,int semnum);
static int sem_p(int semid,int semnum);
static int sem_v(int semid,int semnum);
static void del_semvalue(int semid,int semnum);
static void add(int p1[],int p2[],int p3[]);
static void equal(int p1[],int p2[]);

int main()
{
	void *shared_memory = (void*)0;
	int p2c[2],c2p[2],p1[3],p2[3],p3[3];
	pid_t fork_result;
	char buffer[BUFSIZ+1];
	char* shared_buff;
	int i;
	memset(buffer,0,sizeof(buffer));
	p1[2]=0,p1[1]=0,p1[0]=1,p2[2]=0,p2[1]=0,p2[0]=1;
	int shmid,semid;
	semid = semget((key_t)1234,2,0666|IPC_CREAT);
	if(!set_semvalue(semid,SN_READ)){
		fprintf(stderr,"failed to initialize semaphore\n");
	}
	if(!set_semvalue(semid,SN_WRITE)){
		fprintf(stderr,"failed to initialize semaphore\n");
        }
	shmid=shmget((key_t)1235,sizeof(buffer),0666|IPC_CREAT);
	fork_result = fork();
		if(fork_result == -1)
		{
			fprintf(stderr,"fork failure\n");
			exit(EXIT_FAILURE);

		}
		if(fork_result == 0)
		{
			shared_memory = shmat(shmid,(void*)0,0);
			if(shared_memory==(void *)-1){
				fprintf(stderr,"shmat failed\n");
				exit(EXIT_FAILURE);

			}
			printf("memory attached at %x\n",(int)shared_memory);
			shared_buff = (char*)shared_memory;
			for(i=0;i<50;i++)
			{
        			if(i%5==0)
        			{	
					sem_p(semid,SN_WRITE);//信号量锁
                			printf("the child begin:");
                			
                			sscanf(shared_buff,"%d,%d,%d,%d,%d,%d",p1+2,p1+1,p1,p2+2,p2+1,p2);
                			//printf("the cbuffer %s ",buffer);
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
                 			printf("%d,%d,%d  ",p3[2],p3[1],p3[0]);
                 			if(i%5==4)
                 			{

                        			sprintf(shared_buff,"%d,%d,%d,%d,%d,%d",p1[2],p1[1],p1[0],p2[2],p2[1],p2[0]);
                                        	printf("\n");
						sem_v(semid,SN_READ);


                 			}
          			}
			}
			if(shmdt(shared_memory)==-1){
                                fprintf(stderr,"shmdt failed\n");
                                exit(EXIT_FAILURE);
                        }
			printf("child exit\n");
			exit(EXIT_SUCCESS);	
	        	

		}
		else
		{	
			
			shared_memory = shmat(shmid,(void*)0,0);
			if(shared_memory==(void *)-1){
				fprintf(stderr,"shmat failed\n");
				exit(EXIT_FAILURE);

			}
			printf("memory attached at %x\n",(int)shared_memory);
			shared_buff = (char*)shared_memory;	
			sem_p(semid,SN_READ);
			printf("the parent begin:");
			add(p1,p2,p3);//p3=p2+p1;
			equal(p2,p1);//p1=p2;
			equal(p3,p2);//p2=p3;
			printf("%d,%d,%d ",p3[2],p3[1],p3[0]);
			for(i=1;i<50;i++)
			{
				 if(i%5==0)
                                {	
					sem_p(semid,SN_READ);//信号量锁					
					printf("the parent begin:");
					
                                        sscanf(shared_buff,"%d,%d,%d,%d,%d,%d",p1+2,p1+1,p1,p2+2,p2+1,p2);
					//printf("the pbuffer:%s ",buffer);
                                        add(p1,p2,p3);//p3=p2+p1;
                                        equal(p2,p1);//p1=p2;
                                        equal(p3,p2);//p2=p3;
					printf("%d,%d,%d ",p3[2],p3[1],p3[0]);
                                }
                                else
                                {
                                        add(p1,p2,p3);//p3=p2+p1;
                                        equal(p2,p1);//p1=p2;
                                        equal(p3,p2);//p2=p3;
					printf("%d,%d,%d ",p3[2],p3[1],p3[0]);
                                        if(i%5==4)
                                        {

                                                sprintf(shared_buff,"%d,%d,%d,%d,%d,%d",p1[2],p1[1],p1[0],p2[2],p2[1],p2[0]);
                                            	printf("\n");	
						sem_v(semid,SN_WRITE);	
                                        }
                                }

			}
			//printf("parent exit\n");			
			int start_val;
			pid_t childpid = wait(&start_val);	
			if(shmdt(shared_memory)==-1){
				fprintf(stderr,"shmdt failed\n");
				exit(EXIT_FAILURE);
			}
			if(shmctl(shmid,IPC_RMID,0)==-1){
				fprintf(stderr,"shmdt(IPC_RMID) failed\n");
				exit(EXIT_FAILURE);
				
			}
			//del_semvalue(semid,SN_WRITE);
			del_semvalue(semid,SN_READ);
			printf("parent exit\n");
			exit(EXIT_SUCCESS);	
			

		}
		//exit(EXIT_SUCCESS);	
}

static int set_semvalue(int semid,int semnum){
        union semun sem_union;
        if(semnum == SN_READ)
                sem_union.val = 1;
        else
                sem_union.val = 0;
        if(semctl(semid,semnum,SETVAL,sem_union)==-1) return 0;
        return 1;

}

static int sem_p(int semid,int semnum)
{
        struct sembuf sem_b;
        sem_b.sem_num = semnum;
        sem_b.sem_op = -1 ;
        sem_b.sem_flg = SEM_UNDO;
        if(semop(semid,&sem_b,1)== -1)
        {
                fprintf(stderr,"sem_p failed\n");
                return 0;
        }
        return 1;
}

static int sem_v(int semid, int semnum)
{
        struct sembuf sem_b;
        sem_b.sem_num = semnum;
        sem_b.sem_op = 1 ;
        sem_b.sem_flg = SEM_UNDO;
        if(semop(semid,&sem_b,1)== -1)
        {
                fprintf(stderr,"sem_p failed\n");
                return 0;
        }
        return 1;
}
static void del_semvalue(int semid,int semnum)
{
        union semun sem_union;
        if(semctl(semid,semnum,IPC_RMID,sem_union)== -1)
                fprintf(stderr,"failed to delete sem %d\n",semnum);
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


