#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "shm_com.h"
#include "semun.h"
#define SN_READ	0
#define SN_WRITE 1

static int set_semvalue(int semid,int semnum);
static int sem_p(int semid,int semnum);
static int sem_v(int semid,int semnum);
static void del_semvalue(int semid,int semnum);

int main()
{
	int runing=1;
	void *shared_memory = (void*)0;
	struct shared_use_st *shared_stuff;
	int shmid;
	int semid;
	char buffer[BUFSIZ];
	semid = semget((key_t)1234,2,0666|IPC_CREAT);
	if(!set_semvalue(semid,SN_READ)){
		fprintf(stderr,"failed to initialize semaphore\n");
	}
	if(!set_semvalue(semid,SN_WRITE)){
		fprintf(stderr,"failed to initialize semaphore\n");
        }
	shmid=shmget((key_t)1235,sizeof(struct shared_use_st),0666|IPC_CREAT);
	shared_memory = shmat(shmid,(void*)0,0);
	if(shared_memory==(void *)-1){
		fprintf(stderr,"shmat failed\n");
		exit(EXIT_FAILURE);

	}
	printf("memory attached at %x\n",(int)shared_memory);
	shared_stuff =(struct shared_use_st*) shared_memory;
	while(runing)
	{
		sem_p(semid,SN_READ);//信号量锁
		printf("enter some text:");
		fgets(buffer,BUFSIZ,stdin);
		strncpy(shared_stuff->some_text,buffer,TEXT_SZ);
		sem_v(semid,SN_WRITE);
		if(strncmp(shared_stuff->some_text,"end",3)==0)
			runing =0 ;
		
	}
        if(shmdt(shared_memory)==-1){
		fprintf(stderr,"shmdt failed\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
	
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
		fprintf(stderr,"failed to delete sem\n");	
}


