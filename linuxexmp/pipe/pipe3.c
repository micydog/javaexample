#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

static void add(int p1[],int p2[],int p3[]);
static void equal(int p1[],int p2[]);
int main(void)
{
	int data_processed,i,j;
	int p2c[2],c2p[2],p1[3],p2[3],p3[3];
	pid_t fork_result;
	char buffer[BUFSIZ+1];
	memset(buffer,0,sizeof(buffer));
	p1[2]=0,p1[1]=0,p1[0]=1,p2[2]=0,p2[1]=0,p2[0]=1;
	if((pipe(p2c)==0)&&(pipe(c2p)==0)){
		fork_result = fork();
		if(fork_result == -1)
		{
			fprintf(stderr,"fork failure\n");
			exit(EXIT_FAILURE);

		}
		if(fork_result == 0)
		{
			for(i=0;i<50;i++)
			{
				if(i%5==0)
				{	
					printf("the child begin:");
					data_processed = read(p2c[0],buffer,BUFSIZ);
					sscanf(buffer,"%d,%d,%d,%d,%d,%d",p1+2,p1+1,p1,p2+2,p2+1,p2);
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

						sprintf(buffer,"%d,%d,%d,%d,%d,%d",p1[2],p1[1],p1[0],p2[2],p2[1],p2[0]);
						data_processed= write(c2p[1],buffer,BUFSIZ);
						printf("\n");


					}
				}
			}
		}
		else
		{	add(p1,p2,p3);//p3=p2+p1;
			equal(p2,p1);//p1=p2;
			equal(p3,p2);//p2=p3;
			printf("%d,%d,%d ",p3[2],p3[1],p3[0]);
			for(i=1;i<50;i++)
			{
				 if(i%5==0)
                                {	
					printf("the parent begin:");
                                        data_processed = read(c2p[0],buffer,BUFSIZ);
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
                                                data_processed= write(p2c[1],buffer,BUFSIZ);
						printf("\n");		
                                        }
                                }

			}


		}
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
