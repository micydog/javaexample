#include <stdio.h>
#include <string.h>

int main(void)
{
  FILE *fp, *sp;
  char ch;
  int  i,j;
	if((fp=fopen("a","r+"))==NULL)
	{
	  printf("can't open the a file");
	  exit(1);
	}
	if((sp=fopen("c","w+"))==NULL)
	{
	  printf("can't open the c file");
	  exit(1);
	}
	
	for (i=0;i<1000 ;i++ )
	{
		ch=fgetc(fp);
		 fputc(ch,sp);
		 if(feof(fp))
		{
			 printf("%d\n",EOF);
          	         j=fseek(fp,5L,SEEK_SET);
                       	 printf("curpoint=%d\n",j);
			 
		}
	}
		
	 

	fclose(fp);
	fclose(sp);
	exit(0);


}

