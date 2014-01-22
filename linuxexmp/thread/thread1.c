#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <math.h>

void *thread_func(void *arg);
static void add(int p1[],int p2[],int p3[]);
static void equal(int p1[],int p2[]);

char buffer[BUFSIZ];
sem_t sem1;
sem_t sem2;

int main()
{
	int p2c[2],c2p[2],p1[3],p2[3],p3[3];
	int res;
	int i;
	pthread_t a_thread;
	void *thread_result;
	
	memset(buffer,0,sizeof(buffer));
        p1[2]=0,p1[1]=0,p1[0]=1,p2[2]=0,p2[1]=0,p2[0]=1;
	res = sem_init(&sem1,0,0);
	if(res!=0)
 	{	perror("sem1 init fialed");
		exit(EXIT_FAILURE);
	}
	res = sem_init(&sem2,0,0);
 	if(res!=0)
        {       perror("sem2 init fialed");
		exit(EXIT_FAILURE);
	}
	res = pthread_create(&a_thread,NULL,thread_func,NULL);
	printf("the main thread  is runing:");
	add(p1,p2,p3);//p3=p2+p1;
	equal(p2,p1);//p1=p2;
	equal(p3,p2);//p2=p3;
	for(i=1;i<50;i++)
	{
		if(i%5==0)
                {
                        sem_wait(&sem2);
                        printf("the main func begin:");
                        sscanf(buffer,"%d,%d,%d,%d,%d,%d",p1+2,p1+1,p1,p2+2,p2+1,p2);
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
                                sprintf(buffer,"%d,%d,%d,%d,%d,%d",p1[2],p1[1],p1[0],p2[2],p2[1],p2[0]);
                                printf("\n");
                                sem_post(&sem1);
                        }		
		}
		

	}	
		res = pthread_join(a_thread,&thread_result);
                if(res!=0)
                {
                        perror("thread joined\n");
                        exit(EXIT_FAILURE);
                }
                sem_destroy(&sem2);
                exit(EXIT_SUCCESS);
	
}


void *thread_func(void *arg)
{
	int p2c[2],c2p[2],p1[3],p2[3],p3[3];
	int i;
	printf("thread func is runing\n");
	for(i=0;i<50;i++)
	{
		 if(i%5==0)
                 {
			sem_wait(&sem1);
			printf("thread func begin:");
			sscanf(buffer,"%d,%d,%d,%d,%d,%d",p1+2,p1+1,p1,p2+2,p2+1,p2);
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
                        	sprintf(buffer,"%d,%d,%d,%d,%d,%d",p1[2],p1[1],p1[0],p2[2],p2[1],p2[0]);
                                printf("\n");
				sem_post(&sem2);
			}			
		 }	

	}
	sem_destroy(&sem1);	
	pthread_exit(NULL);
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
