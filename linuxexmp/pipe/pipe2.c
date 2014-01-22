#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	int data_processed,p1,p2,p3,i,j;
	int p2c[2],c2p[2];
	pid_t fork_result;
	char buffer[BUFSIZ+1];
	memset(buffer,0,sizeof(buffer));
	p1=1,p2=1;
	if((pipe(p2c)==0)&&(pipe(c2p)==0)){
		fork_result = fork();
		if(fork_result == -1)
		{
			fprintf(stderr,"fork failure\n");
			exit(EXIT_FAILURE);

		}
		if(fork_result == 0)
		{

			for(i=0;i<25;i++)
			{
				if(i%5==0)
				{
					data_processed = read(p2c[0],buffer,BUFSIZ);
					sscanf(buffer,"%d,%d",&p1,&p2);
					printf("the cbuffer %s ",buffer);
					p3=p2+p1;
					p1=p2;
					p2=p3;
					printf("%d ",p3);
				}
				else
				{
					p3=p2+p1;
					p1=p2;
					p2=p3;
					printf("%d ",p3);
					if(i%5==4)
					{

						sprintf(buffer,"%d,%d",p1,p2);
						data_processed= write(c2p[1],buffer,BUFSIZ);
						printf("\n");


					}
				}
			}
		}
		else
		{
			p3=p2+p1;
			p1=p2;
			p2=p3;
			printf("%d ",p3);
			for(i=1;i<25;i++)
			{
				 if(i%5==0)
                                {
                                        data_processed = read(c2p[0],buffer,BUFSIZ);
                                        sscanf(buffer,"%d,%d",&p1,&p2);
					printf("the pbuffer:%s ",buffer);
                                        p3=p2+p1;
                                        p1=p2;
                                        p2=p3;
					printf("%d ",p3);
                                }
                                else
                                {
                                        p3=p2+p1;
                                        p1=p2;
                                        p2=p3;
					printf("%d ",p3);
                                        if(i%5==4)
                                        {

                                                sprintf(buffer,"%d,%d",p1,p2);
                                                data_processed= write(p2c[1],buffer,BUFSIZ);
						printf("\n");		
                                        }
                                }

			}


		}
	}

}
